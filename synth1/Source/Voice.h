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
    int tablePos0 = 0;

    Voice(){
        waveTable = new WaveTable();
    }
    
    ~Voice(){
           delete waveTable;
    }
    
    void init (double sampleRate, int samplesPerBlock){
        this->sampleRate = sampleRate;
        this->samplesPerBlock = samplesPerBlock;
        waveTable->init(sampleRate, samplesPerBlock);
    }
    
    void setup(){
        freq = tuneTable[noteNumber] * tuneMulti[noteNumber % 12];
        tablePos0 = 0;
        active = true;
    }
    
    void update(int clock){
        
    }
    
    void render(int clock, AudioBuffer<float>& buffer){
        
        int sr = sampleRate * OVERSAMPLING;
        ScopedNoDenormals noDenormals;
    
        auto* channelDataL = buffer.getWritePointer (0);
        auto* channelDataR = buffer.getWritePointer (1);
    
        float *tableSin = waveTable->sinBuffer;
        float *tableSquare = waveTable->squareBuffer;
        float *tableSaw = waveTable->sawBuffer;
        float *tableTriangle = waveTable->triangleBuffer;
        float *tableWhite = waveTable->whiteBuffer;
        
        for (int i=0; i<samplesPerBlock; ++i) {
            //float v = (tableSin[tablePos0]  + tableSquare[tablePos0]) * velocity / par[1] * par[7];
             float v = tableSaw[tablePos0]  * velocity / par[1] * par[7];
            channelDataL[i] += v;
            channelDataR[i] += v;
            float t = par[0] / 440.0;
            tablePos0 += OVERSAMPLING * freq * t;
            if(tablePos0 >= sr){
                tablePos0 -= sr;
            }
        }
        clock += samplesPerBlock;
    }
    
private:
    int sampleRate;
    int samplesPerBlock;
    int adsr;
    int sampleId = 0;
    int lastBeat = -1;
};
    
#endif /* Voice_h */
