//
//  Delay.h
//  synth1
//
//  Created by Mathias Dietrich on 17.06.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef Delay_h
#define Delay_h

#include <JuceHeader.h>
#include "Note.h"
#include "Curve.h"
#include "ParamBuilder.h"

#define BUFSIZE SAMPLERATEMAX * 5
class Delay {     
    
  public:
    Delay(){

    }
    
    ~Delay(){

    }
    
    int getPos(int pos){
        if(pos < 0){
            return pos + BUFSIZE;
        }
        if(pos > BUFSIZE){
            return pos - BUFSIZE;
        }
        return pos;
    }
    
    void handle(AudioBuffer<float>& buffer, int totalNumInputChannels, int totalNumOutputChannels) {
        auto* channelDataL = buffer.getWritePointer (0);
        auto* channelDataR = buffer.getWritePointer (1);
        
        int delLeft = par[P_FX_DELAYL_TIME] * sampleRate * 0.001;
        int delRight = par[P_FX_DELAYR_TIME] * sampleRate * 0.001;
        float delLeftF = par[P_FX_DELAYL_FEEDBACK];
       
        float delLeftMix = par[P_FX_DELAYL_MIX];
        float delRightMix = par[P_FX_DELAYR_MIX];
        float delRightF = par[P_FX_DELAYR_FEEDBACK];
        
        for(int i=0; i < samplesPerBlock;++i){
            bufL[bufPos] = channelDataL[i];
            bufR[bufPos] = channelDataR[i];
            
            channelDataL[i] = channelDataL[i] * (1.0-delLeftMix)  + bufL[getPos(bufPos-delLeft)] * delLeftMix;
            channelDataR[i] = channelDataR[i] * (1.0-delRightMix)  + bufR[getPos(bufPos-delRight)] * delRightMix;
            
            ++bufPos;
        }
        
        if(bufPos >= BUFSIZE) {
            bufPos -= BUFSIZE;
        }
    }
    
    void init (float sampleRate, int samplesPerBlock){
        this->sampleRate = sampleRate;
        this->samplesPerBlock = samplesPerBlock;
        bufPos = 0;
    }
    
private:
    float sampleRate;
    int samplesPerBlock;
    float  bufL[SAMPLERATEMAX * OVERSAMPLING];
    float  bufR[SAMPLERATEMAX * OVERSAMPLING];
    
    int bufPos;
    
};
#endif /* Delay_h */
