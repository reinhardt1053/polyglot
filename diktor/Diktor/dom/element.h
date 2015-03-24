//
//  element.h
//  Diktor
//
//  Created by Massimo Fazzolari on 23/02/15.
//  Copyright (c) 2015 Massimo Fazzolari. All rights reserved.
//

#pragma once

#include "node.h"
#include <string>
#include <map>
#include <vector>
#include <unordered_set>

namespace dom {
    class Element : public Node
    {
    public:
        Element(string tagName, map<string,string> attributes, vector<shared_ptr<Node>> children);
        Element(string tagName);
        
        //Returns the id attribute value assigned to this element
        string id();
        
        //Returns the set of classes assigned to this element
        unordered_set<string> classes();
        
        string to_string() override;
        
    private:
        string _tagName;
        map<string, string> _attributes;
        
    };
}

