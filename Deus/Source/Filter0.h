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

class Filter0 : public IModule{
public:
       
    void init (int sampleRate, int samplesPerBlock) override{
        this->sampleRate = sampleRate;
        this->sr = sampleRate * OVERSAMPLING;
        this->samplesPerBlock = samplesPerBlock;
    }
    
    ParamSet getSet() override{
       ParamSet set;
       set.moduleId = mFilter0;
       return set;
    }
    
    void set(int pid, float p) override{
        switch(pid){
            case 0:
                cutoff = p;
            break;
            case 1:
                resonance = p;
             break;
            case 2:
                type = p;
             break;
            case 3:
                drive = DecibelToLinear(p);
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

    }
    
    void noteOff(int channel, int note)override{
        
    }
    
    float getNextL(float input, bool move)override{
        return input * drive;
    }
    
    float getNextR(float input, bool move)override{
        return input * drive;
    }
    
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
};


#endif /* Filter0_h */
