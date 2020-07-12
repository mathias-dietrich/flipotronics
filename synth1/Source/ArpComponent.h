//
//  ArpComonent.h
//  synth1
//
//  Created by Mathias Dietrich on 09.07.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef ArpComonent_h
#define ArpComonent_h

#include "WidgetFactory.h"

class ArpComponent :public AbstractComponent{

   public:
    
    void paint (Graphics& g) override {
         Rectangle<int> r = getLocalBounds();
         auto width  = getLocalBounds().getWidth();
         auto height  = getLocalBounds().getHeight();
         g.fillAll (Colours::yellow);
    }
       
     void resized() override{
  
     }

    
     void setDials() override{
         
     }
    
    void build(Node node) override{
           
       }
    
    WidgetFactory widgetFactory;
};

#endif /* ArpComonent_h */
