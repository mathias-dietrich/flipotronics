//
//  WaveTable.hpp
//  synth1
//
//  Created by Mathias Dietrich on 31.05.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef WaveTable_hpp
#define WaveTable_hpp

#include <stdio.h>


#include <JuceHeader.h>
#include "Const.h"


class WaveTable {// The class
  public:             // Access specifier
    WaveTable(){
        
    }
    
    ~WaveTable(){
        
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
    
    int sr;
    void init (double sampleRate, int samplesPerBlock);
    
    float *sinBuffer = new float[SAMPLERATEMAX * OVERSAMPLING];
    float *sawBuffer = new float[SAMPLERATEMAX * OVERSAMPLING];
    float *squareBuffer = new float[SAMPLERATEMAX * OVERSAMPLING];
    float *triangleBuffer = new float[SAMPLERATEMAX * OVERSAMPLING];
    float *whiteBuffer = new float[SAMPLERATEMAX * OVERSAMPLING];
    
private:
    int sampleRate;
    int samplesPerBlock;
    double currentAngle = 0.0, angleDelta = 0.0, level = 0.0, tailOff = 0.0;
    int sampleId = 0;
    float m_amplitude;
    float m_frequency;
    float m_phase;
    float m_time;
    double m_deltaTime;
   
};
#endif /* WaveTable_hpp */
