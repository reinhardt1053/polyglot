//
//  builder.cpp
//  Diktor
//
//  Created by Massimo Fazzolari on 23/03/15.
//  Copyright (c) 2015 Massimo Fazzolari. All rights reserved.
//

#include "builder.h"
#include "css/selector.h"

namespace layout {
    bool Builder::matches(shared_ptr<dom::Element> elem, shared_ptr<css::SimpleSelector> selector)
    {
        //The selector applies to a specific tag name and this Element has a different tag name
        if (selector->tag_name != ""  &&
            selector->tag_name != "*" &&
            selector->tag_name != elem->tag_name)
        {
            return false;
        }
        
        //The selector applies to a specific id and this Element has a different id
        if (selector->id != "" &&
            selector->id != elem->id())
        {
            return false;
        }
        
        auto elem_classes = elem->classes();
        
        //Does the element has assigned a class?
        auto has_class = [elem_classes](string class_name) {
            auto pos = elem_classes.find(class_name);
            return  pos != elem_classes.end();
        };
        
        //The selector applies to a set of classes and one of these classes is not assigned to the Element
        auto selector_classes = selector->classes;
        auto pos = find_if(selector_classes.begin(), selector_classes.end(), has_class);
        if (pos != selector_classes.end())
        {
            return false;
        }
        
        return true;
    }
    
    // If rule matches elem, return a MatchedRule, otherwise return nullptr
    shared_ptr<MatchedRule> Builder::match_rule(shared_ptr<dom::Element> elem,  shared_ptr<css::Rule> rule)
    {
        for (auto selector : rule->selectors)
        {
            auto simple_selector = dynamic_pointer_cast<css::SimpleSelector>(selector);
            if (matches(elem, simple_selector))
            {
                auto matched_rule = make_shared<MatchedRule>();
                matched_rule->rule = rule;
                matched_rule->specificity = simple_selector->specificity();
                return matched_rule;
            }
        }
        return nullptr;
    }
    
    
    
}