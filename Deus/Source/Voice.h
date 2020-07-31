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
#include "Matrix.h"

#include "Filter0.h"
#include "Filter1.h"

#include "Lfo0.h"
class Core;

class Voice{
public:
    
    IModule * inputModule;
    AnalogOsc0 osc0Module;
    AnalogOsc1 osc1Module;
    Filter0 filter0Module;
    Filter1 filter1Module;
    
    IModule * outpuModule;
    IModule * adsr0Module;
    IModule * adsr1Module;
    IModule * adsr2Module;
    
    Lfo0 lfo0Module;
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
        osc0Module.noteOn(channel, note);
        osc1Module.noteOn(channel, note);
        filter0Module.noteOn(channel, note);
        filter1Module.noteOn(channel, note);
    }
    
    void noteRetrigger(){

    }
    
    void noteOff(){
        osc0Module.noteOff(midiChannel, noteNumber);
        osc1Module.noteOff(midiChannel, noteNumber);
        filter0Module.noteOff(midiChannel, noteNumber);
        filter1Module.noteOff(midiChannel, noteNumber);
        active = false;
    }
    
    void kill(){
        
    }
    
    void configure(Preset preset){
        this->preset = preset;

        osc0Module.init(sampleRate,samplesPerBlock );
        osc1Module.init(sampleRate,samplesPerBlock );
        
        filter0Module.init(sampleRate,samplesPerBlock );
        filter1Module.init(sampleRate,samplesPerBlock );
        
        lfo0Module.init(sampleRate,samplesPerBlock );
        
        for(int i=0;i< osc0Module.getParamCount();++i){
            osc0Module.set(i,preset.params[mOSCAnalog0][i].valF);
        }
        osc0Module.setTuning(preset.tuning);
        
        for(int i=0;i< osc1Module.getParamCount();++i){
            osc1Module.set(i,preset.params[mOSCAnalog1][i].valF);
        }
        osc1Module.setTuning(preset.tuning);
        
        for(int i=0;i< filter0Module.getParamCount();++i){
            filter0Module.set(i,preset.params[mFilter0][i].valF);
        }
        for(int i=0;i< filter1Module.getParamCount();++i){
            filter1Module.set(i,preset.params[mFilter1][i].valF);
        }
        
        for(int i=0;i< filter1Module.getParamCount();++i){
            lfo0Module.set(i,preset.params[mLFO0][i].valF);
        }
        
        // Configure Matrix
        matrix.clear();
        matrix.addEntry(matrix.createEntry(s_LFO0, d_OSC0_VOL, mLFO0, 0, mLFO0, P_FIXTURN, t_BIPOLAR_TO_UNIPOLAR, true,true));
        matrix.addEntry(matrix.createEntry(s_LFO0, d_OSC0_PITCH, mLFO0, 1, mLFO0, P_FIXTURN, t_BIPOLAR_TO_UNIPOLAR, true,true));
        matrix.addEntry(matrix.createEntry(s_LFO0, d_FILTER0_CUTOFF, mLFO0, 2, mLFO0, P_FIXTURN, t_BIPOLAR_TO_UNIPOLAR, true,true));
        
        for(int i=0;i< matrix.getParamCount();++i){
            matrix.set(i,preset.params[mMatrix][i].valF);
        }
    }
    
    void update(E_Module module, int pid, float val){
        switch(module){
            case mMatrix:
                matrix.set(pid, val);
            case mOSCAnalog0:
                osc0Module.set(pid, val);
                break;
            case mOSCAnalog1:
                osc1Module.set(pid, val);
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
                filter0Module.set(pid, val);
                break;
                
            case mFilter1:
                filter1Module.set(pid, val);
                break;
                
            case mAdsr0:
                
                break;
            case mAdsr1:
                
                break;
            case mAdsr2:
                
                break;
            case mLFO0:
                lfo0Module.set(pid, val);
                break;
                
            case mLFO1:
                
                break;
            case mLFO2:
                
                break;
                
            case mLFO3:
                    
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
                if(pid==16){
                    osc0Module.setTuning(val);
                    osc1Module.setTuning(val);
                }
                break;
            case mBlank:
                
                break;
            case mMODULECOUNT:
                
                break;
        }
        
       // std::cout << "Voice " << vid << " update " << module << " " << pid << " " << val << std::endl;
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
            
            float oscPitch = 0.5 + matrix.targets[d_OSC0_PITCH];
            osc0Module.pitchMod = oscPitch;
            osc1Module.pitchMod = oscPitch;
            
            float vLeft = osc0Module.getNextL(0, true);
            vLeft += osc1Module.getNextL(0, true);
            
            float vRight = vLeft;

            
            float modFilterCutoff =  matrix.targets[d_FILTER0_CUTOFF];
            filter0Module.modCutoff = modFilterCutoff;
            vLeft = filter0Module.getNextL(vLeft, true);
            vRight = filter0Module.getNextR(vRight, true);
            
            float  mix = vLeft + vRight;
            
            // test LFO
            //float oscVol = 1.0 - lfo0Module->getNextL(0, true);
            
            // Feed Matrix
            matrix.sources[s_LFO0] = lfo0Module.getNextL(0, true);

             // Calc Matrix
            matrix.calc();
            
            float oscVol = matrix.targets[d_OSC0_VOL];
            
            
            if(oscVol<0){
                oscVol *= -1.0f;
            }
            mix *= oscVol;
            
            // guards
        
            channelDataL[sample] += mix;
            channelDataR[sample] += mix;
       }
    }

    Matrix matrix;


private:
    
    int sampleRate;
    int sr;
    int samplesPerBlock;
    Preset preset;
    
};
#endif /* Voice_h */
