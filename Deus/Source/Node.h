//
//  Node.h
//  Deus
//
//  Created by Mathias Dietrich on 8/1/20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef Node_h
#define Node_h

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
    float minValue;
    float maxValue;
    float step;
    E_UnitType unitType;
    
    void clearAll(){
        for(auto it = std::begin(children); it != std::end(children); ++it) {
           Node *n = *it;
           n->clearAll();
        }
        children.clear();
    }
};

#endif /* Node_h */
