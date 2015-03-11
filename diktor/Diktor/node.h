//
//  dom.h
//  Diktor
//
//  Created by Massimo Fazzolari on 16/02/15.
//  Copyright (c) 2015 Massimo Fazzolari. All rights reserved.
//

#ifndef NODE_H
#define NODE_H

#include <vector>

using namespace std;

namespace DOM {
    
    class Node {
    private:
        friend ostream& operator<<(ostream& out, const Node& node);
    protected:
        virtual ostream& toString(ostream& out) const = 0;
        
    public:
        vector<Node*> children;
    };
    
}
#endif
