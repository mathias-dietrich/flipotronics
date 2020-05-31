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

class Voice {       // The class

public:
    int vid;
    bool active;
    WaveTable *waveTable;
    double freq = 880;

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
    
    void render(int clock, AudioBuffer<float>& buffer){
        
      ScopedNoDenormals noDenormals;
    
       auto* channelDataL = buffer.getWritePointer (0);
       auto* channelDataR = buffer.getWritePointer (1);
    
        float *table = waveTable->sinBuffer;
        
        
        for (int i=0; i<samplesPerBlock; ++i) {
            double bpm = 120.0;
            double secconds = clock / sampleRate;
            int sixteens = 2 * secconds * 60.0 / bpm;
            
            if(lastBeat != sixteens){
                 std::cout << sixteens << std::endl;
                lastBeat = sixteens;
                adsr = sampleRate / 16;
            }
            
            if(adsr > 0){
                --adsr;
                channelDataL[i] =  table[sampleId];
                channelDataR[i] =  table[sampleId];
                sampleId += freq;
                if(sampleId >= sampleRate){
                    sampleId -= sampleRate;
                }
            }else{
                sampleId = 0;
                channelDataL[i] =  0;
                channelDataR[i] =  0;
            }
            ++clock;
        }
    }
    
private:
    int sampleRate;
    int samplesPerBlock;
    int adsr;
    int sampleId = 0;
    int lastBeat = -1;
};
    

#endif /* Voice_h */
