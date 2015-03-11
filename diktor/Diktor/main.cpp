//
//  main.cpp
//  Diktor
//
//  Created by Massimo Fazzolari on 02/03/15.
//  Copyright (c) 2015 Massimo Fazzolari. All rights reserved.
//

#include <iostream>
#include "node.h"
#include "element.h"
#include "text.h"
#include "parser.h"

using namespace std;

int main(int argc, const char * argv[]) {
    
    
    DOM::Element html("html");
    DOM::Element body("body");
    DOM::Text text("Hello World");
    
    html.children.push_back(&body);
    body.children.push_back(&text);
    
    cout << html << endl;
    
    return 0;
}
