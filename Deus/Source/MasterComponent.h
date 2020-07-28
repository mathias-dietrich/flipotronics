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
#include "ComponentFactory.h"

class MasterComponent : public IComponent, public EventHandler{
    
public:
    
    MasterComponent(){
        factory = new ComponentFactory();
      //  headerComponent.handler = this;
       // addAndMakeVisible(headerComponent);
    }
    
    ~MasterComponent(){
        clearUi();
        delete factory;
    }
    
    void configure()override {
        
    }
    
    void clearUi(){
        for(auto it = std::begin(children); it != std::end(children); ++it) {
             IComponent *c = *it;
            c->clearUi();
            delete c;
        }
        children.clear();
    }
    
    void resizeUi(int prozent) override{
        eventHandler->resizeUi(prozent);
    }
    
    void paint (Graphics& g) override {
        g.fillAll (Colours::black);
    }
    
    void setDials() override{
        for(auto it = std::begin( children); it != std::end(children); ++it) {
            IComponent *c = *it;
            c->setDials();
           }
    }
    
    void build(Node * node) override{
        Node *nodeMaster = node->children.front();
        width = nodeMaster->width;
        height = nodeMaster->height;
        for(auto it = std::begin( nodeMaster->children); it != std::end( nodeMaster->children); ++it) {
            Node *node = *it;
          
            if(node->type == 0){ //Component
                current = factory->get(node->name);
                current->node = node;
                current->factory = factory;
                current->eventHandler = eventHandler;
                if(node->isVisible){
                    this->addAndMakeVisible(current);
                }else{
                    addChildComponent(current);
                }
                children.push_back(current);
                
                if(node->xmlFile.compare("")==0){
                    
                }else{
                    Node *n = new Node();
                    uiloader.load(n, node->xmlFile);
                    current->build(n);
                }
            }
            if(node->type == 1){ // Widget
                current->build(node);
            }
        }
        repaint();
    }
    
    void update()override {
        switch(Model::of()->masterSel){
                
            case mEdit:
                
                break;
            case mLibrary:
                
                break;
            case mPerform:
                
                break;
            case mArp:
                
                break;
            case mSetup:
                
                break;
            case mDebug:
                
                break;
        }
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
    
    UILoader uiloader;
    
    std::map<int, Param> getParams() override{
        return params;
    }
    
    void setParams( std::map<int, Param> params) override{
        this->params = params;
    }
        
    private:
        std::map<int, Param> params;
};

#endif /* MasterComponent_h */
