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

namespace CSS
{
    class Value
    {
        
    };
    
    class Keyword : public Value
    {
    public:
        string value;
    };
    
    enum Unit { PX, CM, MM, EM };
    
    class Length : public Value
    {
    public:
        float value;
        Unit unit;
    };
    
    class Color: public Value
    {
    public:
        unsigned int r;
        unsigned int g;
        unsigned int b;
        unsigned int a;
    };
    
    class Declaration
    {
    public:
        string name;
        shared_ptr<Value> value;
    };
    
    // http://www.w3.org/TR/selectors/#specificity
    class Specificity
    {
    public:
        size_t a;
        size_t b;
        size_t c;
    };
    
    class Selector
    {
    public:
        virtual Specificity specificity() = 0;
    };
    
    class SimpleSelector : public Selector
    {
        
    public:
        string tag_name;
        string id;
        vector<string> classes;
        
        Specificity specificity() override;
    };
    
    class Rule
    {
    public:
        vector<shared_ptr<Selector>> selectors;
        vector<shared_ptr<Declaration>> declarations;
    };
    
    class Stylesheet
    {
    public:
        vector<shared_ptr<Rule>> rules;
    };
    

    
    class Parser
    {
        
    private:
        size_t _pos;
        string _input;
        
        char next_char();
        bool starts_with(string s);
        bool has_next_char();
        char consume_char();
        string consume_while(function<bool(char)> test);
        void consume_whitespaces();
        
        // Parse one simple selector, e.g.: `type#id.class1.class2.class3`
        shared_ptr<SimpleSelector> parse_simple_selector();
        
        // Parse one `<property>: <value>;` declaration.
        shared_ptr<Declaration> parse_declaration();
        
        // Parse a rule set: `<selectors> { <declarations> }`.
        shared_ptr<Rule> parse_rule();
        
        // Parse a comma-separated list of selectors.
        vector<shared_ptr<Selector>> parse_selectors();
        vector<shared_ptr<Declaration>> parse_declarations();
        
        
        static bool is_valid_identifier_char(char c);
        
        string parse_identifier();
        
        //Methods for parsing values:
        shared_ptr<Value> parse_value();
        shared_ptr<Value> parse_length();
        shared_ptr<Value> parse_color();
        shared_ptr<Value> parse_keyword();
        
        
        Parser(string input);
    };
    
    
}
#endif
