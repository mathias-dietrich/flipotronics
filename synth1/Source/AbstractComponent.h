//
//  AbstractComponent.h
//  synth1
//
//  Created by Mathias Dietrich on 25.06.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef AbstractComponent_h
#define AbstractComponent_h

#include <stdio.h>
#include <JuceHeader.h>

class AbstractComponent : public Component{
    
public:
    void init(float sampleRate, int samplesPerBlock){
        this->samplesPerBlock = samplesPerBlock;
        this->sampleRate = sampleRate;
        this->sr = sampleRate * OVERSAMPLING;
        this->blocksPerSecond = sampleRate / samplesPerBlock;
    }
    
    float sampleRate;
    int samplesPerBlock;
    float sr;
    int blocksPerSecond;
};

#endif /* AbstractComponent_h */
