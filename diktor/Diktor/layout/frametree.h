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

namespace layout {
    class FrameTree
    {
    public:
        Frame build(shared_ptr<dom::Node> root, shared_ptr<css::Stylesheet> stylesheet);
    private:
        bool matches(dom::Element elem, css::Selector selector);
    };

}