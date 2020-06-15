//
//  Lowpass1.h
//  synth1
//
//  Created by Mathias Dietrich on 15.06.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef Lowpass1_h
#define Lowpass1_h

class Lowpass1{
public:
    Lowpass1(){
        m_cutoff = 10.0;
        m_sampleRate = 44100.0;
        m_z1_state = 0.0;
    }
    inline float process(float x){
        const float v = (x - m_z1_state)*m_G;
        const float y = v + m_z1_state;
        m_z1_state = y + v;
        return y;
    }
    inline void setCutoff(const float cutoff){
        m_cutoff = cutoff;
        setInstantaneousResponseGain();
    }
    inline void setSampleRate(const float sampleRate){
        m_sampleRate = sampleRate;
        setInstantaneousResponseGain();
    }
    inline void reset(){
        m_z1_state = 0.0;
    }
    inline float getFilterState(){
        return m_z1_state;
    }
    inline float getInstantaneousResponseGain(){
        return m_g;
    }
private:
    inline void setInstantaneousResponseGain(){
        m_g = tan(M_PI*m_cutoff/m_sampleRate);
        m_G = m_g/(1.0+m_g);
    }
    float m_cutoff;
    float m_sampleRate;
    float m_z1_state;
    float m_g;
    float m_G;
};

#endif /* Lowpass1_h */
