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
#include "ModMatrix.h"
#include "Matrix.h"

class Voice {

public:
    int vid;
    bool active;
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
    
    Osc osc1_A;
    Osc osc2_A;
    Osc subOsc_A;
    
    Osc osc1_B;
    Osc osc2_B;
    Osc subOsc_B;
    
    Osc osc1_C;
    Osc osc2_C;
    Osc subOsc_C;
    
    Osc osc1_D;
    Osc osc2_D;
    Osc subOsc_D;
    
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
    
    MultiModeLadderFilter filter1L;
    MultiModeLadderFilter filter1R;
    
    MultiModeLadderFilter filter2L;
    MultiModeLadderFilter filter2R;
    
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
        this->par = par;
        
        // OSC
        osc1_A.par = par;
        osc2_A.par = par;
        subOsc_A.par = par;
        osc1_A.init(1,sampleRate,samplesPerBlock);
        osc2_A.init(2,sampleRate,samplesPerBlock);
        subOsc_A.init(3,sampleRate,samplesPerBlock);
        
        osc1_B.par = par;
        osc2_B.par = par;
        subOsc_B.par = par;
        osc1_B.init(1,sampleRate,samplesPerBlock);
        osc2_B.init(2,sampleRate,samplesPerBlock);
        subOsc_B.init(3,sampleRate,samplesPerBlock);
        
        osc1_C.par = par;
        osc2_C.par = par;
        subOsc_C.par = par;
        osc1_C.init(1,sampleRate,samplesPerBlock);
        osc2_C.init(2,sampleRate,samplesPerBlock);
        subOsc_C.init(3,sampleRate,samplesPerBlock);
        
        osc1_D.par = par;
        osc2_D.par = par;
        subOsc_D.par = par;
        osc1_D.init(1,sampleRate,samplesPerBlock);
        osc2_D.init(2,sampleRate,samplesPerBlock);
        subOsc_D.init(3,sampleRate,samplesPerBlock);
    
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
        filter1L.setSampleRate(sampleRate);
        filter2R.setSampleRate(sampleRate);
        Model::of().isUpdateParams = true;
        setParams();
    }
    
    void setParams(){
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

        filter1L.setFilterType(par[P_FILTER1_TYPE] );
        filter1L.setCutoff(par[P_FILTER1_FREQ]);
        filter1L.setResonance(par[P_FILTER1_RES] / 100.0f);
        
        filter1R.setFilterType(par[P_FILTER1_TYPE] );
        filter1R.setCutoff(par[P_FILTER1_FREQ]);
        filter1R.setResonance(par[P_FILTER1_RES] / 100.0f);

        filter2L.setFilterType(par[P_FILTER2_TYPE] );
        filter2L.setCutoff(par[P_FILTER2_FREQ]);
        filter2L.setResonance(par[P_FILTER2_RES] / 100.0f);
        
        filter2R.setFilterType(par[P_FILTER2_TYPE] );
        filter2R.setCutoff(par[P_FILTER2_FREQ]);
        filter2R.setResonance(par[P_FILTER2_RES] / 100.0f);
    }
    
    void noteOn(int midiNote, float * par){
        this->noteNumber = midiNote;
        this->par = par;
        
        tablePos0 = 0;
        tablePos1 = sampleRate/2;
        tablePos0_n1 = -1;
        
        setParams();
        
        active = true;
        adsr1.start();
        adsr2.start();
        adsr3.start();
        adsr4.start();
        
        lastPos0 = 1;
        
        filter1L.reset();
        filter1L.setBoost(true);
        
        filter1R.reset();
        filter1R.setBoost(true);
        
        filter2L.reset();
        filter2L.setBoost(true);
        
        filter2R.reset();
        filter2R.setBoost(true);
        
        osc1_A.startNote(noteNumber);
        osc2_A.startNote(noteNumber);
        subOsc_A.startNote(noteNumber);
        
        osc1_B.startNote(noteNumber);
        osc2_B.startNote(noteNumber);
        subOsc_B.startNote(noteNumber);
        
        osc1_C.startNote(noteNumber);
        osc2_C.startNote(noteNumber);
        subOsc_C.startNote(noteNumber);
        
        osc1_D.startNote(noteNumber);
        osc2_D.startNote(noteNumber);
        subOsc_D.startNote(noteNumber);
    }
    
    void kill(){
        active = false;
        adsr1.state = Adsr::ADSR_OFF;
        adsr2.state = Adsr::ADSR_OFF;
        adsr3.state = Adsr::ADSR_OFF;
        adsr4.state = Adsr::ADSR_OFF;
     }
    
    void retrigger(float * par){
        osc1_A.retriggerNote();
        osc2_A.retriggerNote();
        subOsc_A.retriggerNote();
        
        osc1_B.retriggerNote();
        osc2_B.retriggerNote();
        subOsc_B.retriggerNote();
        
        osc1_C.retriggerNote();
        osc2_C.retriggerNote();
        subOsc_C.retriggerNote();
        
        osc1_D.retriggerNote();
        osc2_D.retriggerNote();
        subOsc_D.retriggerNote();
        
        adsr1.start();
       adsr2.start();
       adsr3.start();
       adsr4.start();
    }
    
    void noteOff(){
        adsr1.release();
        adsr2.release();
        adsr3.release();
        adsr4.release();
    }
    
    void update(int clock, float * par){
        this->par = par;
        if(Model::of().isUpdateParams){
            setParams();
        }
        Model::of().isUpdateParams = false;
    }
    
    // ===============================================================================================
    //   RENDER
    // ===============================================================================================
    void render(int clock, AudioBuffer<float>& buffer, float (&p)[MAXPARAM * 4], Matrix & matrix){

        ScopedNoDenormals noDenormals;

        osc1_A.par = p;
        osc2_A.par = p;
        subOsc_A.par = p;
        
        osc1_B.par = p;
        osc2_B.par = p;
        subOsc_B.par = p;

        osc1_C.par = p;
        osc2_C.par = p;
        subOsc_C.par = p;

        osc1_D.par = p;
        osc2_D.par = p;
        subOsc_D.par = p;

        // Buffers
        auto* channelDataL = buffer.getWritePointer (0);
        auto* channelDataR = buffer.getWritePointer (1);

        float * tableLfo1 = lfo1.tables[(int)p[P_LFO1_WAV]];
        float * tableLfo2 = lfo2.tables[(int)p[P_LFO2_WAV]];
        float * tableLfo3 = lfo3.tables[(int)p[P_LFO3_WAV]];
        float * tableLfo4 = lfo4.tables[(int)p[P_LFO4_WAV]];
        
        // Prepare
        float volVelo = velocity ;
        
        // Calulate each Sample
        for (int i=0; i<samplesPerBlock; ++i) {
            float v0_A = osc1_A.getSample((E_WaveType)p[P_OSC1_WAV]);
            float v1_A = osc2_A.getSample((E_WaveType)p[P_OSC2_WAV]);
            float vSub_A = subOsc_A.getSample((E_WaveType)p[P_OSC1_WAV]);

            v0_A *= volVelo;
            v0_A *=  DecibelToLinear(p[P_OSC1_VOL]);
            v1_A *= volVelo;
            v1_A *=  DecibelToLinear(p[P_OSC2_VOL]);
            vSub_A = vSub_A * adsr1.output * p[P_OSC1_SUB];
            
            float v0_B = osc1_B.getSample((E_WaveType)p[MAXPARAM + P_OSC1_WAV]);
            float v1_B = osc2_B.getSample((E_WaveType)p[MAXPARAM + P_OSC2_WAV]);
            float vSub_B = subOsc_B.getSample((E_WaveType)p[MAXPARAM + P_OSC1_WAV]);

            v0_B *= volVelo;
            v0_B *=  DecibelToLinear(p[MAXPARAM + P_OSC1_VOL]);
            v1_B *= volVelo;
            v1_B *=  DecibelToLinear(p[MAXPARAM + P_OSC2_VOL]);
            vSub_B = vSub_B * adsr1.output * p[MAXPARAM +P_OSC1_SUB];
            
            float v0_C = osc1_B.getSample((E_WaveType)p[2*MAXPARAM + P_OSC1_WAV]);
            float v1_C = osc2_B.getSample((E_WaveType)p[2*MAXPARAM + P_OSC2_WAV]);
            float vSub_C = subOsc_B.getSample((E_WaveType)p[2*MAXPARAM + P_OSC1_WAV]);

            v0_C *= volVelo;
            v0_C *=  DecibelToLinear(p[2*MAXPARAM + P_OSC1_VOL]);
            v1_C *= volVelo;
            v1_C *=  DecibelToLinear(p[2*MAXPARAM + P_OSC2_VOL]);
            vSub_C = vSub_C * adsr1.output * p[2*MAXPARAM + P_OSC1_SUB];
           
            float v0_D = osc1_B.getSample((E_WaveType)p[3*MAXPARAM + P_OSC1_WAV]);
            float v1_D = osc2_B.getSample((E_WaveType)p[3*MAXPARAM + P_OSC2_WAV]);
            float vSub_D = subOsc_B.getSample((E_WaveType)p[3*MAXPARAM + P_OSC1_WAV]);

            v0_D *= volVelo;
            v0_D *=  DecibelToLinear(p[3*MAXPARAM + P_OSC1_VOL]);
            v1_D *= volVelo;
            v1_D *=  DecibelToLinear(p[3*MAXPARAM + P_OSC2_VOL]);
            vSub_D = vSub_D * adsr1.output * p[3*MAXPARAM + P_OSC1_SUB];

            // Mono
            float vol = DecibelToLinear(p[P_VOLUME]);
             
            float a = v0_A * (1.0f-p[P_VOICESELECT_X]) * (1.0f-p[P_VOICESELECT_Y]);
            //float b = v0_B * p[P_VOICESELECT_X] * (1.0f-p[P_VOICESELECT_Y]);
         
            // float c = v0_C * (1.0f-p[P_VOICESELECT_X]) * p[P_VOICESELECT_Y];
            // float d = v0_D * p[P_VOICESELECT_X] * p[P_VOICESELECT_Y];

           // float vSumOscL = vol * a  * (1.0f - p[P_PAN]) + b  * (1.0f - p[MAXPARAM +P_PAN]) + c * (1.0f - p[2*MAXPARAM +P_PAN]) + d * (1.0f - p[3*MAXPARAM +P_PAN]);
           // float vSumOscR = vol * a  * p[P_PAN] + b * p[MAXPARAM +P_PAN] + c * p[2*MAXPARAM +P_PAN] + d  * p[3*MAXPARAM +P_PAN];
            
            float vSumOscL = vol * a * (1.0f - p[P_PAN]) ;
            float vSumOscR = vol * a  * p[P_PAN];
            
            // Feed Matrix
            float lfo0Output = matrix.sources[s_LFO1] = tableLfo1[((int)tablePosLfo1)];
            matrix.sources[s_LFO2] = tableLfo2[((int)tablePosLfo2)];
            matrix.sources[s_LFO3] = tableLfo3[((int)tablePosLfo3)];
            matrix.sources[s_LFO4] = tableLfo4[((int)tablePosLfo4)];
            
            // Calc Matrix
            matrix.calc(p);
            
             // Filter
            if(filter1L.getFilterType() != OFF2){
                float cutoff = p[P_FILTER1_FREQ];
                cutoff *= 1.0 - p[P_LFO1_FILTER] * (1.0 + lfo0Output) * 0.5;
                filter1L.setCutoff(cutoff);
                filter1L.setDrive(p[P_FILTER1_DRIVE]);
                vSumOscL = filter1L.process(vSumOscL);
            }
            if(filter1R.getFilterType() != OFF2){
                float cutoff = p[P_FILTER1_FREQ];
                cutoff *= 1.0 - p[P_LFO1_FILTER] * (1.0 + lfo0Output) * 0.5;
                filter1R.setCutoff(cutoff);
                filter1R.setDrive(p[P_FILTER1_DRIVE]);
                vSumOscR = filter1R.process(vSumOscR);
            }
            
            // LFO Amp
            vSumOscL *= 1.0 - p[P_LFO1_VOL] * lfo0Output;
            vSumOscR *= 1.0 - p[P_LFO1_VOL] * lfo0Output;
            
            // ADSR
            vSumOscL *= smoothMaster.processLP(adsr1.output);
            vSumOscR *= smoothMaster.processLP(adsr1.output);

            // Bounds Check
            if(vSumOscL > 1.0f) {
                vSumOscL = 1.0f;
            }
            if(vSumOscL < -1.0f) {
                vSumOscL = -1.0f;
            }
            if(vSumOscR > 1.0f) {
                vSumOscR = 1.0f;
            }
            if(vSumOscR < -1.0f) {
                vSumOscR = -1.0f;
            }
            
            channelDataL[i] += vSumOscL;
            channelDataR[i] += vSumOscR;
            
// Move the Osc forward  =======================================================================
            
            osc1_A.modFreq = matrix.targets[d_OSC1_FREQ];
            osc1_A.modVol = matrix.targets[d_OSC1_VOL];
            
            osc1_B.modFreq = matrix.targets[d_OSC1_FREQ];
            osc1_B.modVol = matrix.targets[d_OSC1_VOL];
            
            osc1_C.modFreq = matrix.targets[d_OSC1_FREQ];
            osc1_C.modVol = matrix.targets[d_OSC1_VOL];
            
            osc1_D.modFreq = matrix.targets[d_OSC1_FREQ];
            osc1_D.modVol = matrix.targets[d_OSC1_VOL];
            
            // Filter
            filter1L.modCutoff = matrix.targets[d_FILTER1_CUTOFF];
            filter1R.modCutoff = matrix.targets[d_FILTER1_CUTOFF];
            
            // OSC
            osc1_A.move();
            osc2_A.move();
            subOsc_A.move();
            
            osc1_B.move();
            osc2_B.move();
            subOsc_B.move();
            
            osc1_C.move();
            osc2_C.move();
            subOsc_C.move();
            
            osc1_D.move();
            osc2_D.move();
            subOsc_D.move();

            // Move LFO
            tablePosLfo1 += OVERSAMPLING * p[P_LFO1_FREQ];
            tablePosLfo2 += OVERSAMPLING * p[P_LFO2_FREQ];
            tablePosLfo3 += OVERSAMPLING * p[P_LFO3_FREQ];
            tablePosLfo4 += OVERSAMPLING * p[P_LFO4_FREQ];

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
    float * par;
};
    
#endif /* Voice_h */
