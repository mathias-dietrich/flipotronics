//
//  Smooth.h
//  synth1
//
//  Created by Mathias Dietrich on 15.06.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
// https://forum.juce.com/t/parameter-smoothing-methods-algorithms/14773/3
//

#ifndef Smooth_h
#define Smooth_h

#include <stdio.h>
#include <JuceHeader.h>

class Smooth {

public:
    
    void setup(int millisecondsToReach99percent, int sampleRate){
         coeff = (float)(exp(log(0.01f)/( millisecondsToReach99percent * sampleRate * 0.001)));
    }
    
    float processLP(float inVal){
        smoothed = coeff * (smoothed - inVal) + inVal;
        return smoothed;
    }
    
private:
    float coeff;
    float smoothed;
};

#endif /* Smooth_h */
