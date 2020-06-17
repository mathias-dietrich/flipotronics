//
//  Osc.h
//  synth1
//
//  Created by Mathias Dietrich on 15.06.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef Osc_h
#define Osc_h

#include <stdio.h>
#include <JuceHeader.h>
#include "WaveTable.h"
#include "Enum.h"

class Osc{
    public:
    
    float * tables[20];
    
    // wSin, wSaw, wTriangle, wSquare, wShark, wWhite, wPink, wBrown, wTable
    
    Osc(){
        waveTable = WaveTable::of();
        tables[wSin] = waveTable->sinBuffer;
        tables[wSaw] = waveTable->squareBuffer;
        tables[wTriangle] = waveTable->sawBuffer;
        tables[wSquare] = waveTable->triangleBuffer;
        tables[wShark] = waveTable->whiteBuffer;
        tables[wWhite] = waveTable->whiteBuffer;
        tables[wPink] = waveTable->whiteBuffer;
        tables[wBrown] = waveTable->whiteBuffer;
        tables[wTable] = waveTable->whiteBuffer;
    }
    
    ~Osc(){

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
    
    private:
        WaveTable * waveTable;
        float sampleRate;
        float samplesPerBlock;
        float sr;
        
};
#endif /* Osc_h */
