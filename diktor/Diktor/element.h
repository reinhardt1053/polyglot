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

namespace DOM {

class Element : public Node
{
private:
    string tagName;
    map<string, string> attributes;
    
protected:
    ostream& toString(ostream& out) const override;
    
public:
    Element(string tagName, map<string,string> attributes, vector<Node*> children);
    Element(string tagName);
    
};

    
}


#endif
