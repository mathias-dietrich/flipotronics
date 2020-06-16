//
//  Voice.h
//  synth1
//
//  Created by Mathias Dietrich on 31.05.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef Voice_h
#define Voice_h

#include <stdio.h>
#include <JuceHeader.h>
#include "WaveTable.h"
#include "Model.h"
#include "Func.h"
#include "ParamBuilder.h"
#include "Adsr.h"
#include "Smooth.h"
#include "Osc.h"
#include "MultiModeLadderFilter.h"
#include "Lfo.h"

class Voice {

public:
    int vid;
    bool active;
    //WaveTable *waveTable;
    int noteNumber = 0;
    float velocity = 1.0;
    double volOscSin = 1.0;
    double volOscSaw = 1.0;
    double volOscSquare = 1.0;
    double volOscTriangle = 1.0;
    double volOscWhite = 1.0;
    int midiChannel = 0;
    int64 now = Time::currentTimeMillis();
    float tablePos0 = 0;
    float tablePos0_n1 = -1;
    float tablePos1 = 0;
    float tablePosSub = 0;
    float lastF0 = 0;
    float lastF1 = 0;
    
    Adsr adsr0;
    Adsr adsr1;
    Adsr adsr2;
    Adsr adsr3;
    
    Lfo lfo0;
    Lfo lfo1;
    Lfo lfo2;
    Lfo lfo3;
    
    float adsr0Target;
    float adsr0Target1;
    
    int lastPos0 = 1;
    
    Smooth smoothMaster;
    
    MultiModeLadderFilter filter0;
    MultiModeLadderFilter filter1;
    
    Voice(){
        
        // ADSR
        adsr0.uid = 1;
        adsr1.uid = 2;
        adsr2.uid = 3;
        adsr3.uid = 4;
        
        
    }
    
    ~Voice(){

    }

    void init (double sampleRate, int samplesPerBlock){
        this->sampleRate = sampleRate;
        sr = sampleRate * OVERSAMPLING;
        this->samplesPerBlock = samplesPerBlock;

        // OSC
        osc0.init(sampleRate,samplesPerBlock);
        osc1.init(sampleRate,samplesPerBlock);
        
        
        // ADSR
        adsr0.init(sampleRate,samplesPerBlock);
        adsr1.init(sampleRate,samplesPerBlock);
        adsr2.init(sampleRate,samplesPerBlock);
        adsr3.init(sampleRate,samplesPerBlock);
        
        adsr0Target = 0;
        
        // Smooth
        smoothMaster.setup(1,sampleRate);
        
        // Filter
        filter0.setSampleRate(sampleRate);
        filter1.setSampleRate(sampleRate);
        
        setParams();
    }
    
    void setParams(){
        adsr0.attackTimeMsec = par[P_ADSR1_ATTACK];
        adsr0.decayTimeMsec = par[P_ADSR1_DECAY];
        adsr0.sustainLevel = par[P_ADSR1_SUSTAIN];
        adsr0.releaseTimeMsec = par[P_ADSR1_RELEASE];
        adsr0.setAttackCurve(par[P_ADSR1_ATTACK_CURVE]);
        adsr0.setDecayCurve(par[P_ADSR1_DECAY_CURVE]);
        adsr0.setSustainCurve(par[P_ADSR1_SUSTAIN_CURVE]);
        adsr0.setReleaseCurve(par[P_ADSR1_RELEASE_CURVE]);
        adsr0.filterTarget = par[P_ADSR1_FILTER];
        adsr0.pitchTarget = par[P_ADSR1_PITCH];
        adsr0.ampTarget = par[P_ADSR1_AMP];
        adsr0.fxTarget = par[P_ADSR1_FX];
        adsr0.holdTimeMsec = par[P_ADSR1_HOLD];
        adsr0.delayTimeMsec = par[P_ADSR1_DELAY];
        adsr0.trigger = par[P_ADSR1_TRIGGER];
        adsr0.triggerTreshold = par[P_ADSR1_TRESHOLD];
        
        adsr1.attackTimeMsec = par[P_ADSR2_ATTACK];
        adsr1.decayTimeMsec = par[P_ADSR2_DECAY];
        adsr1.sustainLevel = par[P_ADSR2_SUSTAIN];
        adsr1.releaseTimeMsec = par[P_ADSR2_RELEASE];
        adsr1.setAttackCurve(par[P_ADSR2_ATTACK_CURVE]);
        adsr1.setDecayCurve(par[P_ADSR2_DECAY_CURVE]);
        adsr1.setSustainCurve(par[P_ADSR2_SUSTAIN_CURVE]);
        adsr1.setReleaseCurve(par[P_ADSR2_RELEASE_CURVE]);

        adsr1.filterTarget = par[P_ADSR2_FILTER];
        adsr1.pitchTarget = par[P_ADSR2_PITCH];
        adsr1.ampTarget = par[P_ADSR2_AMP];
        adsr1.fxTarget = par[P_ADSR2_FX];
        adsr1.holdTimeMsec = par[P_ADSR2_HOLD];
        adsr1.delayTimeMsec = par[P_ADSR2_DELAY];
        adsr1.trigger = par[P_ADSR2_TRIGGER];
        adsr1.triggerTreshold = par[P_ADSR2_TRESHOLD];
        
        adsr2.attackTimeMsec = par[P_ADSR3_ATTACK];
        adsr2.decayTimeMsec = par[P_ADSR3_DECAY];
        adsr2.sustainLevel = par[P_ADSR3_SUSTAIN];
        adsr2.releaseTimeMsec = par[P_ADSR3_RELEASE];
        adsr2.setAttackCurve(par[P_ADSR3_ATTACK_CURVE]);
        adsr2.setDecayCurve(par[P_ADSR3_DECAY_CURVE]);
        adsr2.setSustainCurve(par[P_ADSR3_SUSTAIN_CURVE]);
        adsr2.setReleaseCurve(par[P_ADSR3_RELEASE_CURVE]);

        adsr2.filterTarget = par[P_ADSR3_FILTER];
        adsr2.pitchTarget = par[P_ADSR3_PITCH];
        adsr2.ampTarget = par[P_ADSR3_AMP];
        adsr2.fxTarget = par[P_ADSR3_FX];
        adsr2.holdTimeMsec = par[P_ADSR3_HOLD];
        adsr2.delayTimeMsec = par[P_ADSR3_DELAY];
        adsr2.trigger = par[P_ADSR3_TRIGGER];
        adsr2.triggerTreshold = par[P_ADSR3_TRESHOLD];

        adsr3.attackTimeMsec = par[P_ADSR4_ATTACK];
        adsr3.decayTimeMsec = par[P_ADSR4_DECAY];
        adsr3.sustainLevel = par[P_ADSR4_SUSTAIN];
        adsr3.releaseTimeMsec = par[P_ADSR4_RELEASE];
        adsr3.setAttackCurve(par[P_ADSR4_ATTACK_CURVE]);
        adsr3.setDecayCurve(par[P_ADSR4_DECAY_CURVE]);
        adsr3.setSustainCurve(par[P_ADSR4_SUSTAIN_CURVE]);
        adsr3.setReleaseCurve(par[P_ADSR4_RELEASE_CURVE]);

        adsr3.filterTarget = par[P_ADSR4_FILTER];
        adsr3.pitchTarget = par[P_ADSR4_PITCH];
        adsr3.ampTarget = par[P_ADSR4_AMP];
        adsr3.fxTarget = par[P_ADSR4_FX];
        adsr3.holdTimeMsec = par[P_ADSR4_HOLD];
        adsr3.delayTimeMsec = par[P_ADSR4_DELAY];
        adsr3.trigger = par[P_ADSR4_TRIGGER];
        adsr3.triggerTreshold = par[P_ADSR4_TRESHOLD];
        
        filter0.setFilterType(par[P_FILTER1_TYPE]);
        filter0.setCutoff(par[P_FILTER1_FREQ]);
        filter0.setResonance(par[P_FILTER1_RES] / 100.0f);
        filter0.setFilterType(LPF1);
        
        filter1.setFilterType(par[P_FILTER2_TYPE]);
        filter1.setCutoff(par[P_FILTER2_FREQ]);
        filter1.setResonance(par[P_FILTER2_RES] / 100.0f);
    }
    
    void reset(){
        tablePos0 = 0;
        tablePos1 = sampleRate/2;
        tablePos0_n1 = -1;
        
        setParams();
        
        active = true;
        adsr0.start();
        adsr1.start();
        adsr2.start();
        adsr3.start();
        
        lastPos0 = 1;
        
        filter0.reset();
        filter0.setBoost(true);
        
        filter1.reset();
        filter1.setBoost(true);
    }
    
    void kill(){
        active = false;
        adsr0.state = Adsr::ADSR_OFF;
        adsr1.state = Adsr::ADSR_OFF;
        adsr2.state = Adsr::ADSR_OFF;
        adsr3.state = Adsr::ADSR_OFF;
     }
    void retrigger(){
        reset();
    }
    
    void noteOff(){
        adsr0.release();
        adsr1.release();
        adsr2.release();
        adsr3.release();
    }
    
    void update(int clock){
        setParams();
    }
    
    // ===============================================================================================
    //   RENDER
    // ===============================================================================================
    void render(int clock, AudioBuffer<float>& buffer){
        ScopedNoDenormals noDenormals;
        int sr = sampleRate * OVERSAMPLING;
        
        // Buffers
        auto* channelDataL = buffer.getWritePointer (0);
        auto* channelDataR = buffer.getWritePointer (1);

        // Tables
        float * table0 = osc0.tables[(int)par[P_OSC1_WAV]];
        float * table1 = osc0.tables[(int)par[P_OSC2_WAV]];
        float * table2 = osc0.tables[wSin];
        
        // Prepare
        float volVelo = velocity / par[P_NOVOICES];
        
        // Calulate each Sample
        for (int i=0; i<samplesPerBlock; ++i) {
            int p0 = tablePos0;
            int p1 = tablePos1;
            p0 = p0 / (1.0f + par[P_OSC1_PULSE] * 0.01f);
            p1 = p1 / (1.0f + par[P_OSC2_PULSE] * 0.01f);
            float v0 = osc0.interpolate(osc0.checkPos(p0 + par[P_OSC1_PHASE] / 360.0f * sr), table0);
            float v1 = osc0.interpolate(osc0.checkPos(p1 + par[P_OSC2_PHASE] / 360.0f * sr), table1);
            float vSub = osc0.interpolate(osc0.checkPos(tablePosSub), table2);

            v0 *= volVelo;
            v0 *=  DecibelToLinear(par[P_OSC1_VOL]);
            
            v1 *= volVelo;
            v1 *=  DecibelToLinear(par[P_OSC2_VOL]);
            
            vSub = vSub * adsr0.output * par[P_OSC1_SUB];
            float vol = DecibelToLinear(par[P_VOLUME]);
            
            // Mono
            float mono = (v0 + v1 + vSub)  * vol / 3.0f;
            
            // Filter
            mono = filter0.process(mono);
            
            // ADSR
            mono *= smoothMaster.processLP(adsr0.output);
            
            // Pan
            float vSumL = mono * (1.0f - par[P_PAN]);
            float vSumR = mono * par[P_PAN];

            // Bounds Check
            if(vSumL > 1.0f){
                vSumL = 1.0f;
            }
            if(vSumL < -1.0f){
                vSumL = -1.0f;
            }
            
            if(vSumR > 1.0f){
                vSumR = 1.0f;
            }
            if(vSumR < -1.0f){
                vSumR = -1.0f;
            }
            
            channelDataL[i] += vSumL;
            channelDataR[i] += vSumR;
            
            // Move the Osc
            int midiNote0 = noteNumber + par[P_OSC1_SEMI] + 12 * par[P_OSC1_OCT];
            float freq0 = tuneTable[midiNote0] * tuneMulti[midiNote0 % 12];
            
            int midiNote1 = noteNumber + par[P_OSC2_SEMI] + 12 * par[P_OSC2_OCT];
            float freq1 = tuneTable[midiNote1] * tuneMulti[midiNote1 % 12];
            
            float t = par[0] / 440.0f;
            
            // fine tune
            freq0 = freq0 + freq0 *  par[P_OSC1_FINE] * 0.01f;
            freq1 = freq1 + freq1 *  par[P_OSC2_FINE] * 0.01f;
            
            // move pos
            tablePos0 += OVERSAMPLING * freq0  * t ;
            
            bool sync = false;
            if(tablePos0 < lastPos0){
                sync = true;
            }
            
            if(sync && par[P_OSC2_SYNC] ){
                tablePos1 = 0;
                sync = false;
                lastPos0 = 1;
            }else{
                tablePos1 += OVERSAMPLING * freq1  * t;
                lastPos0 = tablePos0;
            }
            
            tablePosSub += OVERSAMPLING * freq0 / 3.0f * t;
            
            // bounds check
            tablePos0 = osc0.checkPos(tablePos0);
            tablePos1 = osc0.checkPos(tablePos1);
            tablePosSub = osc0.checkPos(tablePosSub);
        }

        // General - once per Block
        clock += samplesPerBlock;
        adsr0.tick(samplesPerBlock);
        if(adsr0.state == Adsr::ADSR_DONE){
            adsr0.state = Adsr::ADSR_OFF;
            std::cout << "End of  voice "  << vid << std::endl;
            active = false;
        }
    }
    
private:
    int sampleRate;
    int sr;
    int samplesPerBlock;
    int adsr;
    int sampleId = 0;
    int lastBeat = -1;
    Osc osc0;
    Osc osc1;
};
    
#endif /* Voice_h */
