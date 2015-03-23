//
//  stylesheet.h
//  Diktor
//
//  Created by Massimo Fazzolari on 20/03/15.
//  Copyright (c) 2015 Massimo Fazzolari. All rights reserved.
//

#pragma once

#include <string>
#include <vector>
#include "css/rule.h"

using namespace std;

namespace css {
    class Stylesheet
    {
    public:
        vector<shared_ptr<Rule>> rules;
        string to_string();
    };
}

