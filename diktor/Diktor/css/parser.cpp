//
//  css.cpp
//  Diktor
//
//  Created by Massimo Fazzolari on 12/03/15.
//  Copyright (c) 2015 Massimo Fazzolari. All rights reserved.
//

#include <assert.h>
#include <algorithm>
#include <string>

#include "css/parser.h"
#include "css/stylesheet.h"

namespace css {

    Parser::Parser(string input)
    {
        _input = input;
        _pos = 0;
    }
    
    char Parser::next_char()
    {
        return _input[_pos];
    }
    
    bool Parser::starts_with(string s)
    {
        return _input.compare(_pos, s.size(), s) == 0;
    }
    
    bool Parser::has_next_char()
    {
        return  _pos < _input.size() - 1;
    }
    
    //Consume a char
    char Parser::consume_char()
    {
        char c = _input[_pos]; _pos++;
        return c;
    }
    
    string Parser::consume_while(function<bool(char)> test)
    {
        string result;
        
        while (has_next_char() && test(next_char()))
        {
            result.push_back(consume_char());
        }
        
        return result;
    }
    
    void Parser::consume_whitespaces()
    {
        auto is_whitespace = [](char c) -> bool { return isspace(c); };
        consume_while(is_whitespace);
    }
    
    bool Parser::is_valid_identifier_char(char c)
    {
        return isalnum(c)  ||
               isnumber(c) ||
               c == '_'    ||
               c == '-';
    }
    
    string Parser::parse_identifier()
    {
        return consume_while(is_valid_identifier_char);
    }
    
    shared_ptr<SimpleSelector> Parser::parse_simple_selector()
    {
        auto selector = make_shared<SimpleSelector>();
        
        while (has_next_char()) {
            switch (char c = next_char()) {
                case '#':
                    consume_char();
                    selector->id = parse_identifier();
                    break;
                case '.':
                    consume_char();
                    selector->classes.push_back(parse_identifier());
                    break;
                case '*':
                    //universal selector
                    consume_char();
                default:
                    if (is_valid_identifier_char(c)){
                        selector->tag_name = parse_identifier();
                    }
                    else
                    {
                        return selector;
                    }
                    break;
            }
        }
        
        return selector;
    }
    
    vector<shared_ptr<Rule>> Parser::parse_rules()
    {
        vector<shared_ptr<Rule>> rules;
        while (true) {
            consume_whitespaces();
            if (!has_next_char()) break;
            rules.push_back(parse_rule());
        }
        return rules;
    }
    
    
    // Parse a rule set: `<selectors> { <declarations> }`.
    shared_ptr<Rule> Parser::parse_rule()
    {
        auto rule = make_shared<Rule>();
        rule->selectors = parse_selectors();
        rule->declarations = parse_declarations();
        return rule;
    }
    
    //Return true if Selector A specificity is greater then  Selector B specificity
    bool Parser::selector_greater(shared_ptr<Selector> a, shared_ptr<Selector> b)
    {
        return a->specificity() > b->specificity();
    }
    
    // Parse a comma-separated list of selectors.
    vector<shared_ptr<Selector>> Parser::parse_selectors()
    {
        vector<shared_ptr<Selector>> selectors;
        bool start_of_declarations = false;
        while (!start_of_declarations) {
            auto selector = parse_simple_selector();
            selectors.push_back(selector);
            consume_whitespaces();
            switch (char c = next_char()) {
                case ',':
                    consume_char();
                    consume_whitespaces();
                    break;
                case '{':
                    start_of_declarations = true;
                    break;
                default:
                    assert(false);
                    break;
            }
        }
        
        // Selectors with higher specificity comes first
        sort(selectors.begin(), selectors.end(), selector_greater );
        return selectors;
    }
    
    // Parse a list of declarations enclosed in `{ ... }`.
    vector<shared_ptr<Declaration>> Parser::parse_declarations()
    {
        assert(consume_char() == '{');
        vector<shared_ptr<Declaration>> declarations;
        
        while (true) {
            consume_whitespaces();
            if (next_char() == '}') {
                consume_char();
                break;
            }
            declarations.push_back(parse_declaration());
        }
        return declarations;
    }
    
    shared_ptr<Declaration> Parser::parse_declaration()
    {
        auto property_name = parse_identifier();
        consume_whitespaces();
        assert(consume_char() == ':');
        consume_whitespaces();
        auto value = parse_value();
        consume_whitespaces();
        assert(consume_char() == ';');
        
        auto declaration = make_shared<Declaration>();
        declaration->name = property_name;
        declaration->value = value;
        
        return declaration;
    }
    
    shared_ptr<Value> Parser::parse_value()
    {
        char c = next_char();
        
        if (isnumber(c))
            return parse_length();
        else if (c == '#')
            return parse_color();
        else
            return parse_keyword();
    }
    
    shared_ptr<Value> Parser::parse_length()
    {
        auto length = make_shared<Length>();
        length->value = parse_float();
        length->unit = parse_unit();
        
        return length;
    }
    
    float Parser::parse_float()
    {
        auto is_float_number_char = [] (char c) -> bool {
            if (isnumber(c) || c == '.') return true;
            else return false;
        };
        
        auto float_str = consume_while(is_float_number_char);
        return atof(float_str.c_str());
    }
    
    Unit Parser::parse_unit()
    {
        auto identifier = parse_identifier();
        
        //Lower case the identifier (e.g. "Px" to "px")
        transform(identifier.begin(), identifier.end(),
                  identifier.begin(), toupper);
        
        if (identifier == "px")
            return Unit::PX;
        else if (identifier == "cm")
            return Unit::CM;
        else
            assert(false);
    }
    
    shared_ptr<Value> Parser::parse_color()
    {
        assert(consume_char() == '#');
        
        auto color = make_shared<Color>();
        
        color->r = parse_hex_pair();
        color->g = parse_hex_pair();
        color->b = parse_hex_pair();
        color->a = 255;
        
        return color;  
    }
    
    // Convert from Hex to Decimal
    unsigned int Parser::parse_hex_pair()
    {
        auto hexstr = _input.substr(_pos, 2);
        _pos +=2;
        
        //Convert an HEX string to an unsigned int (es. FF -> 255)
        return static_cast<unsigned int>(strtoul(hexstr.c_str(), NULL, 16));
    }
    
    shared_ptr<Value> Parser::parse_keyword()
    {
        auto keyword = make_shared<Keyword>();
        keyword->value = parse_identifier();
        return keyword;
    }
    
    shared_ptr<Stylesheet> Parser::parse(string source)
    {
        Parser parser(source);
        auto stylesheet = make_shared<Stylesheet>();
        stylesheet->rules = parser.parse_rules();
        return stylesheet;
    }
}