//
//  elementnode.cpp
//  Diktor
//
//  Created by Massimo Fazzolari on 24/02/15.
//  Copyright (c) 2015 Massimo Fazzolari. All rights reserved.
//

#include "element.h"
#include <iostream>

namespace dom {
    
    Element::Element(string tag_name, map<string,string> attributes, vector<shared_ptr<Node>> children)
    {
        this->tag_name = tag_name;
        this->attributes = attributes;
        this->children = children;
        
    }
    
    Element::Element(string tag_name)
    {
        this->tag_name = tag_name;
    }
    
    
    string Element::id()
    {
        return attributes["id"];
    }
    
    unordered_set<string> Element::classes()
    {
        unordered_set<string> items;
       
        map<string,string>::const_iterator it = attributes.find("class");
        while (it!=attributes.end())
        {
            items.insert(it->second);
            it++;
        }
        
        return items;
    }
    
    string Element::to_string()
    {
        string result;
        
        //Open tag
        result.append("<");
        result.append(tag_name);
        
        //Attributes
        if (!this->attributes.empty())
        {
            result.append(" ");
            for (auto attribute : this->attributes){
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
            result.append(child->to_string());
        }
        
        //Close tag;
        result.append("</");
        result.append(tag_name);
        result.append(">");
        
        return result;
    }
}