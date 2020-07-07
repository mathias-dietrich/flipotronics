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

class MacroComponent:  public AbstractComponent, public Slider::Listener{

   public:
    
    void paint (Graphics& g) override {
         Rectangle<int> r = getLocalBounds();
         auto width  = getLocalBounds().getWidth();
         auto height  = getLocalBounds().getHeight();
         g.fillAll (Colours::white);
    }
       
     void resized() override{
  
     }
    
    void sliderValueChanged(Slider *  slider) override {
        setDials();
    }
    
    
     void setDials() override{
     }
};

#endif /* MacroComponent_h */
