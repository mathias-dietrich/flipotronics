//
//  MasterComponent.h
//  Deus
//
//  Created by Mathias Dietrich on 15.07.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef MasterComponent_h
#define MasterComponent_h

#include "Inc.h"
#include "IComponent.h"
#include "HeaderComponent.h"
#include "EventHandler.h"

class MasterComponent : public IComponent, public EventHandler{
    
public:
    
    MasterComponent(){
       
    }
    
    ~MasterComponent(){
          delete headerComponent;
      }
    
    MasterComponent(int width, int height){
        headerComponent = new HeaderComponent();
        headerComponent->handler = this;
        this->width = width;
        this->height = height;
        addAndMakeVisible(headerComponent);
    }
    
    void resizeAll(float prozent) override{
        handler->resizeAll(prozent);
    }
    
    void paint (Graphics& g) override {
            g.fillAll (Colours::green);
    }
    
    void init(int width, int height){
        this->width = width;
        this->height = height;
    }
    
    void setDials() override{
           
    }
    
    void build(Node node) override{
        
    }
    
    void resized() override{
        if(headerComponent==0){
            return;
        }
        headerComponent->setBounds(0,0,width,50);
        for(auto it = std::begin(children); it != std::end(children); ++it) {
            IComponent *c = *it;
            Node n = c->node;
            c->setBounds(n.x,n.y,n.width,n.height);
            c->resized();
            c->setVisible(n.isVisible);
            c->repaint();
        }
    }
    
    HeaderComponent * headerComponent;
    EventHandler * handler;
};

#endif /* MasterComponent_h */
