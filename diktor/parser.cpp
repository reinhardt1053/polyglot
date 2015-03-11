//
//  parser.cpp
//  Diktor
//
//  Created by Massimo Fazzolari on 10/03/15.
//  Copyright (c) 2015 Massimo Fazzolari. All rights reserved.
//

#include "parser.h"

char Parser::next()
{
    return _input[_pos];
}

bool Parser::starts_with(string s)
{
    return _input.compare(_pos, s.size(), s) == 0;
}

bool Parser::has_next()
{
    return _input.size() == _pos;
}

//Consume a char
char Parser::consume_char()
{
    char c = _input[_pos]; _pos++;
    return c;
}

string Parser::consume_while(testCharFn test)
{
    string result;
    
    while (has_next() && test(next()))
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



