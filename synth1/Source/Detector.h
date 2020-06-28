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
            float pL = fabs(channelDataL[i]);
            float pR = fabs(channelDataR[i]);
            
            float v = (channelDataL[i] + channelDataR[i]) * 0.5;
            v = fabs(v);
            v *= v;
            
            
            if(v > last){
                current = attack * (last-v) + v;
            }else{
                 current = release * (last-v) + v;
            }
            
            if(pL > lastPeakL){
                currentPeakL = attack * (lastPeakL-v) + v;
            }else{
                 currentPeakL = release * (lastPeakL-v) + v;
            }
            
            if(pR > lastPeakR){
               currentPeakR = attack * (lastPeakR-v) + v;
           }else{
                currentPeakR = release * (lastPeakR-v) + v;
           }
            
            current = fmin(current, 1.0f);
            current = fmax(current, 0.0f);
            last = current;
            current = pow(current, 0.5f);
            
            lastPeakL = currentPeakL;
            lastPeakR = currentPeakR;
        }
        
        float level = -96.0f;
        if(current > 0.0f){
            level = 20.0f * log10(current);
            if(level < -96.0f){
                level = -96.0f;
            }
        }
        Model::of().sumRMS = level;
        
        float levelL = -96.0f;
        float levelR = -96.0f;
        if(currentPeakL > 0.0f){
           levelL = 20.0f * log10(currentPeakL);
           if(levelL < -96.0f){
               levelL = -96.0f;
            }
         }
        if(currentPeakR > 0.0f){
          levelR = 20.0f * log10(currentPeakR);
          if(levelR < -96.0f){
              levelR = -96.0f;
           }
        }
         Model::of().sumPeakL = levelL;
         Model::of().sumPeakR = levelR;
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
    float lastPeakL;
    float lastPeakR;
    float current;
    float currentPeakL;
    float currentPeakR;
    
    private:
    double TC = -0.99967234081320612457819304641019;
        float sampleRate;
        int samplesPerBlock;
        float attack = 200;
        float release = 300;
        
};
#endif /* Detector_h */
