//
//  Poti.h
//  synth1
//
//  Created by Mathias Dietrich on 23.06.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef Poti_h
#define Poti_h

#include <JuceHeader.h>


class PotiLookAndFeel : public  LookAndFeel_V4{
    public:
    
     PotiLookAndFeel() {
          
     }
    
    void drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos,
                              const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) {

    }
    

    void drawLinearSlider (Graphics& g, int x, int y, int width, int height,float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle style, Slider& slider){
        g.setColour(juce::Colours::black);
        g.fillRect(x,y,width,height);
        g.setColour(juce::Colours::lightgrey);
        for(int i =0; i < height; i=i+5){
            g.drawLine(x, y + i,x + width, y + i, 0.2);
        }
        g.setColour(juce::Colours::lightblue);
        g.fillRect(x,int(sliderPos-5),width,10);
        g.setColour(juce::Colours::darkgrey);
        g.drawLine(x,int(sliderPos),width,int(sliderPos),1.2);
        g.setColour(juce::Colours::white);
        g.drawLine(x+2,int(sliderPos)-1,width-4,int(sliderPos)-1,0.2);
    }
};

class PitchWheel : public Slider{
    
public:
    
    PotiLookAndFeel potiLookAndFeel;
    
     PitchWheel() {
        potiLookAndFeel.setColour (Slider::thumbColourId, Colours::blue);
        this->setLookAndFeel (&potiLookAndFeel);
    }
    
    ~PitchWheel() {
        setLookAndFeel (nullptr);
     }
    
    void drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos,
                           const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) {

    }
    

    
private:
};

#endif /* Poti_h */
