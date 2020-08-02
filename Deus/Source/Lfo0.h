//
//  Lfo0.h
//  Deus
//
//  Created by Mathias Dietrich on 7/31/20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef Lfo0_h
#define Lfo0_h

#include "IModule.h"
#include "Model.h"
#include "Enums.h"

class Lfo0 : public IModule{
public:
       
    void init (int sampleRate, int samplesPerBlock) override{
        this->sampleRate = sampleRate;
        this->sr = sampleRate * OVERSAMPLING;
        this->samplesPerBlock = samplesPerBlock;

        // Test
        m_deltaTime = 1.0 / ((double )sampleRate);
        m_phase = 0;
    }

    void set(int pid, float p) override{
        switch(pid){
            case 0:
                wave = p;
            break;
            case 1:
                freq = p;
             break;
        }
    }
    
    int getParamCount() override{
          return 3;
    }
    
    E_Module getType() override{
        return mLFO0;
    }
    
    void reset(){
        m_phase = 0;
        m_time = 0;
    }
    
    void noteOn(int channel, int note) override{

    }
    
    void noteOff(int channel, int note)override{
        
    }
    
    float getNextL(float input, bool move)override{
        if(move){
            val =  sin(2.0f * double_Pi * freq * m_time + m_phase);
            m_time += m_deltaTime;
        }
        return val;
    }
    
    float getNextR(float input, bool move)override{
        if(move){
           val =  sin(2.0f * double_Pi * freq * m_time + m_phase);
           m_time += m_deltaTime;
       }
       return val;
    }
    
private:
    
    //Live Params
    atomic<int> wave;
    atomic<float> freq;
    
    float m_phase;
    float m_deltaTime;
    float m_time = 0.0;
    
    int sampleRate;
    int sr;
    int samplesPerBlock;
    
    float val;
};

#endif /* Lfo0_h */
