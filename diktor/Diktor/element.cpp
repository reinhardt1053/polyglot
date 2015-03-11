//
//  elementnode.cpp
//  Diktor
//
//  Created by Massimo Fazzolari on 24/02/15.
//  Copyright (c) 2015 Massimo Fazzolari. All rights reserved.
//

#include "element.h"
#include <iostream>

namespace DOM {

Element::Element(string tagName, map<string,string> attributes, vector<shared_ptr<Node>> children)
{
    _tagName = tagName;
    _attributes = attributes;
    this->children = children;
    
}

Element::Element(string tagName)
{
    _tagName = tagName;
}

    
string Element::toString()
{
    string result;
    
    //Open tag
    result.push_back('<');
    result.append(_tagName);
    result.push_back('>');
    
    
    //Children
    for (auto child : this->children)
    {
        result.append(child->toString());
    }
    
    //Close tag;
    result.append("</");
    result.append(_tagName);
    result.push_back('>');
    
    return result;
   
}

}