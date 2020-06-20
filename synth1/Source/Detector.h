//
//  Detector.h
//  synth1
//
//  Created by Mathias Dietrich on 17.06.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef Detector_h
#define Detector_h

#include <stdio.h>
#include <JuceHeader.h>

class Detector{
public:
    
    Detector(){

    }

    void handle(AudioBuffer<float>& buffer, int totalNumInputChannels, int totalNumOutputChannels) {
        auto* channelDataL = buffer.getWritePointer (0);
        auto* channelDataR = buffer.getWritePointer (1);
        
        for(int i=0; i < samplesPerBlock;++i){
            float p = fabs(channelDataL[i]);
            float v = (channelDataL[i] + channelDataR[i]) * 0.5;
            v = fabs(v);
            v *= v;
            
            
            if(v > last){
                current = attack * (last-v) + v;
            }else{
                 current = release * (last-v) + v;
            }
            
            if(p > lastPeak){
                currentPeak = attack * (lastPeak-v) + v;
            }else{
                 currentPeak = release * (lastPeak-v) + v;
            }
            
            current = fmin(current, 1.0f);
            current = fmax(current, 0.0f);
            last = current;
            current = pow(current, 0.5f);
            
            lastPeak = currentPeak;
        }
        
        float level = -96.0f;
        if(current > 0.0f){
            level = 20.0f * log10(current);
            if(level < -96.0f){
                level = -96.0f;
            }
        }
        sumRMS = level;
        
        level = -96.0f;
           if(currentPeak > 0.0f){
               level = 20.0f * log10(currentPeak);
               if(level < -96.0f){
                   level = -96.0f;
            }
         }
        sumPeak = level;
    }
    
    void init (float sampleRate, int samplesPerBlock){
        this->sampleRate = sampleRate;
        this->samplesPerBlock = samplesPerBlock;
        last = 0;
    }
    
    void setAttack(int ms){
        attack = exp(TC /  (ms * sampleRate * 0.001f));
    }
    
    void setRelease(int ms){
        release = exp(TC / (ms * sampleRate * 0.001f));
    }
        
    float last;
    float lastPeak;
    float current;
    float currentPeak;
    
    private:
    double TC = -0.99967234081320612457819304641019;
        float sampleRate;
        int samplesPerBlock;
        float attack = 200;
        float release = 300;
        
};
#endif /* Detector_h */
