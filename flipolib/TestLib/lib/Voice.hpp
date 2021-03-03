//
//  Voice.hpp
//  TestLib
//
//  Created by Mathias Dietrich on 02.03.21.
//

#ifndef Voice_hpp
#define Voice_hpp

#include <stdio.h>
#include <ostream>
#include <iostream>

#include "Def.h"
#include "Renderer.h"

class Voice : Renderer{
public:
    bool active = false;
    bool isOn;
    
    int id;
    int channel = 0;
    int zone;
    int midiNote;
    
    float freq;
    float step;
    float delta;
    float sine_table[SAMPLE_RATE];
    float tuning = 440.0;
    
    void pitchBend(int val){
        // TODO
    }
    
    void modWheel(int val){
        // TODO
    }
    
    void controller(int cc, int val){
        // TODO
    }
    
    void init(){
        float m_deltaTime = 1.0 / (float)SAMPLE_RATE;
        float m_time = 0.0;
        for (int i = 0; i < SAMPLE_RATE; i++){
            float value = sin(2.0 * M_PI_2  * m_time);
            sine_table[i] = value;
            m_time += m_deltaTime;
        }
    }
    
    void setNote(int midiNote){
        this->midiNote = midiNote;
        freq = tuning * pow(2.0, (midiNote - 69)/12.0);
        std::cout << " freq " << freq << std::endl;
        step = freq;
        delta = 0;
    }
    
    void render(SAMPLE * l, SAMPLE * r, int noOfSamples)  {
        if(active){
            for (int i = 0; i < noOfSamples; ++i) {
                float v = sine_table[(int)delta];
                l[i] += v;
                r[i] += v;
                delta += step;
                if (delta >= SAMPLE_RATE) {
                    delta -= SAMPLE_RATE;
                }
            }
        }
    }
    
private:
   
};

#endif /* Voice_hpp */
