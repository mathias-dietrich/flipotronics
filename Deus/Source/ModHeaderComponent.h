//
//  ModHeaderComponent.h
//  Deus
//
//  Created by Mathias Dietrich on 7/25/20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef ModHeaderComponent_h
#define ModHeaderComponent_h

#include "IComponent.h"
#include "WidgetFactory.h"
#include "IFactory.h"

class ModHeaderComponent :  public IComponent, public Button::Listener {
public:
    
    ModHeaderComponent(){
        
    }
    
    ~ModHeaderComponent(){
        for(auto it = std::begin(children); it != std::end(children); ++it) {
            delete *it;
        }
        for(auto it = std::begin(widgets); it != std::end(widgets); ++it) {
            delete *it;
        }
    }
    
    void paint (Graphics& g) override {
        Rectangle<float> r = convertRect(getLocalBounds());
               auto width  = r.getWidth();
               //auto height  = r.getHeight();
               
               // Fill
               auto defaultColour = Colours::black;
               g.fillAll (juce::Colours::findColourForName (node->bgColor, defaultColour));
        
               // Border
               g.setColour(C_MODULE_BORDER);
               g.drawRoundedRectangle(r, 13.0f, 5.0f);
               g.fillRoundedRectangle(0,0,width, 10, 15.0f);
               g.fillRect(0.0f,8.0f,width, 12.0f);
              // g.fillRoundedRectangle(0,height-5,width, 5, 15.0f);
               
               //g.setColour(C_MODULE_BG);
               //g.fillRect(2.0f,17.0f,width-4, height - 22);
                
               // Title
               g.setColour(C_MODULE_TITLE);
               g.drawText(node->title, 5,3,200,20,Justification::topLeft, false);
    }
    
    void setDials() override{
       for(auto it = std::begin(widgets); it != std::end(widgets); ++it) {
           //Poti *p =  (Poti*) *it;
          // Node *node = p->node;
          // setPoti(node, p);
          // p->setValue(Model::of().par[node->paramId],dontSendNotification);
       }
    }
    
    void build(Node * node) override{
        for(auto it = std::begin(node->children); it != std::end(node->children); ++it){
              Node *n = *it;
             if(node->name.compare("modview")==1){
               ModView *wc = (ModView *) WidgetFactory::of()->get(n->name);
               wc->node = n;
               addAndMakeVisible(wc);
               wc->setName(toString(n->paramId));
               wc->addListener (this);
               widgets.push_back(wc);
            }
        }
    }
    
    void buttonClicked(Button *  button) override {
        setDials();
    }
    
    void resized() override{
         for(auto it = std::begin(widgets); it != std::end(widgets); ++it) {
            ModView *p =  (ModView*) *it;
            Node *node = p->node;
            p->setBounds(node->x , node->y, node->width,node->height);
            p->setVisible(node->isVisible);
        }
    }

    private:

};
#endif /* ModHeaderComponent_h */
