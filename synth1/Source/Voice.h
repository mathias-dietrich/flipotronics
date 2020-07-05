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
#include "FilterExtern/ModulationMatrix.h"
#include "FilterExtern/MoogLadderFilter.h"
#include "FilterExtern/SEMFilter.h"

#include "ReleasePool.h"

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
    
    float tablePosLfo1 = 0;
    float tablePosLfo2 = 0;
    float tablePosLfo3 = 0;
    float tablePosLfo4 = 0;
    
    Osc osc1;
    Osc osc2;
    
    Adsr adsr1;
    Adsr adsr2;
    Adsr adsr3;
    Adsr adsr4;
    
    Lfo lfo1;
    Lfo lfo2;
    Lfo lfo3;
    Lfo lfo4;
    
    float adsr0Target;
    float adsr0Target1;
    
    int lastPos0 = 1;
    
    Smooth smoothMaster;
    
    MultiModeLadderFilter filter1;
    MultiModeLadderFilter filter2;
    
    CMoogLadderFilter  filter3;
    CSEMFilter filter4;
    ReleasePool pool;
    
    Voice(){
        
        // ADSR
        adsr1.uid = 1;
        adsr2.uid = 2;
        adsr3.uid = 3;
        adsr4.uid = 4;
        
        lfo1.uid = 1;
        lfo2.uid = 2;
        lfo3.uid = 3;
        lfo4.uid = 4;
        
        filter3.reset();
        filter4.reset();
    }
    
    ~Voice(){

    }

    void init (double sampleRate, int samplesPerBlock, float * par){
        this->sampleRate = sampleRate;
        this->sr = sampleRate * OVERSAMPLING;
        this->samplesPerBlock = samplesPerBlock;

        // OSC
        osc1.init(sampleRate,samplesPerBlock);
        osc2.init(sampleRate,samplesPerBlock);
        
        // ADSR
        adsr1.init(sampleRate,samplesPerBlock);
        adsr2.init(sampleRate,samplesPerBlock);
        adsr3.init(sampleRate,samplesPerBlock);
        adsr4.init(sampleRate,samplesPerBlock);
        
        adsr0Target = 0;
        
        // LFO
        lfo1.init(sampleRate,samplesPerBlock);
        lfo2.init(sampleRate,samplesPerBlock);
        lfo3.init(sampleRate,samplesPerBlock);
        lfo4.init(sampleRate,samplesPerBlock);
        
        // Smooth
        smoothMaster.setup(1,sampleRate);
        
        // Filter
        filter1.setSampleRate(sampleRate);
        filter2.setSampleRate(sampleRate);
        Model::of().isUpdateParams = true;
        setParams(par);
    }
    
    void setParams(float * par){
        adsr1.attackTimeMsec = par[P_ADSR1_ATTACK];
        adsr1.decayTimeMsec = par[P_ADSR1_DECAY];
        adsr1.sustainLevel = par[P_ADSR1_SUSTAIN];
        adsr1.releaseTimeMsec = par[P_ADSR1_RELEASE];
        adsr1.setAttackCurve(par[P_ADSR1_ATTACK_CURVE]);
        adsr1.setDecayCurve(par[P_ADSR1_DECAY_CURVE]);
        adsr1.setSustainCurve(par[P_ADSR1_SUSTAIN_CURVE]);
        adsr1.setReleaseCurve(par[P_ADSR1_RELEASE_CURVE]);
        adsr1.filterTarget = par[P_ADSR1_FILTER];
        adsr1.pitchTarget = par[P_ADSR1_PITCH];
        adsr1.ampTarget = par[P_ADSR1_AMP];
        adsr1.fxTarget = par[P_ADSR1_FX];
        adsr1.holdTimeMsec = par[P_ADSR1_HOLD];
        adsr1.delayTimeMsec = par[P_ADSR1_DELAY];
        adsr1.trigger = par[P_ADSR1_TRIGGER];
        adsr1.triggerTreshold = par[P_ADSR1_TRESHOLD];
        
        adsr2.attackTimeMsec = par[P_ADSR2_ATTACK];
        adsr2.decayTimeMsec = par[P_ADSR2_DECAY];
        adsr2.sustainLevel = par[P_ADSR2_SUSTAIN];
        adsr2.releaseTimeMsec = par[P_ADSR2_RELEASE];
        adsr2.setAttackCurve(par[P_ADSR2_ATTACK_CURVE]);
        adsr2.setDecayCurve(par[P_ADSR2_DECAY_CURVE]);
        adsr2.setSustainCurve(par[P_ADSR2_SUSTAIN_CURVE]);
        adsr2.setReleaseCurve(par[P_ADSR2_RELEASE_CURVE]);

        adsr2.filterTarget = par[P_ADSR2_FILTER];
        adsr2.pitchTarget = par[P_ADSR2_PITCH];
        adsr2.ampTarget = par[P_ADSR2_AMP];
        adsr2.fxTarget = par[P_ADSR2_FX];
        adsr2.holdTimeMsec = par[P_ADSR2_HOLD];
        adsr2.delayTimeMsec = par[P_ADSR2_DELAY];
        adsr2.trigger = par[P_ADSR2_TRIGGER];
        adsr2.triggerTreshold = par[P_ADSR2_TRESHOLD];
        
        adsr3.attackTimeMsec = par[P_ADSR3_ATTACK];
        adsr3.decayTimeMsec = par[P_ADSR3_DECAY];
        adsr3.sustainLevel = par[P_ADSR3_SUSTAIN];
        adsr3.releaseTimeMsec = par[P_ADSR3_RELEASE];
        adsr3.setAttackCurve(par[P_ADSR3_ATTACK_CURVE]);
        adsr3.setDecayCurve(par[P_ADSR3_DECAY_CURVE]);
        adsr3.setSustainCurve(par[P_ADSR3_SUSTAIN_CURVE]);
        adsr3.setReleaseCurve(par[P_ADSR3_RELEASE_CURVE]);

        adsr3.filterTarget = par[P_ADSR3_FILTER];
        adsr3.pitchTarget = par[P_ADSR3_PITCH];
        adsr3.ampTarget = par[P_ADSR3_AMP];
        adsr3.fxTarget = par[P_ADSR3_FX];
        adsr3.holdTimeMsec = par[P_ADSR3_HOLD];
        adsr3.delayTimeMsec = par[P_ADSR3_DELAY];
        adsr3.trigger = par[P_ADSR3_TRIGGER];
        adsr3.triggerTreshold = par[P_ADSR3_TRESHOLD];

        adsr4.attackTimeMsec = par[P_ADSR4_ATTACK];
        adsr4.decayTimeMsec = par[P_ADSR4_DECAY];
        adsr4.sustainLevel = par[P_ADSR4_SUSTAIN];
        adsr4.releaseTimeMsec = par[P_ADSR4_RELEASE];
        adsr4.setAttackCurve(par[P_ADSR4_ATTACK_CURVE]);
        adsr4.setDecayCurve(par[P_ADSR4_DECAY_CURVE]);
        adsr4.setSustainCurve(par[P_ADSR4_SUSTAIN_CURVE]);
        adsr4.setReleaseCurve(par[P_ADSR4_RELEASE_CURVE]);

        adsr4.filterTarget = par[P_ADSR4_FILTER];
        adsr4.pitchTarget = par[P_ADSR4_PITCH];
        adsr4.ampTarget = par[P_ADSR4_AMP];
        adsr4.fxTarget = par[P_ADSR4_FX];
        adsr4.holdTimeMsec = par[P_ADSR4_HOLD];
        adsr4.delayTimeMsec = par[P_ADSR4_DELAY];
        adsr4.trigger = par[P_ADSR4_TRIGGER];
        adsr4.triggerTreshold = par[P_ADSR4_TRESHOLD];
        
        filter1.setFilterType(par[P_FILTER1_TYPE] );
        filter1.setCutoff(par[P_FILTER1_FREQ]);
        filter1.setResonance(par[P_FILTER1_RES] / 100.0f);

        filter2.setFilterType(par[P_FILTER2_TYPE] );
        filter2.setCutoff(par[P_FILTER2_FREQ]);
        filter2.setResonance(par[P_FILTER2_RES] / 100.0f);
    }
    
    void reset(float * par){
        tablePos0 = 0;
        tablePos1 = sampleRate/2;
        tablePos0_n1 = -1;
        
        setParams(par);
        
        active = true;
        adsr1.start();
        adsr2.start();
        adsr3.start();
        adsr4.start();
        
        lastPos0 = 1;
        
        filter1.reset();
        filter1.setBoost(true);
        
        filter2.reset();
        filter2.setBoost(true);
        
        int midiNote1 = noteNumber + par[P_OSC2_SEMI] + 12 * par[P_OSC2_OCT];
        float freq1 = Model::of().tuneTable[midiNote1] * Model::of().tuneMulti[midiNote1 % 12];
        osc1.oscillator.m_dOscFo = freq1;
        osc1.oscillator.update();
        osc1.oscillator.startOscillator();
    }
    
    void kill(){
        active = false;
        adsr1.state = Adsr::ADSR_OFF;
        adsr2.state = Adsr::ADSR_OFF;
        adsr3.state = Adsr::ADSR_OFF;
        adsr4.state = Adsr::ADSR_OFF;
     }
    void retrigger(float * par){
        reset(par);
    }
    
    void noteOff(){
        adsr1.release();
        adsr2.release();
        adsr3.release();
        adsr4.release();
    }
    
    void update(int clock, float * par){
        if(Model::of().isUpdateParams){
            setParams(par);
        }
        Model::of().isUpdateParams = false;
    }
    
    // ===============================================================================================
    //   RENDER
    // ===============================================================================================
    void render(int clock, AudioBuffer<float>& buffer, float (&p)[MAXPARAM]){
        

        ScopedNoDenormals noDenormals;
        int sr = sampleRate * OVERSAMPLING;
        
        // Buffers
        auto* channelDataL = buffer.getWritePointer (0);
        auto* channelDataR = buffer.getWritePointer (1);

        // Tables
        float * table0 = osc1.tables[(int)p[P_OSC1_WAV]];
        float * table1 = osc2.tables[(int)p[P_OSC2_WAV]];
        float * table2 = osc2.tables[wSin];
        
        float * tableLfo1 = lfo1.tables[(int)p[P_LFO1_WAV]];
        float * tableLfo2 = lfo2.tables[(int)p[P_LFO2_WAV]];
        float * tableLfo3 = lfo3.tables[(int)p[P_LFO3_WAV]];
        float * tableLfo4 = lfo4.tables[(int)p[P_LFO4_WAV]];
        
        // Prepare
        float volVelo = velocity ;
        
        // Calulate each Sample
        for (int i=0; i<samplesPerBlock; ++i) {
            int p0 = tablePos0;
            int p1 = tablePos1;
            p0 = p0 / (1.0f + p[P_OSC1_PULSE] * 0.01f);
            p1 = p1 / (1.0f + p[P_OSC2_PULSE] * 0.01f);
            float v0 = osc1.interpolate(osc1.checkPos(p0 + p[P_OSC1_PHASE] / 360.0f * sr), table0);
            float v1 = osc1.interpolate(osc1.checkPos(p1 + p[P_OSC2_PHASE] / 360.0f * sr), table1);
            
            v0 = osc1.oscillator.doOscillate();
            
            float vSub = osc1.interpolate(osc1.checkPos(tablePosSub), table2);

            v0 *= volVelo;
            v0 *=  DecibelToLinear(p[P_OSC1_VOL]);
            
            v1 *= volVelo;
            v1 *=  DecibelToLinear(p[P_OSC2_VOL]);
            
            vSub = vSub * adsr1.output * p[P_OSC1_SUB];
            float vol = DecibelToLinear(p[P_VOLUME]);
            
            // Mono
            float mono = (v0 + v1 + vSub)  * vol ;
            
            float lfo0Output = tableLfo1[((int)tablePosLfo1)];
            
             // Filter
            if(filter1.getFilterType() != OFF2){
                float cutoff = p[P_FILTER1_FREQ];
                cutoff *= 1.0 - p[P_LFO1_FILTER] * (1.0 + lfo0Output) * 0.5;
                filter1.setCutoff(cutoff);
                filter1.setDrive(p[P_FILTER1_DRIVE]);
                mono = filter1.process(mono);
            }
            
            // LFO Amp
            mono *= 1.0 - p[P_LFO1_VOL] * lfo0Output;
            
            // ADSR
            mono *= smoothMaster.processLP(adsr1.output);
            
            // Pan
            float vSumL = mono * (1.0f - p[P_PAN]);
            float vSumR = mono * p[P_PAN];

            // Bounds Check
            if(vSumL > 1.0f) {
                vSumL = 1.0f;
            }
            if(vSumL < -1.0f) {
                vSumL = -1.0f;
            }
            if(vSumR > 1.0f) {
                vSumR = 1.0f;
            }
            if(vSumR < -1.0f) {
                vSumR = -1.0f;
            }
            
            channelDataL[i] += vSumL;
            channelDataR[i] += vSumR;
            
// Move the Osc forward  =======================================================================
           
            // calc Midi Note Osc 1
            int midiNote0 = noteNumber + p[P_OSC1_SEMI] + 12 * p[P_OSC1_OCT];
            
            // Get frequency from the Tuning Table
            float freq0 = Model::of().tuneTable[midiNote0] * Model::of().tuneMulti[midiNote0 % 12];
            
            // calc Midi Note Osc 2
            int midiNote1 = noteNumber + p[P_OSC2_SEMI] + 12 * p[P_OSC2_OCT];
            
            // Get frequency from the Tuning Table
            float freq1 = Model::of().tuneTable[midiNote1] * Model::of().tuneMulti[midiNote1 % 12];
            
            // fine tune
            freq0 = freq0 + freq0 *  p[P_OSC1_FINE] * 0.01f;
            freq1 = freq1 + freq1 *  p[P_OSC2_FINE] * 0.01f;
            
            // LFO Pitch to Osc
            freq0 *= 1.0 - p[P_LFO1_PITCH] *  lfo0Output;
            freq1 *= 1.0 - p[P_LFO1_PITCH] *  lfo0Output;
            
            // fine tuning from UI relative to 440Hz
            float t = p[0] / 440.0f;
            
            // move pos OSC
            tablePos0 += OVERSAMPLING * freq0  * t ;
            
            bool sync = false;
            if(tablePos0 < lastPos0){
                sync = true;
            }
            
            if(sync && p[P_OSC2_SYNC] ){
                tablePos1 = 0;
                sync = false;
                lastPos0 = 1;
            }else{
                tablePos1 += OVERSAMPLING * freq1  * t;
                lastPos0 = tablePos0;
            }
            
            tablePosSub += OVERSAMPLING * freq0 / 3.0f * t;
            
            // Move LFO
            tablePosLfo1 += OVERSAMPLING * p[P_LFO1_FREQ];
            tablePosLfo2 += OVERSAMPLING * p[P_LFO2_FREQ];
            tablePosLfo3 += OVERSAMPLING * p[P_LFO3_FREQ];
            tablePosLfo4 += OVERSAMPLING * p[P_LFO4_FREQ];
            
            // bounds check OSC
            tablePos0 = osc1.checkPos(tablePos0);
            tablePos1 = osc2.checkPos(tablePos1);
            tablePosSub = osc2.checkPos(tablePosSub);
            
             // bounds check LFO
            tablePosLfo1 = lfo1.checkPos(tablePosLfo1);
            tablePosLfo2 = lfo1.checkPos(tablePosLfo2);
            tablePosLfo3 = lfo1.checkPos(tablePosLfo3);
            tablePosLfo4 = lfo1.checkPos(tablePosLfo4);
            
            dInc += 1.0f / 880.0f;
            if(dInc >= 1.0){
                dInc -= 1.0;
            }
        }

        // General - once per Block
        clock += samplesPerBlock;
        adsr1.tick(samplesPerBlock);
        if(adsr1.state == Adsr::ADSR_DONE){
            adsr1.state = Adsr::ADSR_OFF;
           // std::cout << "End of  voice "  << vid << std::endl;
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
    
    double dModulo;
    double dInc;
    
};
    
#endif /* Voice_h */
