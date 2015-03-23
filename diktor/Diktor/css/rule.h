//
//  rule.h
//  Diktor
//
//  Created by Massimo Fazzolari on 20/03/15.
//  Copyright (c) 2015 Massimo Fazzolari. All rights reserved.
//

#pragma once

#include <string>
#include "css/selector.h"
#include "css/declaration.h"

using namespace std;

namespace css {
    class Rule
    {
    public:
        vector<shared_ptr<Selector>> selectors;
        vector<shared_ptr<Declaration>> declarations;
        string to_string();
    };
    
}
