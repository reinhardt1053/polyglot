//
//  declaration.cpp
//  Diktor
//
//  Created by Massimo Fazzolari on 21/03/15.
//  Copyright (c) 2015 Massimo Fazzolari. All rights reserved.
//

#include "declaration.h"

namespace css {
    string Declaration::to_string()
    {
        string result;
        
        //Property name
        result.append(name);
        result.append(":");
        result.append(value->to_string());
        result.append(";");
        
        return result;
    }
}