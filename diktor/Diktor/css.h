//
//  css.h
//  Diktor
//
//  Created by Massimo Fazzolari on 12/03/15.
//  Copyright (c) 2015 Massimo Fazzolari. All rights reserved.
//

#ifndef CSS_H
#define CSS_H

#include <stdlib.h>
#include <string>
#include <vector>
#include <functional>

using namespace std;

namespace css
{
    class Value
    {
    public:
        virtual string to_string() = 0;
    };
    
    class Keyword : public Value
    {
    public:
        string value;
        string to_string() override;
    };
    
    enum Unit { PX, CM };
    
    class Length : public Value
    {
    public:
        float value;
        Unit unit;
        
        string to_string() override;
    };
    
    class Color: public Value
    {
    public:
        unsigned int r;
        unsigned int g;
        unsigned int b;
        unsigned int a;
        
        string to_string() override;
    };
    
    class Declaration
    {
    public:
        string name;
        shared_ptr<Value> value;
        
        string to_string();
    };
    
    class Selector
    {
    public:
        virtual unsigned int specificity() = 0;
        virtual string to_string() = 0;
    };
    
    class SimpleSelector : public Selector
    {
        
    public:
        string tag_name;
        string id;
        vector<string> classes;
        
        unsigned int specificity() override;
        string to_string() override;
    };
    
    class Rule
    {
    public:
        vector<shared_ptr<Selector>> selectors;
        vector<shared_ptr<Declaration>> declarations;
        string to_string();
    };
    
    class Stylesheet
    {
    public:
        vector<shared_ptr<Rule>> rules;
        string to_string();
    };
    
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
#endif
