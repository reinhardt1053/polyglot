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

#include "DOM/node.h"
#include "DOM/attribute.h"

using namespace std;

namespace HTML {
    
    class Parser {
        
    public:
        // Parse an HTML document and return the root element.
        static shared_ptr<DOM::Node> parse(string source);
        
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
        shared_ptr<DOM::Node> parse_text();
        
        // Parse a single element node, including its open tag, content, and closing tag
        shared_ptr<DOM::Node> parse_element();
        
        // Parse a single node
        shared_ptr<DOM::Node> parse_node();
        
        // Parse a single name="value" pair
        DOM::Attribute parse_attr();
        
        // Parse a list of name="value" pairs, separated by whitespace.
        map<string,string> parse_attributes();
        
        //Parse a sequence of sibling nodes
        vector<shared_ptr<DOM::Node>> parse_nodes();
        
        Parser(string input);
        
    };
}

#endif
