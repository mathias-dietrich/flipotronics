//
//  RootComponent.h
//  synth1
//
//  Created by Mathias Dietrich on 11.07.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef RootComponent_h
#define RootComponent_h

#include "ComponentFactory.h"

class RootComponent :  public AbstractComponent {
public:
    
    RootComponent(){
        
    }
    
    ~RootComponent(){
       for(auto it = std::begin(children); it != std::end(children); ++it) {
         delete *it;
       }
    }
    
    void paint (Graphics& g) override {
            Rectangle<int> r = getLocalBounds();
            auto width  = getLocalBounds().getWidth();
            auto height  = getLocalBounds().getHeight();
            g.fillAll (C_BLACK);
       }
    
    void setDials() override{
        for(auto it = std::begin(children); it != std::end(children); ++it) {
          auto c = *it;
            c->setDials();
        }
    }
    
    void build(Node node) override{
       for(auto it = std::begin( node.childen); it != std::end( node.childen); ++it) {
           Node node = *it;
           AbstractComponent *c = componentFactory.get(node.type);
           this->addAndMakeVisible(c);
           children.push_back(c);
         }
    }
    
    void resized() override{
        for(auto it = std::begin(children); it != std::end(children); ++it) {
          auto c = *it;
            c->setBounds(0,0,0,0);
        }
    }
    
    ComponentFactory componentFactory;
};

#endif /* RootComponent_h */
