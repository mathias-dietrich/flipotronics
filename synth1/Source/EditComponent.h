//
//  RootComponent.h
//  synth1
//
//  Created by Mathias Dietrich on 11.07.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef EditComponent_h
#define EditComponent_h

#include "AbstractComponent.h"
#include "ComponentFactory.h"

class EditComponent :  public AbstractComponent {
public:
    
    EditComponent(){
        
    }
    
    ~EditComponent(){
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
           if(node.type == 0){ //Component
               current = componentFactory.get(node.name);
               current->node = node;
               this->addAndMakeVisible(current);
               children.push_back(current);
           }
           if(node.type == 1){ // Widget
               current->build(node);
           }
         }
    }
    
    void resized() override{
        for(auto it = std::begin(children); it != std::end(children); ++it) {
            AbstractComponent *c = *it;
            Node n = c->node;
            c->setBounds(n.x,n.y,n.width,n.height);
        }
    }
    
    AbstractComponent *current;
    ComponentFactory componentFactory;
};

#endif /* EditComponent_h */
