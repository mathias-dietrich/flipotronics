//
//  LibraryComponent.h
//  synth1
//
//  Created by Mathias Dietrich on 09.07.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef LibraryComponent_h
#define LibraryComponent_h

class LibraryComponent:  public AbstractComponent{

   public:
    
    void paint (Graphics& g) override {
         Rectangle<int> r = getLocalBounds();
         auto width  = getLocalBounds().getWidth();
         auto height  = getLocalBounds().getHeight();
         g.fillAll (Colours::darkgreen);
    }
       
     void resized() override{
  
     }

    
     void setDials() override{
         
     }
};

#endif /* LibraryComponent_h */
