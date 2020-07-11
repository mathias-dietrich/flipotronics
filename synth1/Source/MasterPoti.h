//
//  MasterPoti.h
//  synth1
//
//  Created by Mathias Dietrich on 28.06.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef MasterPoti_h
#define MasterPoti_h

class MasterPotiLookAndFeel : public  LookAndFeel_V4{
    public:
    
     MasterPotiLookAndFeel() {
          
     }

    
    void drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos,
                              const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override{
 
        // Image
        g.drawImageWithin(ImageFactory::of().png[ePotiMaster], x+1, y, width-2,height-2, juce::RectanglePlacement::centred, false);
    
        // Circle
        auto radius = jmin (width / 2, height / 2) - 4.0f;
        auto centreX = x + width  * 0.5f;
        auto centreY = y + height * 0.5f;
        auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

        // Pointer
        Path p;
        radius -= 0;
        auto pointerLength = (radius) * 0.23f;
        auto pointerThickness = 4.0f;
        p.addRectangle (-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
        p.applyTransform (AffineTransform::rotation (angle).translated (centreX, centreY));
        g.setColour (Colours::black);
        g.fillPath (p);
    }
};

class MasterPoti : public Slider{
    
public:
    
    MasterPotiLookAndFeel potiLookAndFeel;

   
    MasterPoti() {
      //using juce::Component::Slider...;
        
         juce::Slider::setLookAndFeel (&potiLookAndFeel);
          hideTextBox(true);
    }
    
    ~MasterPoti() {
        // using juce::Component::setLookAndFeel;
        juce::Slider::setLookAndFeel (nullptr);
     }
    
    void build(Node node) {
           
       }
    
    void setDials(){
        
    }
    
private:
    
};

#endif /* MasterPoti_h */
