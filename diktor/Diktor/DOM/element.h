//
//  element.h
//  Diktor
//
//  Created by Massimo Fazzolari on 23/02/15.
//  Copyright (c) 2015 Massimo Fazzolari. All rights reserved.
//

#ifndef ELEMENT_H
#define ELEMENT_H

#include "node.h"
#include <string>
#include <map>
#include <vector>

namespace dom {

class Element : public Node
{
private:
    string _tagName;
    map<string, string> _attributes;
    
public:
    Element(string tagName, map<string,string> attributes, vector<shared_ptr<Node>> children);
    Element(string tagName);
    
    string to_string() override;
    
    
};

    
}


#endif
