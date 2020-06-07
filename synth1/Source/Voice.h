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


class Voice {       // The class

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
    
    void reset(){
        
        tablePos0 = 0;
        tablePos1 = sampleRate/2;
        tablePos0_n1 = -1;
        
        adsr0.delayTimeMsec = 0;
        adsr0.attackTimeMsec = 0;
        adsr0.decayTimeMsec = 200;
        adsr0.sustainLevel = 0.5;
        adsr0.releaseTimeMsec = 400;
        
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
        
    }
    
    void render(int clock, AudioBuffer<float>& buffer){
        ScopedNoDenormals noDenormals;
        int sr = sampleRate * OVERSAMPLING;
        auto* channelDataL = buffer.getWritePointer (0);
        auto* channelDataR = buffer.getWritePointer (1);

        float * table0;
        switch(((int)par[P_OSC1_WAV])){
            case 0:
                table0 =  waveTable->sinBuffer;
                break;
                
            case 1:
                table0 =  waveTable->squareBuffer;
                break;
                
            case 2:
                table0 =  waveTable->sawBuffer;
                break;
                
            case 3:
                table0 =  waveTable->triangleBuffer;
                break;
                
            case 4:
                table0 =  waveTable->whiteBuffer;
                break;
                
            case 5:
                table0 =  waveTable->whiteBuffer;
                break;
            
            case 6:
                table0 =  waveTable->whiteBuffer;
                break;
        }
        float * table1;
        switch(((int)par[P_OSC2_WAV])){
            case 0:
                table1 =  waveTable->sinBuffer;
                break;
                
            case 1:
                table1 =  waveTable->squareBuffer;
                break;
                
            case 2:
                table1 =  waveTable->sawBuffer;
                break;
                
            case 3:
                table1 =  waveTable->triangleBuffer;
                break;
                
            case 4:
                table1 =  waveTable->whiteBuffer;
                break;
                
            case 5:
                table1 =  waveTable->triangleBuffer;
                break;
                
            case 6:
                table1 =  waveTable->whiteBuffer;
                break;
        }
        float * table2 = waveTable->sinBuffer;
        
        for (int i=0; i<samplesPerBlock; ++i) {
            int p0 = tablePos0;
            int p1 = tablePos1;
            p0 = p0 / (1.0f + par[P_OSC1_PULSE] / 100.0);
            p1 = p1 / (1.0f + par[P_OSC2_PULSE] / 100.0);
            float v0 = interpolate(checkPos(p0 + par[P_OSC1_PHASE] * sr), table0);
            float v1 = interpolate(checkPos(p1 + par[P_OSC2_PHASE] * sr), table1);
            float vSub = interpolate(checkPos(tablePosSub), table2);

            v0 = v0 * velocity / par[P_NOVOICES];
            v0 = v0 * adsr0.vol * par[P_OSC1_VOL];
            
            v1 = v1 * velocity / par[P_NOVOICES];
            v1 = v1 * adsr0.vol * par[P_OSC2_VOL];
            
            vSub = vSub * adsr0.vol * par[P_OSC1_SUB];
            
            float mono = (v0 + v1 + vSub)  * par[P_VOLUME] / 3.0f;
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
            
            float t = par[0] / 440.0;
            
            // fine tune
            freq0 = freq0 + freq0 *  par[P_OSC1_FINE] / 100.0f;
            freq1 = freq1 + freq1 *  par[P_OSC2_FINE] / 100.0f;
            
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
                tablePos1 += OVERSAMPLING * freq1  * t ;
                lastPos0 = tablePos0;
            }
            
            
            tablePosSub += OVERSAMPLING * freq0 /3.0 * t;
            
            // bounds check
            tablePos0 = checkPos(tablePos0 );
            tablePos1 = checkPos(tablePos1 );
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
