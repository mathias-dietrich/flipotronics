//
//  ComponentFactory.h
//  synth1
//
//  Created by Mathias Dietrich on 11.07.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef ComponentFactory_h
#define ComponentFactory_h

#include "MacroComponent.h"

class ComponentFactory{
public:
    
    AbstractComponent * get(String type){
  
        if(type == "macro"){
            return new MacroComponent();
        }
       
        return new MacroComponent();
    }
};

#endif /* ComponentFactory_h */
