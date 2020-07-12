//
//  Poti.h
//  synth1
//
//  Created by Mathias Dietrich on 23.06.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef PitchWheel_h
#define PitchWheel_h

#include <JuceHeader.h>
#include "Widget.h"

class PitchWheelLookAndFeel : public  LookAndFeel_V4{
    public:
    
     PitchWheelLookAndFeel() {
          
     }
    
    void drawLinearSlider (Graphics& g, int x, int y, int width, int height,float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle style, Slider& slider) override{
        g.setColour(juce::Colours::darkgrey);
        g.fillRect(x,y,width,height);
        g.setColour(juce::Colours::lightgrey);
        for(int i =0; i < height; i=i+5){
            g.drawLine(x, y + i,x + width, y + i, 0.2);
        }
        g.setColour(juce::Colours::mintcream);
        g.fillRect(x,int(sliderPos-5),width,10);
        g.setColour(juce::Colours::darkgrey);
        g.drawLine(x,int(sliderPos),width,int(sliderPos),1.2);
        g.setColour(juce::Colours::white);
        g.drawLine(x+2,int(sliderPos)-1,width-4,int(sliderPos)-1,0.2);
    }
};

class PitchWheel : public Slider {
    
public:
    PitchWheelLookAndFeel pitchWheelLookAndFeel;
    
     PitchWheel() {
         pitchWheelLookAndFeel.setColour (Slider::thumbColourId, Colours::blue);
         this->setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
         this->hideTextBox (true)    ;
         juce::Slider::setLookAndFeel (&pitchWheelLookAndFeel);
    }
    
    ~PitchWheel() {
       juce::Slider::setLookAndFeel (nullptr);
     }
    
    void setDials() {
        
    }
    
   // void resized() {
              //setBounds(node.x, node.y, node.width, node.height);
       //}

private:
    
};

#endif /* Poti_h */
