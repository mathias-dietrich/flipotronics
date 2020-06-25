//
//  CurveComponent.h
//  synth1
//
//  Created by Mathias Dietrich on 25.06.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef CurveComponent_h
#define CurveComponent_h
#include <stdio.h>
#include <JuceHeader.h>
#include "CircularBuffer.h"
#include "Func.h"
#include "Color.h"
#include "AbstractComponent.h"
//==============================================================================

class CurveComponent : public AbstractComponent {
    
 public:
    CurveComponent(){
            curve.set(0);
    }
    
    ~CurveComponent () {
           
    }
       
    void paint (Graphics& g) override {
        Rectangle<int> r = getLocalBounds();
        int width = r.getWidth();
        int height = r.getHeight() ;
        int w = 600; // width
        int h = 300;
        int xOffset = r.getX() + (width-w)/2;
        int yOffset = r.getY() + (height-h)/2;
        g.setColour(C_KEYBORDAREA);
        g.fillRoundedRectangle(xOffset, yOffset, w,h,5);

        curve.set(Model::of().par[1022]);
       
        int ylast = yOffset + h;
        
        g.setColour (Colours::darkgrey);
        for(int i=0;i<w+1;i = i + w/10){
            g.drawLine (xOffset+i,yOffset, xOffset+i , yOffset+h, 0.5);
        }
        for(int i=0;i<h+1;i = i + h/10){
            g.drawLine (xOffset,yOffset+i, xOffset + w , yOffset+i, 0.5);
        }
        
        ylast = yOffset + h;
        g.setColour (Colours::white);
        for(int i=0;i<w;++i){
            int y = yOffset + h - h * curve.getScaled(i , w) ;
            g.drawLine (xOffset + i, ylast, i + xOffset+1, y, 1.0f);
            ylast = y;
        }
    }
    
private:
    
    Curve curve;
};

#endif /* CurveComponent_h */
