//
//  Voice.hpp
//  TestLib
//
//  Created by Mathias Dietrich on 02.03.21.
//

#ifndef Voice_hpp
#define Voice_hpp

#define SAMPLE_RATE 44100

#include <stdio.h>
#include "Renderer.h"
#include <ostream>
#include  <iostream>
#include <AudioUnit/AudioUnit.h>

# define M_PI           3.14159265358979323846
# define M_PI_2           3.14159265358979323846 * 2.0
class Voice : Renderer{
public:
    int id;
    int channel = 0;
    bool active = false;
    int zone;

    bool isOn;
    float theta;
    float freq;
    float step;
    float delta;
    int midiNote;
    float sine_table[SAMPLE_RATE];
    float tuning = 440.0;
    
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
    
    // 32767.0f
    
    void render(float * l, float * r, int noOfSamples)  {
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
