//
//  HeaderComponent.h
//  synth1
//
//  Created by Mathias Dietrich on 28.06.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef HeaderComponent_h
#define HeaderComponent_h

#include "AbstractComponent.h"

class HeaderComponent:  public AbstractComponent{
   public:
   
    HeaderComponent () {

    }
   
    ~HeaderComponent () {
        
    }
    
     void paint (Graphics& g) override{
        Rectangle<int> r = getLocalBounds();
        auto width  = getLocalBounds().getWidth();
        auto height  = getLocalBounds().getHeight();
        
        g.fillAll (Colours::black);

        r.setX(5);
        r.setY(5);
        r.setWidth(100);
        r.setHeight(45);
        g.setColour(C_BRANDTITLE);
        Font f = fontLoader.getAntaro();
        f.setHeight(40.0f);
        f.setBold(true);
        g.setFont(f);
        g.drawFittedText (PRODUCTNAME, r, Justification::topLeft, 1);
         
         f.setHeight(11.0f);
         f.setBold(false);
         f.setItalic(true);
         g.setFont(f);
         g.drawFittedText (COMPANYNAME, r, Justification::bottomRight, 1);
     }
    
    void resized() override{
           
    }
    
private:
        FontLoader fontLoader;
    
};
#endif /* HeaderComponent_h */
