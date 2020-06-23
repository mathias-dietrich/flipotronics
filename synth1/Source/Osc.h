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

    }
    
    ~Osc(){

    }
    
    /*
    forcedinline float interpolateSample(int currentIndex, int tableSize, float * table) noexcept
    {
        auto index0 = (unsigned int) currentIndex;
        auto index1 = index0 == (tableSize - 1) ? (unsigned int) 0 : index0 + 1;
        auto frac = currentIndex - (float) index0;
        auto value0 = table[index0];
        auto value1 = table[index1];
        return value0 + frac * (value1 - value0);
    }
     */
    
    forcedinline float interpolate(int currentIndex, float * table ) noexcept{
        auto index0 = (unsigned int) currentIndex;
        auto index1 = index0 == (waveTable->sr - 1) ? (unsigned int) 0 : index0 + 1;
        auto frac = currentIndex - (float) index0;
        auto value0 = table[index0];
        auto value1 = table[index1];
        return value0 + frac * (value1 - value0);
    }
    
    void init (double sampleRate, int samplesPerBlock){
        this->sampleRate = sampleRate;
        this->sr = sampleRate * OVERSAMPLING;
        this->samplesPerBlock = samplesPerBlock;
        
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
