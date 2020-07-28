//
//  IWidget.h
//  Deus
//
//  Created by Mathias Dietrich on 15.07.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef IWidget_h
#define IWidget_h

#include <JuceHeader.h>
#include "Inc.h"

struct Node{
    int width;
    int height;
    int x;
    int y;
    String name;
    std::vector<Node*> children;
    int paramId;
    E_Module module;
    int type;
    String bgColor;
    bool isVisible;
    String title;
    String xmlFile;
    
    void clearAll(){
        for(auto it = std::begin(children); it != std::end(children); ++it) {
           Node *n = *it;
           n->clearAll();
        }
        children.clear();
    }
};

class Widget{
public:
    
    Widget(){
        
    }
    
     virtual ~Widget(){
        
    }
    
    virtual void setDials() = 0;
    
    Node * node;
};

#endif /* IWidget_h */
