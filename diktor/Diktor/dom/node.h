//
//  dom.h
//  Diktor
//
//  Created by Massimo Fazzolari on 16/02/15.
//  Copyright (c) 2015 Massimo Fazzolari. All rights reserved.
//

#pragma once

#include <vector>

using namespace std;

namespace dom {
    class Node {
    public:
        vector<shared_ptr<Node>> children;
        virtual string to_string() = 0;
    };
}
