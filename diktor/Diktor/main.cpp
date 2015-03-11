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
    
    /*
    
    //Build the DOM tree programmatically

    auto root = make_shared<DOM::Element>("html");
    auto body = make_shared<DOM::Element>("body");
    auto text = make_shared<DOM::Text>("Hello World");
    
    root->children.push_back(body);
    body->children.push_back(text);
    
    cout << root->toString() << endl;
    */
    
    
    //Parse an html string (No root test)
    string html = "<header><title>Diktor</title></header><body>Hello World</body>";
    Parser parser;
    auto root = parser.parse(html);
    
    cout << root->toString() << endl;
    
    
    return 0;
}
