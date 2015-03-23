//
//  stylesheet.cpp
//  Diktor
//
//  Created by Massimo Fazzolari on 20/03/15.
//  Copyright (c) 2015 Massimo Fazzolari. All rights reserved.
//

#include "css/stylesheet.h"

namespace css {
    string Stylesheet::to_string()
    {
        string result;
        for(auto rule : rules)
        {
            result.append(rule->to_string());
        }
        return result;
    }
}