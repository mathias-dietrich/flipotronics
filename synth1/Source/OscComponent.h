//
//  OscComponent.h
//  synth1
//
//  Created by Mathias Dietrich on 13.07.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef OscComponent_h
#define OscComponent_h


#include "AbstractComponent.h"
#include "WidgetFactory.h"
#include "Factory.h"

class OscComponent :  public AbstractComponent {
public:
    
    OscComponent(){
        
    }
    
    ~OscComponent(){
       for(auto it = std::begin(children); it != std::end(children); ++it) {
         delete *it;
       }
    }
    
    void paint (Graphics& g) override {
        Rectangle<int> r = getLocalBounds();
        auto width  = r.getWidth();
        auto height  = r.getHeight();
        auto defaultColour = Colours::black;
        g.fillAll (juce::Colours::findColourForName (node.bgColor, defaultColour));
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
               current = factory->get(node.name);
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
            c->resized();
            c->setVisible(node.isVisible);
        }
    }
    
    AbstractComponent *current;
    WidgetFactory widgetFactory;
    Factory * factory;
};


#endif /* OscComponent_h */
