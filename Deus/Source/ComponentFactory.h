//
//  ComponentFactory.h
//  Deus
//
//  Created by Mathias Dietrich on 16.07.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef ComponentFactory_h
#define ComponentFactory_h

#include "IComponent.h"
#include "IFactory.h"
#include "HeaderComponent.h"
#include "MacroComponent.h"

class ComponentFactory: public IFactory{
public:
    ComponentFactory(){}
    virtual ~ComponentFactory(){
        
    }
    
    IComponent * get(String type){
        if(type == "header"){
            HeaderComponent *c = new HeaderComponent();
            c->factory = this;
            return c;
        }
        if(type == "macro"){
            MacroComponent *c = new MacroComponent();
            c->factory = this;
            return c;
        }
        /*
        if(type == "osc"){
            OscComponent *c = new OscComponent();
            c->factory = this;
            return c;
        }
        if(type == "filter"){
           FilterComponent *c = new FilterComponent();
           c->factory = this;
           return c;
        }
        if(type == "modheader"){
            ModHeaderComponent *c = new ModHeaderComponent();
            c->factory = this;
            return c;
        }
        if(type == "mod"){
            ModSourceComponent *c = new ModSourceComponent();
            c->factory = this;
            return c;
        }
        if(type == "input"){
            InputComponent *c = new InputComponent();
            c->factory = this;
            return c;
        }
        if(type == "amp"){
           AmpComponent *c = new AmpComponent();
           c->factory = this;
           return c;
       }
         */
        return new HeaderComponent();
    }
};

#endif /* ComponentFactory_h */
