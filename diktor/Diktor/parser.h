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

using namespace std;


typedef bool (*testCharFn)(char ch);

class Parser {
    
private:
    
    size_t _pos;
    string _input;
    
    static bool is_whitespace(char c);
    
public:
    char next();
    bool starts_with(string s);
    bool has_next();
    char consume_char();
    string consume_while(testCharFn test);
    void consume_whitespaces();
    
    
};

#endif
