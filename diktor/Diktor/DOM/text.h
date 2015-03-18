//
//  textnode.h
//  Diktor
//
//  Created by Massimo Fazzolari on 20/02/15.
//  Copyright (c) 2015 Massimo Fazzolari. All rights reserved.
//

#ifndef TEXT_H
#define TEXT_H

#include "node.h"
#include <string>
#include <iostream>

namespace DOM {

class Text : public Node
{
private:
    string _data;

public:
    Text(string data);
    
    string to_string() override;
};

}


#endif
