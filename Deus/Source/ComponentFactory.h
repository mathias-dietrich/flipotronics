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
#include "LibraryComponent.h"
#include "ArpComponent.h"
#include "SetupComponent.h"
#include "DebugComponent.h"
#include "PerformComponent.h"

class DeusAudioProcessor;

class ComponentFactory: public IFactory{
public:
    ComponentFactory(){}
    virtual ~ComponentFactory(){
        
    }
    
    IComponent * get(String type){
        if(type == "header"){
            auto *c = new HeaderComponent();
            c->factory = this;
            return c;
        }
        if(type == "macro"){
            auto *c = new MacroComponent();
            c->factory = this;
            return c;
        }
      
        if(type == "edit"){
            auto *c = new EditComponent();
            c->factory = this;
            return c;
        }
        if(type == "input"){
             auto *c = new InputComponent();
             c->factory = this;
             return c;
         }
        if(type == "keyboard"){
            auto *c = new KeyboardComponent(processor);
            c->factory = this;
            return c;
        }
       
        if(type == "osc"){
            auto *c = new OscComponent();
            c->factory = this;
            return c;
        }
        
        if(type == "filter"){
           auto *c = new FilterComponent();
           c->factory = this;
           return c;
        }
        
        if(type == "amp"){
          auto *c = new AmpComponent();
          c->factory = this;
          return c;
        }
        
        if(type == "modheader"){
            auto *c = new ModHeaderComponent();
            c->factory = this;
            return c;
        }

        if(type == "mod"){
            auto *c = new ModComponent();
            c->factory = this;
            return c;
        }
        if(type == "modselector"){
            auto *c = new ModSelector();
            c->factory = this;
            return c;
        }
        if(type == "library"){
           auto *c = new LibraryComponent();
           c->factory = this;
           return c;
        }
        if(type == "arp"){
           auto *c = new ArpComponent();
           c->factory = this;
           return c;
        }
        if(type == "setup"){
           auto *c = new SetupComponent();
           c->factory = this;
           return c;
        }
        if(type == "debug"){
           auto *c = new DebugComponent();
           c->factory = this;
           return c;
        }
        if(type == "perform"){
           auto *c = new PerformComponent();
           c->factory = this;
           return c;
        }
        return new HeaderComponent();
    }
    
    DeusAudioProcessor * processor;
};

#endif /* ComponentFactory_h */
