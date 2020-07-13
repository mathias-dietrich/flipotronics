//
//  Widget.h
//  synth1
//
//  Created by Mathias Dietrich on 12.07.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef Widget_h
#define Widget_h

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
#endif /* Widget_h */
