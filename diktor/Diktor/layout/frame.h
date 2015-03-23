//
//  frame.h
//  Diktor
//
//  Created by Massimo Fazzolari on 18/03/15.
//  Copyright (c) 2015 Massimo Fazzolari. All rights reserved.
//

#pragma once

#include <map>

#include "dom/node.h"
#include "css/value.h"

namespace layout {
    class Frame {
    public:
        shared_ptr<dom::Node> node;
        map<string,css::Value> specified_values;
        vector<shared_ptr<Frame>> children;
    };
}

