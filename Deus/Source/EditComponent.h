//
//  EditComponent.h
//  Deus
//
//  Created by Mathias Dietrich on 17.07.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef EditComponent_h
#define EditComponent_h

#include "IComponent.h"
#include "MasterPoti.h"
#include "OutputMeter.h"
#include "MasterSwitch.h"
#include "MasterPoti.h"
#include "Poti.h"

#include "WidgetFactory.h"
#include "IFactory.h"
#include "UILoader.h"

class UILoader;

class EditComponent :  public IComponent, public Slider::Listener{
public:
    EditComponent(){
       
    }
    
    ~EditComponent(){
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
        
         g.fillAll (C_RED);
    }
    
    void setDials() override{
            for(auto it = std::begin(widgets); it != std::end(widgets); ++it) {
          //      MasterPoti *p =  (MasterPoti*) *it;
              //  Node *node = p->node;
               // p->setValue(Model::of().par[node.paramId],dontSendNotification);
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
    
    void sliderValueChanged(Slider *  slider) override {
      //  int sid = slider->getName().getIntValue();
       // Model::of().par[sid] = slider->getValue();
        setDials();
    }
    
    void build(Node * node) override{
        for(auto it = std::begin( node->childen); it != std::end( node->childen); ++it) {
            Node *node = *it;
            std::cout << node->name << std::endl;
          
            if(node->type == 0){ //Component
                std::cout << node->name << std::endl;
                current = factory->get(node->name);
                current->node = node;
                current->factory = factory;
                current->eventHandler = eventHandler;
                current->build(node);
                if(node->isVisible){
                    this->addAndMakeVisible(current);
                    current->repaint();

                }else{
                   addChildComponent(current);
                }
                children.push_back(current);
                
               // if(node->xmlFile)
               // Node *n = new Node();
               // uiloader.load(n, node->xmlFile);
               // current->build(n);
            }

        }
       repaint();
    }
    UILoader uiloader;
};

#endif /* EditComponent_h */
