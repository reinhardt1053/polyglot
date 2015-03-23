//
//  css.h
//  Diktor
//
//  Created by Massimo Fazzolari on 12/03/15.
//  Copyright (c) 2015 Massimo Fazzolari. All rights reserved.
//

#pragma once

#include <stdlib.h>
#include <string>
#include <vector>
#include <functional>
#include "css/value.h"
#include "css/stylesheet.h"
#include "css/rule.h"

using namespace std;

namespace css
{
    class Parser
    {
    public:
        static shared_ptr<Stylesheet> parse(string source);
        
    private:
        size_t _pos;
        string _input;
        
        char next_char();
        bool starts_with(string s);
        bool has_next_char();
        char consume_char();
        string consume_while(function<bool(char)> test);
        void consume_whitespaces();
        
        // Parse a list of rule sets, separated by optional whitespace.
        vector<shared_ptr<Rule>> parse_rules();
        
        // Parse a rule set: `<selectors> { <declarations> }`.
        shared_ptr<Rule> parse_rule();
        
        // Parse one simple selector, e.g.: `type#id.class1.class2.class3`
        shared_ptr<SimpleSelector> parse_simple_selector();
        
        // Parse one `<property>: <value>;` declaration.
        shared_ptr<Declaration> parse_declaration();
        
        
        // Parse a comma-separated list of selectors.
        vector<shared_ptr<Selector>> parse_selectors();
        
        // Parse a list of declarations enclosed in `{ ... }`.
        vector<shared_ptr<Declaration>> parse_declarations();
        
        
        static bool is_valid_identifier_char(char c);
        
        string parse_identifier();
        
        float parse_float();
        Unit parse_unit();
        
        //Methods for parsing values:
        shared_ptr<Value> parse_value();
        shared_ptr<Value> parse_length();
        shared_ptr<Value> parse_color();
        shared_ptr<Value> parse_keyword();
        
        
        unsigned int parse_hex_pair();
        
        static bool selector_greater(shared_ptr<Selector> a, shared_ptr<Selector> b);
        
        Parser(string input);
    };
}

