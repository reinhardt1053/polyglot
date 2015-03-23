//
//  textnode.h
//  Diktor
//
//  Created by Massimo Fazzolari on 20/02/15.
//  Copyright (c) 2015 Massimo Fazzolari. All rights reserved.
//

#pragma once

#include "node.h"
#include <string>
#include <iostream>

namespace dom {
    class Text : public Node
    {
    private:
        string _data;
        
    public:
        Text(string data);
        
        string to_string() override;
    };
}