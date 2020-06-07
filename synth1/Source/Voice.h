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
    double freq = 440;
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
    
    void reset(){
        freq = tuneTable[noteNumber] * tuneMulti[noteNumber % 12];
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
        float *tableSin = waveTable->sinBuffer;
        float *tableSquare = waveTable->squareBuffer;
        float *tableSaw = waveTable->sawBuffer;
        float *tableTriangle = waveTable->triangleBuffer;
        float *tableWhite = waveTable->whiteBuffer;
        
        for (int i=0; i<samplesPerBlock; ++i) {
            float v = interpolate(tablePos0, tableTriangle);
           // float v = tableSin[((int)tablePos0)];
            
             v = v * velocity / par[P_NOVOICES] ;
           // v += 0.2f * tableSquare[((int)tablePos1)]  * velocity / par[P_NOVOICES] ;
           // v += tableSin[((int)tablePosSub)]  * velocity / par[P_NOVOICES] * par[P_OSC1_SUB];
           // v += lastF1 * 0.99f;
           // v = v / 4.0f;
            
            lastF0 = v * 0.99f;
            lastF1 = lastF0 * 0.99f;
            
            v = v * par[7];
            
            // check >Level
            if(v > 1.0f){
                v = 1.0f;
            }
            if(v < -1.0f){
                v = -1.0f;
            }
            
            v = v * adsr0.vol;
            
            channelDataL[i] += v;
            channelDataR[i] += v;
            float t = par[0] / 440.0;
            
            // move pos
            tablePos0 += OVERSAMPLING * (freq + par[P_OSC1_FINE])  * t;
            tablePos1 += OVERSAMPLING * (freq * 1.01 + par[P_OSC1_FINE])  * t;
            tablePosSub += OVERSAMPLING * freq /3.0 * t;
            
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
