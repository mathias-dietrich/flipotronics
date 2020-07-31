//
//  DebugComponent.h
//  Deus
//
//  Created by Mathias Dietrich on 7/28/20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef DebugComponent_h
#define DebugComponent_h

#include "WidgetFactory.h"
#include "IFactory.h"
#include "UILoader.h"

class UILoader;

class DebugComponent :  public IComponent, public Timer{
    
public:
    DebugComponent(){
        startTimer(200);
    }
    
    ~DebugComponent(){
       for(auto it = std::begin(children); it != std::end(children); ++it) {
         delete *it;
       }
        for(auto it = std::begin(widgets); it != std::end(widgets); ++it) {
          delete *it;
        }
    }
    
    void timerCallback() override{
        repaint();
    }
    
    void paint (Graphics& g) override {
         Rectangle<int> r = getLocalBounds();
         g.fillAll (C_WHITE);
        
         // Debug speed of render
         g.setFont (15.0f);

         // Time taken in the Render Loop
         float taken = Model::of()->timeTaken * 0.000001f;
         if(taken > Core::of()->maxTimeMsec){
          g.setColour (Colours::red);
         }else{
          g.setColour (C_GREENTEXT);
         }
         float cpu = taken / Core::of()->maxTimeMsec * 100.0f;
         g.drawFittedText ("CPU: " +  String(cpu,2) + "%  Taken: " + String(taken,3) + " msec  Max: "
                           + String(Core::of()->maxTimeMsec,3) + " msec", r, Justification::topLeft, 1);

         // Volumes
         g.setColour (C_GREENTEXT);
         g.setFont (15.0f);

       //  r.setY(20);
        // g.drawFittedText ("Peak: " + String(Model::of().sumPeakL), r, Justification::topLeft, 1);

        // r.setY(40);
        // g.drawFittedText ("RMS: " + String(Model::of().sumRMSL,2), r, Justification::topLeft, 1);

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
            std::cout << node->name << std::endl;
          
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
    
    std::map<int, Param> getParams()override{
        return params;
    }
    
    void setParams( std::map<int, Param> params)override{
        this->params = params;
    }
        
    private:
            std::map<int, Param> params;
};
#endif /* DebugComponent_h */
