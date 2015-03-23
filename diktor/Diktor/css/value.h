//
//  value.h
//  Diktor
//
//  Created by Massimo Fazzolari on 20/03/15.
//  Copyright (c) 2015 Massimo Fazzolari. All rights reserved.
//

#pragma once

#include <string>

using namespace std;

namespace css {
    
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
}

