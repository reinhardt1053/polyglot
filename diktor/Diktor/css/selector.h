//
//  selector.h
//  Diktor
//
//  Created by Massimo Fazzolari on 21/03/15.
//  Copyright (c) 2015 Massimo Fazzolari. All rights reserved.
//

#pragma once

#include <string>
#include <vector>


using namespace std;

namespace css {
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
}
