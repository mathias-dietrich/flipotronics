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
#include "EditComponent.h"
#include "InputComponent.h"
#include "KeyboardComponent.h"
#include "PluginProcessor.h"
#include "OscComponent.h"
#include "FilterComponent.h"
#include "AmpComponent.h"
#include "ModHeaderComponent.h"
#include "ModComponent.h"
#include "ModSelector.h"

class DeusAudioProcessor;

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
      
        if(type == "edit"){
            EditComponent *c = new EditComponent();
            c->factory = this;
            return c;
        }
        if(type == "input"){
             InputComponent *c = new InputComponent();
             c->factory = this;
             return c;
         }
        if(type == "keyboard"){
            KeyboardComponent *c = new KeyboardComponent(processor);
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
        
        if(type == "amp"){
              AmpComponent *c = new AmpComponent();
              c->factory = this;
              return c;
        }
        
        if(type == "modheader"){
            ModHeaderComponent *c = new ModHeaderComponent();
            c->factory = this;
            return c;
        }

        if(type == "mod"){
            ModComponent *c = new ModComponent();
            c->factory = this;
            return c;
        }
        if(type == "modselector"){
            ModSelector *c = new ModSelector();
            c->factory = this;
            return c;
        }
        
        
        return new HeaderComponent();
    }
    
    DeusAudioProcessor * processor;
};

#endif /* ComponentFactory_h */
