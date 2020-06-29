//
//  ViewMeterComponent.h
//  synth1
//
//  Created by Mathias Dietrich on 27.06.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef ViewMeterComponent_h
#define ViewMeterComponent_h

#include <math.h>
#define PI 3.1415926535897932384626433832795f

class ViewMeterComponent : public AbstractComponent{
    
public:
    
    void paint (Graphics& g){
        g.drawImageWithin(ImageFactory::of().png[eMeter], 0, 0, 120,80, juce::RectanglePlacement::stretchToFit, false);
        g.drawImageWithin(ImageFactory::of().png[eMeter], 150, 0, 120,80, juce::RectanglePlacement::stretchToFit, false);
        
        float dbL = Model::of().sumPeakL;
        float dbR = Model::of().sumPeakR;
        
     //    dbL = 0;
    //dbR = 0;
        
        float r = 50;
        float cx = 60;
        float cy = 0;
   
        float aL = 134.0f - (96.0 + dbL) / 96.0f * 60.0f;  // we base on 45 degree working
        float aR = 134.0f - (96.0 + dbR) / 96.0f * 60.0f;
        
        float xL = cx + r * cos(aL * PI/180.0f);
        float yL = cy + r * sin(aL * PI/180.0f) ;
        
        float xR = cx + r * cos(aR * PI/180.0f);
        float yR = cy + r * sin(aR * PI/180.0f) ;
        
        g.setColour(juce::Colours::black);
        g.drawLine(60,80, xL, 80 - yL, 1.2);
        g.drawLine(150+60,80, 150+xR, 80 - yR, 1.2);
    }
    
    void resized(){
        
    }
    
    void setDials() override{
        
    }
    
private:
    
};

#endif /* ViewMeterComponent_h */
