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
        osc1Module->noteOn(channel, note);
    }
    
    void noteRetrigger(){

    }
    
    void noteOff(){
        osc1Module->noteOff(midiChannel, noteNumber);
        active = false;
    }
    
    void kill(){
        
    }
    
    void configure(Preset preset){
        this->preset = preset;
        
        // TODO Build all
        osc1Module = ModuleFactory::of()->get(preset.osc1Module);
        osc2Module = ModuleFactory::of()->get(preset.osc2Module);
        
        osc1Module->init(sampleRate,samplesPerBlock );
        
        for(int i=0;i< osc1Module->getParamCount();++i){
            osc1Module->set(i,preset.params[mOSCAnalog0][i].valF);
        }
    
    }
    
    void update(E_Module module, int pid, float val){
        switch(module){
            case mOSCAnalog0:
                osc1Module->set(pid, val);
                break;
            case mOSCAnalog1:
                
                break;
            case mOSCWave0:
                
                break;
            case mOSCWave1:
                
                break;
            case mOSCSample0:
                
                break;
            case mOSCSample1:
                
                break;
            case mFilter0:
                
                break;
            case mFilter1:
                
                break;
            case mAdsr0:
                
                break;
            case mAdsr1:
                
                break;
            case mAdsr2:
                
                break;
            case mLFO0:
                
                break;
            case mLFO1:
                
                break;
            case mLFO2:
                
                break;
            case mAmp:
                
                break;
            case mInput:
                
                break;
            case mLFX0:
                
                break;
            case mLFX1:
                
                break;
            case mLFX2:
                
                break;
            case mLFX3:
                
                break;
            case mMacro:
                
                break;
            case mBlank:
                
                break;
            case mMODULECOUNT:
                
                break;
        }
        
        std::cout << "Voice " << vid << " update " << module << " " << pid << " " << val << std::endl;
    }
    
    void init (double sampleRate, int samplesPerBlock){
        this->sampleRate = sampleRate;
        this->sr = sampleRate * OVERSAMPLING;
        this->samplesPerBlock = samplesPerBlock;
    }
    
    void render(int64 clock, AudioBuffer<float>& buffer){
        auto* channelDataL = buffer.getWritePointer (0);
        auto* channelDataR = buffer.getWritePointer (1);
        for (int sample = 0; sample < samplesPerBlock; ++sample) {
            float value = osc1Module->getNext(true);
            channelDataL[sample] += value;
            channelDataR[sample] += value;
       }
    }
    
private:
    
    int sampleRate;
    int sr;
    int samplesPerBlock;
    Preset preset;

};
#endif /* Voice_h */
