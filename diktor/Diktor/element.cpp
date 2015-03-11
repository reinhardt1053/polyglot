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

Element::Element(string tagName, map<string,string> attributes, vector<Node*> children)
{
    _tagName = tagName;
    _attributes = attributes;
    this->children = children;
    
}

Element::Element(string tagName)
{
    _tagName = tagName;
}

    
ostream& Element::toString(ostream& out) const
{
    //Open tag
    out << '<' << _tagName << '>' << endl;
    
    //Children
    for (auto child : this->children)
    {
        out << *child;
    }
    
    out << "</" << _tagName << '>' << endl;
    //Close tag;
    
    
    return out;
   
}

}