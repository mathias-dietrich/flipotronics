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

class Voice {

public:
    int vid;
    bool active;
    WaveTable *waveTable;
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
    
    int lastPos0 = 1;
    
    Voice(){
        waveTable = new WaveTable();
    }
    
    ~Voice(){
           delete waveTable;
    }
    
    inline int checkPos(int pos){
        while(pos < 0){
            pos += sr;
        }
        while(pos >= sr){
           pos -= sr;
        }
        return pos;
    }
    
    inline float interpolate(int pos, float * buffer ){
        int prevPos = checkPos(pos - 1);
        int nextPos = checkPos(pos + 1);
        return (buffer[prevPos] + buffer[pos] + buffer[nextPos]) / 3.0f;
    }
    
    void init (double sampleRate, int samplesPerBlock){
        this->sampleRate = sampleRate;
        sr = sampleRate * OVERSAMPLING;
        this->samplesPerBlock = samplesPerBlock;
        waveTable->init(sampleRate, samplesPerBlock);
        adsr0.init(sampleRate,samplesPerBlock);
        adsr1.init(sampleRate,samplesPerBlock);
        adsr2.init(sampleRate,samplesPerBlock);
        adsr3.init(sampleRate,samplesPerBlock);
    }
    
    void kill(){
        active = false;
        adsr0.state = Adsr::ADSR_OFF;
        adsr1.state = Adsr::ADSR_OFF;
        adsr2.state = Adsr::ADSR_OFF;
        adsr3.state = Adsr::ADSR_OFF;
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
    }
    
    void noteOff(){
        adsr0.state = Adsr::ADSR_RELEASE;
        adsr1.state = Adsr::ADSR_RELEASE;
        adsr2.state = Adsr::ADSR_RELEASE;
        adsr3.state = Adsr::ADSR_RELEASE;
    }
    
    void update(int clock){
        setParams();
    }
    
    void render(int clock, AudioBuffer<float>& buffer){
        ScopedNoDenormals noDenormals;
        int sr = sampleRate * OVERSAMPLING;
        auto* channelDataL = buffer.getWritePointer (0);
        auto* channelDataR = buffer.getWritePointer (1);

        float * table0;
        switch(((int)par[P_OSC1_WAV])){
            case wSin:
                table0 =  waveTable->sinBuffer;
                break;
                
            case wSquare:
                table0 =  waveTable->squareBuffer;
                break;
                
            case wSaw:
                table0 =  waveTable->sawBuffer;
                break;
                
            case wTriangle:
                table0 =  waveTable->triangleBuffer;
                break;
                
            case wWhite:
                table0 =  waveTable->whiteBuffer;
                break;
                
            case wPink:
                table0 =  waveTable->whiteBuffer;
                break;
            
            case wBrown:
                table0 =  waveTable->whiteBuffer;
                break;
                
            case wShark:
                table0 =  waveTable->whiteBuffer;
                break;
                
            case wTable:
                table0 =  waveTable->whiteBuffer;
                break;
        }
        float * table1;
        switch(((int)par[P_OSC2_WAV])){
            case wSin:
                table1 =  waveTable->sinBuffer;
                break;
                
            case wSquare:
                table1 =  waveTable->squareBuffer;
                break;
                
            case wSaw:
                table1 =  waveTable->sawBuffer;
                break;
                
            case wTriangle:
                table1 =  waveTable->triangleBuffer;
                break;
                
            case wWhite:
                table1 =  waveTable->whiteBuffer;
                break;
                
            case wPink:
                table1 =  waveTable->whiteBuffer;
                break;
            
            case wBrown:
                table1 =  waveTable->whiteBuffer;
                break;
                
            case wShark:
                table1 =  waveTable->whiteBuffer;
                break;
                
            case wTable:
                table1 =  waveTable->whiteBuffer;
                break;
        }
        float * table2 = waveTable->sinBuffer;
        
        float volVelo = velocity / par[P_NOVOICES];
        for (int i=0; i<samplesPerBlock; ++i) {
            int p0 = tablePos0;
            int p1 = tablePos1;
            p0 = p0 / (1.0f + par[P_OSC1_PULSE] * 0.01f);
            p1 = p1 / (1.0f + par[P_OSC2_PULSE] * 0.01f);
            float v0 = interpolate(checkPos(p0 + par[P_OSC1_PHASE] / 360.0f * sr), table0);
            float v1 = interpolate(checkPos(p1 + par[P_OSC2_PHASE] / 360.0f * sr), table1);
            float vSub = interpolate(checkPos(tablePosSub), table2);

           // volVelo *= adsr0.output;
            v0 *= volVelo;
            v0 *=  DecibelToLinear(par[P_OSC1_VOL]);
            
            v1 *= volVelo;
            v1 *=  DecibelToLinear(par[P_OSC2_VOL]);
            
            vSub = vSub * adsr0.output * par[P_OSC1_SUB];
            float vol = DecibelToLinear(par[P_VOLUME]);
            float mono = (v0 + v1 + vSub)  * vol / 3.0f;
            float vSumL = mono * (1.0f - par[P_PAN]);
            float vSumR = mono * par[P_PAN];
            
            // check >Level
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
            tablePos0 = checkPos(tablePos0);
            tablePos1 = checkPos(tablePos1);
            tablePosSub = checkPos(tablePosSub);
            
            adsr0.tick();
        }
        clock += samplesPerBlock;
        if(adsr0.state == Adsr::ADSR_DONE){
            adsr0.state = Adsr::ADSR_OFF;
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
};
    
#endif /* Voice_h */
