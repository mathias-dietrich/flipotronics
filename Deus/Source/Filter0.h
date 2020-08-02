//
//  Filter0.h
//  Deus
//
//  Created by Mathias Dietrich on 7/30/20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef Filter0_h
#define Filter0_h

#include "IModule.h"
#include "Model.h"
#include "MultiModeLadderFilter.h"

class Filter0 : public IModule{
public:
       
    void init (int sampleRate, int samplesPerBlock) override{
        this->sampleRate = sampleRate;
        this->sr = sampleRate * OVERSAMPLING;
        this->samplesPerBlock = samplesPerBlock;
        
        filterL.setSampleRate(sampleRate);
        filterR.setSampleRate(sampleRate);
        modCutoff = 1.0f;
    }
    
    void set(int pid, float p) override{
        switch(pid){
            case 0:
                cutoff = p;
                filterL.setCutoff(cutoff);
                filterR.setCutoff(cutoff);
            break;
            case 1:
                resonance = p;
                filterL.setResonance(resonance / 100.0f);
                filterR.setResonance(resonance / 100.0f);
            break;
            case 2:
                type = p;
                 filterL.setFilterType(type);
                 filterR.setFilterType(type);
            break;
            case 3:
                drive = DecibelToLinear(p);
                filterL.setDrive(drive);
                filterR.setDrive(drive);
             break;
        }
    }
    
    int getParamCount() override{
          return 4;
    }
    
    E_Module getType() override{
        return mFilter0;
    }
    
    void reset(){
        val = 0;
    }
    
    void noteOn(int channel, int note) override{
        filterL.reset();
        filterL.setBoost(true);
        filterR.reset();
        filterR.setBoost(true);
    }
    
    void noteOff(int channel, int note)override{
        
    }
    
    float getNextL(float input, bool move)override{
        filterL.modCutoff = modCutoff;
        filterL.setCutoff(cutoff);
        return filterL.process(input);
    }
    
    float getNextR(float input, bool move)override{
        filterR.modCutoff = modCutoff;
        filterL.setCutoff(cutoff);
        return filterR.process(input);
    }
    
    float modCutoff = 1.0f;
    
private:
    
    //Live Params
    atomic<int> cutoff;
    atomic<int> resonance;
    atomic<float> type;
    atomic<float> drive;
    
    int note;
    float val;
    
    int sampleRate;
    int sr;
    int samplesPerBlock;
    
    MultiModeLadderFilter filterL;
    MultiModeLadderFilter filterR;
};


#endif /* Filter0_h */
