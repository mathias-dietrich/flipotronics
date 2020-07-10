//
//  SetupComponent.h
//  synth1
//
//  Created by Mathias Dietrich on 09.07.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef SetupComponent_h
#define SetupComponent_h

class SetupComponent:  public AbstractComponent{

   public:
    
    void paint (Graphics& g) override {
         Rectangle<int> r = getLocalBounds();
         auto width  = getLocalBounds().getWidth();
         auto height  = getLocalBounds().getHeight();
         g.fillAll (Colours::maroon);
    }
       
     void resized() override{
  
     }

    
     void setDials() override{
         
     }
};

#endif /* SetupComponent_h */
