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
#include "OscComponent.h"
#include "FilterComponent.h"
#include "Factory.h"
#include "ModSourceComponent.h"
#include "ModHeaderComponent.h"
#include "InputComponent.h"
#include "AmpComponent.h"

class ComponentFactory: public Factory{
public:
    ComponentFactory(){}
    ~ComponentFactory(){}
    
    AbstractComponent * get(String type){
        if(type == "macro"){
            MacroComponent *c = new MacroComponent();
            c->factory = this;
            return c;
        }
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
        return new MacroComponent();
    }
};

#endif /* ComponentFactory_h */
