//
//  css.cpp
//  Diktor
//
//  Created by Massimo Fazzolari on 12/03/15.
//  Copyright (c) 2015 Massimo Fazzolari. All rights reserved.
//

#include "css.h"
#include <assert.h>

namespace CSS {

    //http://www.w3.org/TR/selectors/#specificity
    Specificity SimpleSelector::specificity()
    {
        Specificity specificity;
        
        specificity.a = (id.empty() ? 0 : 1);
        specificity.b = classes.size();
        specificity.c = (tag_name.empty() ? 0 : 1);
        
        return specificity;
    }
    
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
        auto is_whitespace = [](char c) { return isspace(c); };
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
                default:
                    if (is_valid_identifier_char(c)){
                        selector->tag_name = parse_identifier();
                    }
                    break;
            }
        }
        
        return selector;
    }
    
    // Parse a rule set: `<selectors> { <declarations> }`.
    shared_ptr<Rule> Parser::parse_rule()
    {
        auto rule = make_shared<Rule>();
        rule->selectors = parse_selectors();
        rule->declarations = parse_declarations();
        return rule;
    }
    
    // Parse a comma-separated list of selectors.
    vector<shared_ptr<Selector>> Parser::parse_selectors()
    {
        vector<shared_ptr<Selector>> selectors;
        bool start_of_declarations = false;
        while (!start_of_declarations) {
            auto selector = parse_simple_selector();
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
        
        if (isalnum(c))
            return parse_length();
        else if (c == '#')
            return parse_color();
        else
            return parse_keyword();
    }
    
    
}