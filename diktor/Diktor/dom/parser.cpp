//
//  parser.cpp
//  Diktor
//
//  Created by Massimo Fazzolari on 10/03/15.
//  Copyright (c) 2015 Massimo Fazzolari. All rights reserved.
//

#include <assert.h>
#include <map>
#include "dom/element.h"
#include "dom/text.h"
#include "dom/parser.h"

namespace dom {
    
    shared_ptr<dom::Node> Parser::parse(string source)
    {
        Parser parser(source);
        vector<shared_ptr<dom::Node>> nodes = parser.parse_nodes();
        
        
        // If the document contains a root element, just return it. Otherwise, create one.
        if (nodes.size() == 1)
            return nodes[0];
        else
        {
            map<string,string> root_attrs;
            auto root = make_shared<dom::Element>("html",root_attrs, nodes);
            return root;
        }
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
    
    bool Parser::has_next()
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
        
        while (has_next() && test(next_char()))
        {
            result.push_back(consume_char());
        }
        
        return result;
    }
    
    bool Parser::is_whitespace(char c)
    {
        return isspace(c);
    }
    
    
    void Parser::consume_whitespaces()
    {
        consume_while(is_whitespace);
    }
    
    bool Parser::is_alpha_or_number(char c)
    {
        return isalpha(c) || isnumber(c);
    }
    
    string Parser::parse_name()
    {
        return consume_while(is_alpha_or_number);
    }
    
    shared_ptr<dom::Node> Parser::parse_text()
    {
        auto is_not_open_tag = [](char c) -> bool { return c != '<'; } ;
        return make_shared<dom::Text>(consume_while(is_not_open_tag));
    }
    
    shared_ptr<dom::Node> Parser::parse_element()
    {
        //Opening tag
        assert(consume_char() == '<');
        
        string tag_name = parse_name();
        map<string,string> attrs = parse_attributes();
        
        assert(consume_char() == '>');
        
        //Content
        vector<shared_ptr<dom::Node>> children = parse_nodes();
        
        //Closing tag
        assert(consume_char() == '<');
        assert(consume_char() == '/');
        assert(parse_name() == tag_name);
        assert(consume_char() == '>');
        
        return make_shared<dom::Element>(tag_name, attrs, children);
    }
    
    shared_ptr<dom::Node> Parser::parse_node()
    {
        if (next_char() == '<')
            return parse_element();
        else
            return parse_text();
    }
    
    dom::Attribute Parser::parse_attr()
    {
        dom::Attribute attr;
        attr.name = parse_name();
        assert(consume_char() == '=');
        attr.value = parse_value();
        return attr;
    }
    
    string Parser::parse_value()
    {
        char quote_char = consume_char();
        assert(quote_char == '"' || quote_char == '\'');
        
        auto is_not_quote_char = [=](char c) -> bool { return c != quote_char; };
        
        string value = consume_while(is_not_quote_char);
        assert(consume_char() == quote_char);
        return value;
        
    }
    
    map<string,string> Parser::parse_attributes()
    {
        map<string,string> attributes;
        
        while (true) {
            consume_whitespaces();
            if (next_char() == '>') {
                break;
            }
            dom::Attribute attr = parse_attr();
            attributes[attr.name] = attr.value;
        }
        
        return attributes;
    }
    
    vector<shared_ptr<dom::Node>> Parser::parse_nodes()
    {
        vector<shared_ptr<dom::Node>> nodes;
        
        while (true){
            consume_whitespaces();
            if (!has_next() || starts_with("</")){
                break;
            }
            nodes.push_back(parse_node());
        }
        
        return nodes;
    }
    
}
