//
//  selector.cpp
//  Diktor
//
//  Created by Massimo Fazzolari on 21/03/15.
//  Copyright (c) 2015 Massimo Fazzolari. All rights reserved.
//

#include "selector.h"

namespace css {
    //http://www.w3.org/TR/selectors/#specificity
    unsigned int SimpleSelector::specificity()
    {
        string a = (id.empty() ? "0" : "1");
        string b = std::to_string(classes.size());
        string c = (tag_name.empty() ? "0" : "1");
        
        return stoi(a+b+c);
    }
    
    string SimpleSelector::to_string()
    {
        string result;
        
        //Tag name
        if (!tag_name.empty()){
            result.append(tag_name);
        }
        
        //Id
        if (!id.empty()){
            result.append("#");
            result.append(id);
        }
        
        //Classes
        for (auto className : classes){
            result.append(".");
            result.append(className);
        }
        
        return result;
    }
}