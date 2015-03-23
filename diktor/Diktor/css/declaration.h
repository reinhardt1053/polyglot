//
//  declaration.h
//  Diktor
//
//  Created by Massimo Fazzolari on 21/03/15.
//  Copyright (c) 2015 Massimo Fazzolari. All rights reserved.
//

#pragma once

#include <string>
#include "css/value.h"

using namespace std;

namespace css {
    class Declaration
    {
    public:
        string name;
        shared_ptr<Value> value;
        
        string to_string();
    };
}
