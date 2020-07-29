//
//  Voice.h
//  Deus
//
//  Created by Mathias Dietrich on 7/29/20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef Voice_h
#define Voice_h

#include "Func.h"
#include "IComponent.h"
#include "IModule.h"
#include "ModuleFactory.h"

class Voice{
public:
    
    IModule * inputModule;
    IModule * osc1Module;
    IModule * osc2Module;
    IModule * filter1Module;
    IModule * filter2Module;
    IModule * outpuModule;
    IModule * adsr0Module;
    IModule * adsr1Module;
    IModule * adsr2Module;
    IModule * lfo0Module;
    IModule * lfo1Module;
    IModule * lfo2Module;
    
    int vid;
    bool active = false;
    int noteNumber = 0;
    int midiChannel = 0;
    float velocity = 0;
    int64 now = Time::currentTimeMillis();
    
    Voice(){

    }
    
    ~Voice(){

    }
    
    void noteOn(int channel, int note){
        midiChannel = channel;
        noteNumber = note;
        active = true;
        
        m_frequency = MidiToFreq(noteNumber, 440.0f);
    }
    
    void noteRetrigger(){

    }
    
    void noteOff(){
        active = false;
    }
    
    void kill(){
        
    }
    
    void configure(Preset preset){
        this->preset = preset;
        
        // TODO Build all
        osc1Module = ModuleFactory::of()->get(preset.osc1Module);
        osc2Module = ModuleFactory::of()->get(preset.osc2Module);
    }
    
    void update(E_Module module, int pid, float val){
        std::cout << "Voice " << vid << " update " << module << " " << pid << " " << val << std::endl;
    }
    
    void init (double sampleRate, int samplesPerBlock){
        this->sampleRate = sampleRate;
        this->sr = sampleRate * OVERSAMPLING;
        this->samplesPerBlock = samplesPerBlock;

        // Test
        m_deltaTime = 1 / sampleRate;
        m_phase = 0;
    }
    
    void render(int64 clock, AudioBuffer<float>& buffer){
        auto* channelDataL = buffer.getWritePointer (0);
        auto* channelDataR = buffer.getWritePointer (1);
        for (int sample = 0; sample < samplesPerBlock; ++sample) {
            float value = m_amplitude * sin(2 * double_Pi * m_frequency * m_time + m_phase);
            channelDataL[sample] += value;
            channelDataR[sample] += value;
            m_time += m_deltaTime;
       }
    }
    
private:
    float m_phase;
    float m_deltaTime;
    float m_frequency = 440;
    float m_time = 0.0;
    float m_amplitude = 1;
    
    int sampleRate;
    int sr;
    int samplesPerBlock;
    Preset preset;

};
#endif /* Voice_h */
