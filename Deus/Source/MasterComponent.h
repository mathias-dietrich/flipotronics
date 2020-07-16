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
#include "UILoader.h"

class MasterComponent : public IComponent, public EventHandler{
    
public:
    
    MasterComponent(){
      //  headerComponent.handler = this;
       // addAndMakeVisible(headerComponent);
    }
    
    ~MasterComponent(){
            for(auto it = std::begin(children); it != std::end(children); ++it) {
                 IComponent *c = *it;
                delete c;
            }
    }
    
    void resizeAll(float prozent) override{
        handler->resizeAll(prozent);
    }
    
    void paint (Graphics& g) override {
        g.fillAll (Colours::green);
        Image img = ImageFactory::of().get("header.png");
    }
    
    void setDials() override{
           
    }
    
    void build(Node * node) override{
        Node *nodeMaster = node->childen.front();
        width = nodeMaster->width;
        height = nodeMaster->height;
        for(auto it = std::begin( nodeMaster->childen); it != std::end( nodeMaster->childen); ++it) {
            Node *node = *it;
          
            if(node->type == 0){ //Component
                current = factory->get(node->name);
                current->node = node;
                current->factory = factory;
                if(node->isVisible){
                    this->addAndMakeVisible(current);
                }else{
                    addChildComponent(current);
                }
                children.push_back(current);
                Node *n = new Node();
                uiloader.load(n, node->xmlFile);
                current->build(n);
            }
            if(node->type == 1){ // Widget
                current->build(node);
            }
        }
        repaint();
    }
    
    void resized() override{
        for(auto it = std::begin(children); it != std::end(children); ++it) {
            IComponent *c = *it;
            Node *n = c->node;
            c->setBounds(n->x,n->y,n->width,n->height);
            c->resized();
            c->setVisible(n->isVisible);
            c->repaint();
        }
    }
    
    EventHandler * handler;
    UILoader uiloader;
};

#endif /* MasterComponent_h */
