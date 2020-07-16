//
//  MacroComponent.h
//  Deus
//
//  Created by Mathias Dietrich on 16.07.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef MacroComponent_h
#define MacroComponent_h


#include "IComponent.h"
#include "MasterPoti.h"
#include "OutputMeter.h"
#include "MasterSwitch.h"
#include "MasterPoti.h"
#include "Poti.h"

#include "WidgetFactory.h"
#include "IFactory.h"

class MacroComponent:  public IComponent, public Slider::Listener{

   public:
    
    MacroComponent(){
       
    }
    
    ~MacroComponent(){
       for(auto it = std::begin(children); it != std::end(children); ++it) {
         delete *it;
       }
        for(auto it = std::begin(widgets); it != std::end(widgets); ++it) {
          delete *it;
        }
    }
    
    void build(Node * node) override{
        for(auto it = std::begin(node->childen); it != std::end(node->childen); ++it){
            Node *macro = *it;
             for(auto it = std::begin(macro->childen); it != std::end(macro->childen); ++it){
                  Node *n = *it;
                 if(node->name.compare("masterpoti")==1){
                   MasterPoti *wc = (MasterPoti *) WidgetFactory::of()->get(n->name);
                   wc->node = n;
                   addAndMakeVisible(wc);
                   wc->setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag );
                   wc->setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 100, 20);
                   wc->setNumDecimalPlacesToDisplay(2);
                   wc->setName(toString(n->paramId));
                   wc->addListener (this);
                   wc->setRange(0,1,0.01f);
                   widgets.push_back(wc);
                }
             }
        }
    }
    
    void paint (Graphics& g) override {
        // Rectangle<int> r = getLocalBounds();
       //  auto width  = r.getWidth();
        // auto height  = r.getHeight();
         auto defaultColour = Colours::black;
         g.fillAll (juce::Colours::findColourForName (node->bgColor, defaultColour));
    }
       
     void resized() override{
         for(auto it = std::begin(widgets); it != std::end(widgets); ++it) {
             MasterPoti *p =  (MasterPoti*) *it;
             Node * node = p->node;
             p->setBounds(node->x , node->y, node->width,node->height);
             p->setVisible(node->isVisible);
         }
     }
    
    void sliderValueChanged(Slider *  slider) override {
      //  int sid = slider->getName().getIntValue();
       // Model::of().par[sid] = slider->getValue();
        setDials();
    }
    
     void setDials() override{
         for(auto it = std::begin(widgets); it != std::end(widgets); ++it) {
       //      MasterPoti *p =  (MasterPoti*) *it;
           //  Node *node = p->node;
            // p->setValue(Model::of().par[node.paramId],dontSendNotification);
         }
     }
    
private:

};


#endif /* MacroComponent_h */