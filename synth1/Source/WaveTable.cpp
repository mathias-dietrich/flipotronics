//
//  WaveTable.cpp
//  synth1
//
//  Created by Mathias Dietrich on 31.05.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#include "WaveTable.h"
#include "Const.h"

WaveTable* WaveTable::instance = 0;

WaveTable* WaveTable::of()
{
    if (instance == 0)
    {
        instance = new WaveTable();
    }
    return instance;
}

void WaveTable::init (double sampleRate, int samplesPerBlock){
    
    // Avoid double inits
    if(this->sampleRate == sampleRate && this->samplesPerBlock == samplesPerBlock){
        return;
    }
    
    this->sampleRate = sampleRate;
    this->sr = sampleRate * OVERSAMPLING;
    this->samplesPerBlock = samplesPerBlock;
    
    m_time = 0.0;
    m_deltaTime = 1.0 / (float)sr;
    
    // Sin Table
    for (int sample = 0; sample < sr; ++sample) {
        float value = sin(2.0 * double_Pi  * m_time);
         sinBuffer[sample] = value;
         m_time += m_deltaTime;
    }
    
    // Square Table Generator - add Sin waves up
    int harmonics = 10;
    int freqmul = 1;
    float vol = 1.0f;
    for (int sample = 0; sample < sr; ++sample){
        squareBuffer[sample] = 0;
        if(sample < sr/2){
            squareBuffer[sample] = 0.5;
           }else{
            squareBuffer[sample] = -0.5;
        }
    }
    for(int i=0; i < harmonics;++i){
        for (int sample = 0; sample < sr; ++sample) {
            int pos = checkPos(sample * freqmul);
            squareBuffer[sample] += sinBuffer[pos] * vol / 10.0f;
        }
        freqmul += 2;
        vol *= 0.5;
    }
        
    // Saw Table
    // (2.0 * mPhase / twoPI) - 1.0;
    for (int sample = 0; sample < sr; ++sample) {
        sawBuffer[sample] = 2.0f * sample / sr  - 1.0f;
    }
    
    // Triangle Table
    for (int sample = 0; sample < sr; ++sample) {
        if(sample<sr/4){
            triangleBuffer[sample] = 4.0 * sample/sr;
        }else if(sample< 3 * sr/4){
            triangleBuffer[sample] = 1.0 - 4.0 * (sample-sr / 4) / sr;
        }else{
            triangleBuffer[sample] = -1.0 + 4.0 * (sample - 3 * sr / 4) / sr;
        }
    }

    // White Table
     Random *random = new Random();
    for (int sample = 0; sample < sr; ++sample) {
        whiteBuffer[sample] = random->nextFloat() * 2.0 - 1.0;
    }
    delete random;
}
