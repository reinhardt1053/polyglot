//
//  main.cpp
//  Diktor
//
//  Created by Massimo Fazzolari on 02/03/15.
//  Copyright (c) 2015 Massimo Fazzolari. All rights reserved.
//

#include <iostream>
#include "dom/node.h"
#include "dom/element.h"
#include "dom/text.h"
#include "dom/parser.h"
#include "css/parser.h"

using namespace std;

int main(int argc, const char * argv[]) {
    
    //Build the DOM tree programmatically
    
    auto html = make_shared<dom::Element>("html");
    auto body = make_shared<dom::Element>("body");
    auto text = make_shared<dom::Text>("Hello World");
    
    html->children.push_back(body);
    body->children.push_back(text);
    
    cout << html->to_string() << endl;
    
    
    //Parse an html string
    string html_str = "<header><title>Diktor</title></header><body><div id='test'>Hello World</div></body>";
    
    auto root = dom::Parser::parse(html_str);
    
    cout << root->to_string() << endl;
    
    
    //Parse a css string
    string css_str = "h1, h2, h3 { font-family: serif; text-align: center; } p.center { text-align: center; color: #FF03A1; }";
    
    auto stylesheet = css::Parser::parse(css_str);
    
    cout << stylesheet->to_string() << endl;
    
    return 0;
}
