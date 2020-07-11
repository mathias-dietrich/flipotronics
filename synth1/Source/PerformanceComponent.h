//
//  PerformanceComponent.h
//  synth1
//
//  Created by Mathias Dietrich on 09.07.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef PerformanceComponent_h
#define PerformanceComponent_h

#include "AbstractComponent.h"
#include "MasterPoti.h"
#include "OutputMeter.h"
#include "MasterSwitch.h"
#include "MasterPoti.h"
#include "VoiceSelector.h"
#include "XYPad.h"
#include "MacroComponent.h"

class PerformanceComponent : public AbstractComponent{

   public:
   
    PerformanceComponent(){
         addAndMakeVisible (voiceSelector);
         addAndMakeVisible (xYPad);
         addAndMakeVisible (macroComponent);
    }
    
    void paint (Graphics& g) override {
         Rectangle<int> r = getLocalBounds();
         auto width  = r.getWidth();
         auto height  = r.getHeight();
         g.fillAll (Colours::black);
    }
    
    void build(Node node) override{
           
       }
       
    void resized() override {
        Rectangle<int> r = getLocalBounds();
        auto width  = r.getWidth();
        auto height  = r.getHeight();
        macroComponent.setBounds(10,10,width-20,70);
        
        int padSize = 531;
        int frame = (width - padSize*2) / 3;
        voiceSelector.setBounds(frame,85,padSize,padSize);
        xYPad.setBounds(2*frame+padSize,85,padSize,padSize);
    }
    
    void setDials() override {
        voiceSelector.setDials();
        xYPad.setDials();
        macroComponent.setDials();
    }
    
    VoiceSelector voiceSelector;
    XYPad xYPad;
    MacroComponent macroComponent;
};

#endif /* PerformanceComponent_h */
