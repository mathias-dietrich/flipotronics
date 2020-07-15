//
//  IWidget.h
//  Deus
//
//  Created by Mathias Dietrich on 15.07.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef IWidget_h
#define IWidget_h

struct Node{
    int width;
    int height;
    int x;
    int y;
    String name;
    std::vector<Node> childen;
    int paramId;
    int type;
    String bgColor;
    bool isVisible;
    String title;
};

class Widget{
public:
    
    Widget(){
        
    }
    
     virtual ~Widget(){
        
    }
    
    virtual void setDials() = 0;
    
    Node node;
};

#endif /* IWidget_h */
