//
//  EventHandler.h
//  Deus
//
//  Created by Mathias Dietrich on 15.07.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef EventHandler_h
#define EventHandler_h

class EventHandler{
public:
     virtual  ~EventHandler(){
     }
    
     virtual void resizeUi(int sel) = 0;
     virtual void update() = 0;
    
    virtual void configure() = 0;
};

#endif /* EventHandler_h */
