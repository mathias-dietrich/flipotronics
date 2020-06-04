//
//  WaveTable.cpp
//  synth1
//
//  Created by Mathias Dietrich on 31.05.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#include "WaveTable.h"
#include "Const.h"

void WaveTable::init (double sampleRate, int samplesPerBlock){
    this->sampleRate = sampleRate;
    this->samplesPerBlock = samplesPerBlock;

     int sr = OVERSAMPLING * sampleRate;
    m_time = 0.0;
    m_deltaTime = 1.0 / (float)sr;
    
   
    
    // Sin Table
    for (int sample = 0; sample < sr; ++sample) {
        float value = sin(2.0 * double_Pi  * m_time);
         sinBuffer[sample] = value;
         m_time += m_deltaTime;
    }
    
    // Square Table
    for (int sample = 0; sample < sr; ++sample) {
        if(sample < sr/2){
            squareBuffer[sample] = 1;
        }else{
            squareBuffer[sample] = -1;
        }
    }
    
    // Saw Table
    for (int sample = 0; sample < sr/2; ++sample) {
        sawBuffer[sample] = 2.0 * sample / sr ;
    }
    for (int sample = sr/2; sample < sr; ++sample) {
        sawBuffer[sample] = 2.0 * sample / sr - 2;
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
    for (int sample = 0; sample < sr; ++sample) {
         Random *random = new Random();
        whiteBuffer[sample] = random->nextFloat() * 2.0 - 1.0;
        //std::cout << whiteBuffer[sample] << std::endl;
        delete random;
    }
}
