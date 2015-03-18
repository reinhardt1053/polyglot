//
//  parser.h
//  Diktor
//
//  Created by Massimo Fazzolari on 10/03/15.
//  Copyright (c) 2015 Massimo Fazzolari. All rights reserved.
//

#ifndef _HTML_H
#define _HTML_H

#include <stdlib.h>
#include <string>
#include <functional>
#include <map>

#include "dom/node.h"
#include "dom/attribute.h"

using namespace std;

namespace html {
    
    class Parser {
        
    public:
        // Parse an HTML document and return the root element.
        static shared_ptr<dom::Node> parse(string source);
        
    private:
        size_t _pos;
        string _input;
        
        static bool is_whitespace(char c);
        static bool is_alpha_or_number(char c);
        
        char next_char();
        bool starts_with(string s);
        bool has_next();
        char consume_char();
        string consume_while(function<bool(char)> test);
        void consume_whitespaces();
        
        // Parse a tag name or attribute name
        string parse_name();
        
        // Parse a quoted value
        string parse_value();
        
        // Parse a text node
        shared_ptr<dom::Node> parse_text();
        
        // Parse a single element node, including its open tag, content, and closing tag
        shared_ptr<dom::Node> parse_element();
        
        // Parse a single node
        shared_ptr<dom::Node> parse_node();
        
        // Parse a single name="value" pair
        dom::Attribute parse_attr();
        
        // Parse a list of name="value" pairs, separated by whitespace.
        map<string,string> parse_attributes();
        
        //Parse a sequence of sibling nodes
        vector<shared_ptr<dom::Node>> parse_nodes();
        
        Parser(string input);
        
    };
}

#endif
