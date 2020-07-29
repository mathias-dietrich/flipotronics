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
       Param p;
       p.module = mMacro;
       p.valF = 0.5;
       p.type = uFloat;
       params[0] = params[1] = params[2] = params[3] =params[4] =params[5] =params[6] =params[7] =params[8] =params[9] =params[10] =params[11] =params[12] =params[13] =params[14] =params[15] = p;

       params[0].pid = 0;
       params[1].pid = 1;
       params[2].pid = 2;
       params[3].pid = 3;
       params[4].pid = 4;
       params[5].pid = 5;
       params[6].pid = 6;
       params[7].pid = 7;
       params[8].pid = 8;
       params[9].pid = 9;
       params[10].pid = 10;
       params[11].pid = 11;
       params[12].pid = 12;
       params[13].pid = 13;
       params[14].pid = 14;
       params[15].pid = 15;
        
        params[0].minVal = 0;
        params[1].minVal = 0;
        params[2].minVal = 0;
        params[3].minVal = 0;
        params[4].minVal = 0;
        params[5].minVal = 0;
        params[6].minVal = 0;
        params[7].minVal = 0;
        params[8].minVal = 0;
        params[9].minVal = 0;
        params[10].minVal = 0;
        params[11].minVal = 0;
        params[12].minVal = 0;
        params[13].minVal = 0;
        params[14].minVal = 0;
        params[15].minVal = 0;
        
        params[0].maxVal = 1;
        params[1].maxVal = 1;
        params[2].maxVal = 1;
        params[3].maxVal = 1;
        params[4].maxVal = 1;
        params[5].maxVal = 1;
        params[6].maxVal = 1;
        params[7].maxVal = 1;
        params[8].maxVal = 1;
        params[9].maxVal = 1;
        params[10].maxVal = 1;
        params[11].maxVal = 1;
        params[12].maxVal = 1;
        params[13].maxVal = 1;
        params[14].maxVal = 1;
        params[15].maxVal = 1;
        
        params[0].stepVal = 0.1;
        params[1].stepVal = 0.1;
        params[2].stepVal = 0.1;
        params[3].stepVal = 0.1;
        params[4].stepVal = 0.1;
        params[5].stepVal = 0.1;
        params[6].stepVal = 0.1;
        params[7].stepVal = 0.1;
        params[8].stepVal = 0.1;
        params[9].stepVal = 0.1;
        params[10].stepVal = 0.1;
        params[11].stepVal = 0.1;
        params[12].stepVal = 0.1;
        params[13].stepVal = 0.1;
        params[14].stepVal = 0.1;
        params[15].stepVal = 0.1;

       params[0].name = "0";
       params[1].name = "1";
       params[2].name = "2";
       params[3].name = "3";
       params[4].name = "4";
       params[5].name = "5";
       params[6].name = "6";
       params[7].name = "7";
       params[8].name = "8";
       params[9].name = "9";
       params[10].name = "10";
       params[11].name = "11";
       params[12].name = "12";
       params[13].name = "13";
       params[14].name = "14";
       params[15].name = "15";
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
        for(auto it = std::begin(node->children); it != std::end(node->children); ++it){
            Node *macro = *it;
             for(auto it = std::begin(macro->children); it != std::end(macro->children); ++it){
                  Node *n = *it;
                 if(node->name.compare("masterpoti")==1){
                   MasterPoti *wc = (MasterPoti *) WidgetFactory::of()->get(n->name);
                   wc->node = n;
                   addAndMakeVisible(wc);
                   wc->setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag );
                   wc->setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, false, 50, 15);
                   wc->setNumDecimalPlacesToDisplay(2);
                   wc->setName(toString(n->paramId));
                   wc->setTitle("Macro");
                   wc->addListener (this);
                   wc->setRange(0,1,0.01f);
                   widgets.push_back(wc);
                }
             }
        }
        setDials();
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
        int sid = slider->getName().getIntValue();
        Core::of()->update(mMacro, sid, slider->getValue());
        setDials();
    }
    
     void setDials() override{
         for(auto it = std::begin(widgets); it != std::end(widgets); ++it) {
             MasterPoti *p =  (MasterPoti*) *it;
             Node *node = p->node;
             Param pr = Model::of()->getParam(node->module, node->paramId);
             p->setValue(pr.valF);
             p->setRange(pr.minVal, pr.maxVal, pr.stepVal);
         }
     }

    std::map<int, Param> getParams() override{
        return params;
    }
    
    void setParams( std::map<int, Param> params) override{
        this->params = params;
    }
    
    int getParamCount() override{
           return 16;
    }
    
private:
        std::map<int, Param> params;
};


#endif /* MacroComponent_h */
