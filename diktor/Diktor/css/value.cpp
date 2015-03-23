//
//  value.cpp
//  Diktor
//
//  Created by Massimo Fazzolari on 20/03/15.
//  Copyright (c) 2015 Massimo Fazzolari. All rights reserved.
//

#include <string>
#include <assert.h>

#include "css/value.h"

using namespace std;

namespace css {
    
    string Keyword::to_string()
    {
        return value;
    }
    
    string Length::to_string()
    {
        string result;
        
        result.append(std::to_string(value));
        
        switch (unit) {
            case PX:
                result.append("px");
                break;
            case CM:
                result.append("cm");
                break;
            default:
                assert(false);
                break;
        }
        
        return result;
    }
    
    string Color::to_string()
    {
        string result;
        result.append("rgb(");
        result.append(std::to_string(r));
        result.append(",");
        result.append(std::to_string(g));
        result.append(",");
        result.append(std::to_string(b));
        result.append(")");
        
        return result;
    }
}