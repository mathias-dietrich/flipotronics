//
//  Detector.h
//  Deus
//
//  Created by Mathias Dietrich on 8/1/20.
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
            
            float vL = channelDataL[i];
            vL = fabs(vL);
            vL *= vL;
            
            float vR =  channelDataR[i];
            vR = fabs(vR);
            vR *= vR;
            
            
            if(vL > lastL){
                currentL = attack * (lastL-vL) + vL;
            }else{
                 currentL = release * (lastL-vL) + vL;
            }
            
            if(pL > lastPeakL){
                currentPeakL = attack * (lastPeakL-vL) + vL;
            }else{
                 currentPeakL = release * (lastPeakL-vL) + vL;
            }
            
            if(pR > lastPeakR){
               currentPeakR = attack * (lastPeakR-vR) + vR;
           }else{
                currentPeakR = release * (lastPeakR-vR) + vR;
           }
            
            currentL = fmin(currentL, 1.0f);
            currentL = fmax(currentL, 0.0f);
            lastL = currentL;
            currentL = pow(currentL, 0.5f);
            
            currentR = fmin(currentR, 1.0f);
            currentR = fmax(currentR, 0.0f);
            lastR = currentR;
            currentR = pow(currentR, 0.5f);
            
            lastPeakL = currentPeakL;
            lastPeakR = currentPeakR;
        }
        
        float levelL = -96.0f;
        if(currentL > 0.0f){
            levelL = 20.0f * log10(currentL);
            if(levelL < -96.0f){
                levelL = -96.0f;
            }
        }
        
        float levelR = -96.0f;
        if(currentR > 0.0f){
            levelR = 20.0f * log10(currentR);
            if(levelR < -96.0f){
                levelR = -96.0f;
            }
        }
        Model::of()->sumRMSL = levelL;
        Model::of()->sumRMSR = levelR;
        
        levelL = -96.0f;
        levelR = -96.0f;
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
         Model::of()->sumPeakL = levelL;
         Model::of()->sumPeakR = levelR;
    }
    
    void init (float sampleRate, int samplesPerBlock){
        this->sampleRate = sampleRate;
        this->samplesPerBlock = samplesPerBlock;
        lastL = 0;
        lastR = 0;
    }
    
    void setAttack(int ms){
        attack = exp(TC /  (ms * sampleRate * 0.001f));
    }
    
    void setRelease(int ms){
        release = exp(TC / (ms * sampleRate * 0.001f));
    }
        
    float lastL;
    float lastR;
    float lastPeakL;
    float lastPeakR;
    float currentL;
    float currentR;
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
