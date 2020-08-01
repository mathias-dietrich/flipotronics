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
