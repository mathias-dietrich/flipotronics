//
//  MasterPoti.h
//  Deus
//
//  Created by Mathias Dietrich on 15.07.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef MasterPoti_h
#define MasterPoti_h

#include "IWidget.h"
#include "Func.h"

class MasterPotiLookAndFeel : public  LookAndFeel_V4{
    public:
    
     MasterPotiLookAndFeel() {
    
     }

    void drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos,
                              const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override{
 
        if(showTitle){ // Macro

            // Title
            g.setColour (Colour(200,200,200));
            Rectangle<int> rv{x,y,width,10};
            g.drawFittedText (title, rv, Justification::centredTop, 1);

            y += 12;
            int circeSize = 30;
            g.drawImageWithin(ImageFactory::of().png[ePotiMaster], x+10, y, circeSize,circeSize, juce::RectanglePlacement::centred, false);
            // Circle
            auto radius = jmin (width / 2, width / 2) ;
            auto centreX = x + width  * 0.5f;
            auto centreY = y + width * 0.5f - 10;
            auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

            // Pointer
            Path p;
            radius -= 10;
            auto pointerLength = (radius) * 0.4f;
            auto pointerThickness = 4.0f;
            p.addRectangle (-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
            p.applyTransform (AffineTransform::rotation (angle).translated (centreX, centreY));
            g.setColour (Colours::black);
            g.fillPath (p);
            
            g.setColour (Colour(200,200,200));
            Rectangle<int> rvv{x,y+30,width,20};
           g.drawFittedText (format(sliderPos,2), rvv, Justification::centredTop, 1);
            
        }else{ // Master
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
            auto pointerLength = (radius) * 0.24f;
            auto pointerThickness = 4.0f;
            p.addRectangle (-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
            p.applyTransform (AffineTransform::rotation (angle).translated (centreX, centreY));
            g.setColour (Colours::black);
            g.fillPath (p);
        }
    }
    
    bool showTitle = false;
    String title;
};

class MasterPoti : public Slider, public Widget{
    
public:
  
    MasterPotiLookAndFeel potiLookAndFeel;

    MasterPoti() {
        juce::Slider::setLookAndFeel (&potiLookAndFeel);
        hideTextBox(true);
    }
    
    ~MasterPoti() {
        juce::Slider::setLookAndFeel (nullptr);
     }
    
    void showTitle(){
        hideTextBox(false);
        potiLookAndFeel.showTitle = true;
    }
    void setTitle(String title){
        showTitle();
        potiLookAndFeel.title = title;
    }
    
    void setDials() override{
       
    }
    
private:
    
};

#endif /* MasterPoti_h */
