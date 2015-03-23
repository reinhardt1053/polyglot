//
//  rule.cpp
//  Diktor
//
//  Created by Massimo Fazzolari on 20/03/15.
//  Copyright (c) 2015 Massimo Fazzolari. All rights reserved.
//

#include "rule.h"

namespace css {
    string Rule::to_string()
    {
        string result;
        
        //Selectors
        bool append_comma = false;
        for (auto selector : selectors){
            if (append_comma) result.append(",");
            result.append(selector->to_string());
            append_comma = true;
        }
        result.append(" {");
        
        //Declarations
        for (auto declaration : declarations) {
            result.append(declaration->to_string());
        }
        
        result.append("} ");
        return result;
    }
}