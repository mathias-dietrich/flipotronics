//
//  AnalogOsc0.h
//  Deus
//
//  Created by Mathias Dietrich on 7/29/20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef AnalogOsc0_h
#define AnalogOsc0_h

#include "IModule.h"
#include "Model.h"

class AnalogOsc0 : public IModule{
public:
       
    void init (int sampleRate, int samplesPerBlock) override{
        this->sampleRate = sampleRate;
        this->sr = sampleRate * OVERSAMPLING;
        this->samplesPerBlock = samplesPerBlock;

        // Test
        m_deltaTime = 1.0 / ((double )sampleRate);
        m_phase = 0;
    }
    
    ParamSet getSet() override{
       ParamSet set;
       set.moduleId = mOSCAnalog0;
       return set;
    }
    
    void set(int pid, float p) override{
        switch(pid){
            case 0:
                octave = p;
            break;
            case 1:
                semitone = p;
             break;
            case 2:
                finetuning = p;
             break;
            case 3:
                volume = p;
             break;
            case 4:
                wave = p;
            break;
        }
    }
    
    int getParamCount() override{
          return 5;
    }
    
    E_Module getType() override{
        return mOSCAnalog0;
    }
    
    void reset(){
        val = 0;
    }
    
    void noteOn(int channel, int note) override{
        this->note = note;
        m_frequency = MidiToFreq(note, 440.0);
    }
    
    void noteOff(int channel, int note)override{
        
    }
    
    float getNext(bool move)override{
        if(move){
            int fNote =  note + octave * 12 + semitone;
            m_frequency =  MidiToFreq(fNote, 440.0);
            float fineTune = 1.0 + finetuning / 100.0f;
            m_frequency *= fineTune;
            float vol = DecibelToLinear(volume);
            val =  vol * sin(2.0f * double_Pi * m_frequency * m_time + m_phase);
            m_time += m_deltaTime;
        }
        return val;
    }
    
private:
    
    //Live Params
    atomic<int> octave;
    atomic<int> semitone;
    atomic<float> finetuning;
    atomic<float> volume;
    atomic<int> wave;
    
    int note;
    float val;
    
    float m_phase;
    float m_deltaTime;
    float m_frequency = 440;
    float m_time = 0.0;
    
    int sampleRate;
    int sr;
    int samplesPerBlock;
};

#endif /* AnalogOsc0_h */
