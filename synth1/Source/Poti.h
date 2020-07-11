//
//  Poti.h
//  synth1
//
//  Created by Mathias Dietrich on 24.06.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef Poti_h
#define Poti_h

class PotiLookAndFeel : public  LookAndFeel_V4{
    public:
    
     PotiLookAndFeel() {
          
     }
    
    Label* createSliderTextBox(Slider& slider) override
    {
        Label* l = LookAndFeel_V2::createSliderTextBox(slider);
        l->setColour(Label::textColourId, Colours::black);
        return l;
    }
    
    void drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos,
                              const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override{
        //BG
        g.setColour (Colour(239,239,239));
        g.fillRect (x, y, width, height + 20);
        
        // Title
        g.setColour (Colour(30,30,30));
        Rectangle<int> rv{x+8,y,width,20};
        g.drawFittedText (title, rv, Justification::centred, 1);
        
        y = y+20;
        height -= 20;
 
        // Image
        g.drawImageWithin(ImageFactory::of().png[ePoti], x+1, y, width-2,height-2, juce::RectanglePlacement::centred, false);
    
        // Circle
        auto radius = jmin (width / 2, height / 2) - 4.0f;
        auto centreX = x + width  * 0.5f;
        auto centreY = y + height * 0.5f;
       // auto rx = centreX - radius;
       //auto ry = centreY - radius;
        //auto rw = radius * 2.0f;
        auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

        // Pointer
        Path p;
        radius -= 11;
        auto pointerLength = (radius) * 0.23f;
        auto pointerThickness = 3.0f;
        p.addRectangle (-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
        p.applyTransform (AffineTransform::rotation (angle).translated (centreX, centreY));
        g.setColour (Colours::black);
        g.fillPath (p);
        
        g.setColour (Colour(239,239,239));
        g.fillRect (x+8, y, 3, height);
        g.setColour (Colour(239,239,239));
        g.fillRect (x+width-11, y, 3, height);
        
         g.setColour (Colour(30,30,30));
        g.drawLine(x ,y,x, y+height-10, 0.5f);
    }
    
     String title;
    
};

class Poti : public Slider {
    
public:
    
    PotiLookAndFeel potiLookAndFeel;
    
    void setTitle(String title){
        potiLookAndFeel.title = title;
    }

     Poti() {
        juce::Slider::setLookAndFeel (&potiLookAndFeel);
        hideTextBox(true);
    }
    
    ~Poti() {
        juce::Slider::setLookAndFeel (nullptr);
     }
    
    void build(Node node) {
           
       }
    
    void setDials() {
           
       }
    
private:
    
};

#endif /* Poti_h */
