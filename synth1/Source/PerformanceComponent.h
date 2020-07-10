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

class PerformanceComponent:  public AbstractComponent{

   public:
    
    void paint (Graphics& g) override {
         Rectangle<int> r = getLocalBounds();
         auto width  = getLocalBounds().getWidth();
         auto height  = getLocalBounds().getHeight();
         g.fillAll (Colours::black);
    }
       
     void resized() override{
  
     }

    
     void setDials() override{
         
     }
};

#endif /* PerformanceComponent_h */
