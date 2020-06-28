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
#include "MasterPoti.h"
#include "OutputMeter.h"

class HeaderComponent:  public AbstractComponent, public Slider::Listener{
   public:
   
    HeaderComponent () {
        potiMasterVol.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag );
        potiMasterVol.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, false, 100, 20);
        potiMasterVol.addListener (this);
        potiMasterVol.setRange(0,1,0.01);
        potiMasterVol.setValue(0.5);
        addAndMakeVisible(potiMasterVol);
        addAndMakeVisible(outputMeter);
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
        Rectangle<int> r = getLocalBounds();
        auto width  = getLocalBounds().getWidth();
        auto height  = getLocalBounds().getHeight();
        potiMasterVol.setBounds(width-80,6,40,40);
        outputMeter.setBounds(width-40,0,40,50);
        
    }
    
     void sliderValueChanged(Slider *  slider) override {
     }
    
private:
        FontLoader fontLoader;
        MasterPoti potiMasterVol;
        OutputMeter outputMeter;
    
};
#endif /* HeaderComponent_h */
