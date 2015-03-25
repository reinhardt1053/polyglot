//
//  builder.h
//  Diktor
//
//  Created by Massimo Fazzolari on 23/03/15.
//  Copyright (c) 2015 Massimo Fazzolari. All rights reserved.
//

#pragma once

#include "layout/frame.h"
#include "dom/node.h"
#include "dom/element.h"
#include "css/stylesheet.h"
#include "css/rule.h"

namespace layout {
    
    class MatchedRule
    {
    public:
        unsigned int specificity;
        shared_ptr<css::Rule> rule;
    };
    
    class Builder
    {
    public:
        shared_ptr<Frame> build(shared_ptr<dom::Node> root, shared_ptr<css::Stylesheet> stylesheet);
    private:
        bool matches(shared_ptr<dom::Element> elem, shared_ptr<css::SimpleSelector> selector);
        shared_ptr<MatchedRule> match_rule(shared_ptr<dom::Element> elem,  shared_ptr<css::Rule> rule);
    };

}