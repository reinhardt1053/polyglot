//
//  textnode.cpp
//  Diktor
//
//  Created by Massimo Fazzolari on 23/02/15.
//  Copyright (c) 2015 Massimo Fazzolari. All rights reserved.
//

#include "text.h"

namespace dom {
    Text::Text(string data)
    {
        _data = data;
    }
    
    string Text::to_string()
    {
        return _data;
    }
}


