//
//  PerformComponent.h
//  Deus
//
//  Created by Mathias Dietrich on 7/28/20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef PerformComponent_h
#define PerformComponent_h

#include "WidgetFactory.h"
#include "IFactory.h"
#include "UILoader.h"

class UILoader;

class PerformComponent :  public IComponent{
    
public:
    PerformComponent(){
       
    }
    
    ~PerformComponent(){
       for(auto it = std::begin(children); it != std::end(children); ++it) {
         delete *it;
       }
        for(auto it = std::begin(widgets); it != std::end(widgets); ++it) {
          delete *it;
        }
    }
    
    void paint (Graphics& g) override {

         auto defaultColour = Colours::black;
         g.fillAll (juce::Colours::findColourForName (node->bgColor, defaultColour));
         g.fillAll(C_YELLOW);
    }
    
    void setDials() override{

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

    void build(Node * node) override{
        for(auto it = std::begin( node->children); it != std::end( node->children); ++it) {
            Node *node = *it;

            if(node->type == 0){ //Component
                std::cout << node->name << std::endl;
                current = factory->get(node->name);
                current->node = node;
                current->factory = factory;
                current->eventHandler = eventHandler;
                //current->build(node);
                if(node->isVisible){
                    this->addAndMakeVisible(current);
                    current->repaint();

                }else{
                   addChildComponent(current);
                }
                children.push_back(current);
                
                if(node->xmlFile.length() > 0){
                    Node *n = new Node();
                    uiloader.load(n, node->xmlFile);
                    current->build(n);
                }
            }

        }
       repaint();
    }
    UILoader uiloader;   
    private:

};
#endif /* PerformComponent_h */
