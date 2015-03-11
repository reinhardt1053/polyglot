//
//  parser.h
//  Diktor
//
//  Created by Massimo Fazzolari on 10/03/15.
//  Copyright (c) 2015 Massimo Fazzolari. All rights reserved.
//

#ifndef _PARSER_H
#define _PARSER_H

#include <stdlib.h>
#include <string>
#include "node.h"
#include <functional>
#include <map>

using namespace std;


struct Attribute {
    string name;
    string value;
};


class Parser {
    
private:
    
    size_t _pos;
    string _input;
    
    static bool is_whitespace(char c);
    static bool is_alpha_or_number(char c);
    
protected:
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
    Attribute parse_attr();
    
    // Parse a list of name="value" pairs, separated by whitespace.
    map<string,string> parse_attributes();
    
    //Parse a sequence of sibling nodes
    vector<shared_ptr<DOM::Node>> parse_nodes();
    
public:
    Parser();
    Parser(size_t pos, string input);
    
    // Parse an HTML document and return the root element.
    shared_ptr<DOM::Node> parse(string source);
    
};

#endif
