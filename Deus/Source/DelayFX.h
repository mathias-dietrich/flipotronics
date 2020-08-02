//
//  DelayFX.h
//  Deus
//
//  Created by Mathias Dietrich on 8/2/20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef DelayFX_h
#define DelayFX_h

#include "IModule.h"
#include "Model.h"

#define DELBUFSIZE SAMPLERATEMAX * 4

class DelayFX : public IModule{
public:
       
    void init (int sampleRate, int samplesPerBlock) override{
        this->sampleRate = sampleRate;
        this->sr = sampleRate * OVERSAMPLING;
        this->samplesPerBlock = samplesPerBlock;
        bufPos = 0;
    }
    
    ParamSet getSet() override{
       ParamSet set;
       set.moduleId = mFilter0;
       return set;
    }
    
    int getPos(int pos){
        if(pos < 0){
            return pos + DELBUFSIZE;
        }
        if(pos > DELBUFSIZE){
            return pos - DELBUFSIZE;
        }
        return pos;
    }
    
    void handle(AudioBuffer<float>& buffer, int totalNumInputChannels, int totalNumOutputChannels) {
        auto* channelDataL = buffer.getWritePointer (0);
        auto* channelDataR = buffer.getWritePointer (1);
        
        int delLeft = timeL * sampleRate * 0.001;
        int delRight = timeR * sampleRate * 0.001;

        for(int i=0; i < samplesPerBlock;++i){
            bufL[bufPos] = channelDataL[i] + feedbackL * bufL[getPos(bufPos-delLeft)];
            bufR[bufPos] = channelDataR[i] + feedbackR * bufR[getPos(bufPos-delRight)];
            
            channelDataL[i] = channelDataL[i] * (1.0-volL)  + bufL[getPos(bufPos-delLeft)] * volL;
            channelDataR[i] = channelDataR[i] * (1.0-volR)  + bufR[getPos(bufPos-delRight)] * volR;
            
            ++bufPos;
        }
        if(bufPos >= DELBUFSIZE) {
            bufPos -= DELBUFSIZE;
        }
    }
    
    void set(int pid, float p) override{
        switch(pid){
            case 0:
                timeL = p;
            break;
            case 1:
                timeR = p;
            break;
            case 2:
                feedbackL = p;
            break;
            case 3:
                feedbackR = p;
             break;
            case 4:
                volL = p;
            break;
            case 5:
                volR = p;
             break;
        }
    }
    
    int getParamCount() override{
          return 4;
    }
    
    E_Module getType() override{
        return mDelay;
    }
    
    void reset(){

    }
    
    void noteOn(int channel, int note) override{

    }
    
    void noteOff(int channel, int note)override{
        
    }
    
    float getNextL(float input, bool move)override{
        valL = input;
        return valL;
    }
    
    float getNextR(float input, bool move)override{
        valR = input;
        return valR;
    }
    
    float modCutoff = 1.0f;
    
    //Live Params
    atomic<float> timeL;
    atomic<float> timeR;
    atomic<float> feedbackL;
    atomic<float> feedbackR;
    atomic<float> volL;
    atomic<float> volR;
    
    int note;
    float valL;
    float valR;
    
    int sampleRate;
    int sr;
    int samplesPerBlock;
    
private:
    float  bufL[DELBUFSIZE];
    float  bufR[DELBUFSIZE];
    int bufPos;

};

#endif /* DelayFX_h */
