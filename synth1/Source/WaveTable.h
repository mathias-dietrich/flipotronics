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

#define TABLEMAX 192000
class WaveTable {// The class
  public:             // Access specifier
    WaveTable(){
        
    }
    
    ~WaveTable(){
        
    }
    void init (double sampleRate, int samplesPerBlock);
    
    float *sinBuffer = new float[TABLEMAX];
    float *sawBuffer = new float[TABLEMAX];
    float *squareBuffer = new float[TABLEMAX];
    float *triangleBuffer = new float[TABLEMAX];
    float *whiteBuffer = new float[TABLEMAX];
    
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
    Random *random = new Random();
};
#endif /* WaveTable_hpp */
