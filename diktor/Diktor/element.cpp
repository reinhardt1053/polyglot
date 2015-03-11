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
    result.append("<");
    result.append(_tagName);
    
    //Attributes
    if (!this->_attributes.empty())
    {
        result.append(" ");
        for (auto attribute : this->_attributes){
            result.append(attribute.first);
            result.append("=\"");
            result.append(attribute.second);
            result.append("\"");
        }
    }
    result.append(">");
    
    
    //Children
    for (auto child : this->children)
    {
        result.append(child->toString());
    }
    
    //Close tag;
    result.append("</");
    result.append(_tagName);
    result.append(">");
    
    return result;
   
}

}