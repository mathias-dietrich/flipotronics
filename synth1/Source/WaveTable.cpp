//
//  WaveTable.cpp
//  synth1
//
//  Created by Mathias Dietrich on 31.05.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#include "WaveTable.h"

void WaveTable::init (double sampleRate, int samplesPerBlock){
    this->sampleRate = sampleRate;
    this->samplesPerBlock = samplesPerBlock;

    m_time = 0.0;
    m_deltaTime = 1.0 / sampleRate;
    
    // Sin Table
    for (int sample = 0; sample < sampleRate; ++sample) {
        float value = sin(2.0 * double_Pi  * m_time);
         sinBuffer[sample] = value;
         m_time += m_deltaTime;
    }
    
    // Square Table
    m_time = 0.0;
    for (int sample = 0; sample < sampleRate; ++sample) {
        if(sample < sampleRate/2){
            squareBuffer[sample] = 1;
        }else{
            squareBuffer[sample] = -1;
        }
        m_time += m_deltaTime;
    }
    
    // Saw Table
    m_time = 0.0;
    for (int sample = 0; sample < sampleRate; ++sample) {
        sawBuffer[sample] = 2.0 * sample / sampleRate - 1.0;
        m_time += m_deltaTime;
    }
    
    // Triangle Table
    m_time = 0.0;
    for (int sample = 0; sample < sampleRate; ++sample) {
        if(sample<sampleRate/4){
            triangleBuffer[sample] = 4.0 * sample/sampleRate;
        }else if(sample< 3 * sampleRate/4){
            triangleBuffer[sample] = 1.0 - 4.0 * (sample-sampleRate / 4) / sampleRate;
        }else{
            triangleBuffer[sample] = -1.0 + 4.0 * (sample - 3 * sampleRate / 4) / sampleRate;
        }
        m_time += m_deltaTime;
    }
    
    // White Table
    for (int sample = 0; sample < sampleRate; ++sample) {
        whiteBuffer[sample] = random->nextFloat() * 2.0 - 1.0;
        std::cout << whiteBuffer[sample] << std::endl;
    }
}
