//
//  MacroComponent.h
//  synth1
//
//  Created by Mathias Dietrich on 07.07.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef MacroComponent_h
#define MacroComponent_h

#include "AbstractComponent.h"
#include "MasterPoti.h"
#include "OutputMeter.h"
#include "MasterSwitch.h"
#include "MasterPoti.h"
#include "Poti.h"

class MacroComponent:  public AbstractComponent, public Slider::Listener{

   public:
    
    MacroComponent(){
        for(int i=0; i < 8; i++){
            poti[i].setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag );
            poti[i].setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 100, 20);
            poti[i].setNumDecimalPlacesToDisplay(2);
            poti[i].setName(toString(i));
            poti[i].addListener (this);
            addAndMakeVisible(poti[i]);
            setDials();
        }
    }
    
    ~MacroComponent(){
       for(auto it = std::begin(children); it != std::end(children); ++it) {
         delete *it;
       }
    }
    
    void build(Node node) override{
           
    }
    
    void paint (Graphics& g) override {
         Rectangle<int> r = getLocalBounds();
         auto width  = getLocalBounds().getWidth();
         auto height  = getLocalBounds().getHeight();
         g.fillAll (C_BLACK);
    }
       
     void resized() override{
         for(int i=0; i < 8; i++){
             poti[i].setBounds(120 + i * 150, 0, 60,60);
         }
     }
    
    void sliderValueChanged(Slider *  slider) override {
        int sid = slider->getName().getIntValue();
        int pid = P_MACRO_0 + sid;
        Model::of().par[pid] = slider->getValue();
        setDials();
    }
    
     void setDials() override{
         for(int i=0; i < 8; ++i){
             int pid = P_MACRO_0 + i;
             poti[i].setRange(Model::of().params[pid].minVal,Model::of().params[pid].maxVal,Model::of().params[pid].stepVal);
             poti[i].setValue(Model::of().par[pid],dontSendNotification);
         }
     }
    
private:
    MasterPoti poti[8];
};

#endif /* MacroComponent_h */
