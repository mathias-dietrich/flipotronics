//
//  Amp.h
//  Deus
//
//  Created by Mathias Dietrich on 8/3/20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef Amp_h
#define Amp_h

#include "IModule.h"
#include "Model.h"

class Amp : public IModule{
    
public:
       
    void init (int sampleRate, int samplesPerBlock) override{
        this->sampleRate = sampleRate;
        this->sr = sampleRate * OVERSAMPLING;
        this->samplesPerBlock = samplesPerBlock;
    }
    
    void set(int pid, float p) override{
        switch(pid){
            case 0:
                volume = DecibelToLinear(p);
            break;
            case 1:
                pan = p;
            break;
            case 2:
                saturation = p;
            break;
        }
    }
    
    int getParamCount() override{
          return 3;
    }
    
    E_Module getType() override{
        return mAmp;
    }
    
    void reset(){

    }
    
    void noteOn(int channel, int note) override{
    }
    
    void noteOff(int channel, int note)override{
        
    }
    
    float getNextL(float input, bool move)override{
        float v = tanh(6.0f * saturation * input );
        v*= volume * (1.0-(pan+0.5f));
        if(v>0.999){
            v = 0.999;
        }
        if(v<-0.999){
            v = -0.999;
        }
        return v;
    }
    
    float getNextR(float input, bool move)override{
        float v = tanh(6.0f * saturation * input );
        v*= volume *( pan+0.5f);
        if(v>0.999){
            v = 0.999;
        }
        if(v<-0.999){
            v = -0.999;
        }
        return v;
    }
    
private:
    
    // Live Params
    atomic<float> volume;
    atomic<float> pan;
    atomic<float> saturation;
    
    int note;
    float val;
    
    int sampleRate;
    int sr;
    int samplesPerBlock;
};
#endif /* Amp_h */
