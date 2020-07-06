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

#include "FilterExtern/Oscillator.h"
#include "FilterExtern/QBLimitedOscillator.h"
#include "FilterExtern/PolyBLEP.h"

class Osc{
    public:

    Osc(){

    }
    
    ~Osc(){
        delete polyBLEP;
    }
    
    forcedinline float interpolate(int currentIndex, float * table ) noexcept{
        auto index0 = (unsigned int) currentIndex;
        auto index1 = index0 == (2048 - 1) ? (unsigned int) 0 : index0 + 1;
        auto frac = currentIndex - (float) index0;
        auto value0 = table[index0];
        auto value1 = table[index1];
        return value0 + frac * (value1 - value0);
    }
    
    float getSample(E_WaveType wt){
        switch(wt){
            case wSin:
            {
                //auto table = waveTable->sinBuffer[midiNoteCalculated];
                return polyBLEP->get();
                //return table[(int)phase];
                 //return interpolate(checkPosSin(phase), table);
                //return interpolate(checkPosSin(phase + par[P_OSC1_PHASE + paramOffset] / 360.0f * 2048), table);
            }
                
            case wSaw:
                 break;
                
            case wTriangle:
                 break;
                
            case wSquare:
                 break;
                
            case wShark:
                 break;
                
            case wWhite:
                 break;
                
            case wPink:
                 break;
                
            case wBrown:
                 break;
                
            case wTable:
                 break;
        }
        return 0;
    }
    
    void startNote(int midiNote){
        phase = 0;
        this->midiNote = midiNote;
        midiNoteCalculated = midiNote + par[P_OSC1_SEMI + paramOffset] + 12 * par[P_OSC1_OCT + paramOffset];
        freq = Model::of().tuneTable[midiNoteCalculated] * Model::of().tuneMulti[midiNoteCalculated % 12];
        polyBLEP->setFrequency(freq);
       
    }
    
    void move(){
        
        // Noge
        midiNoteCalculated = midiNote + par[P_OSC1_SEMI + paramOffset] + 12 * par[P_OSC1_OCT + paramOffset];
        
        // Freq
        freq = Model::of().tuneTable[midiNoteCalculated] * Model::of().tuneMulti[midiNoteCalculated % 12];
        int tablFreq = freq;
        
       // freq = 1;
        
        // fine Tune
        freq = freq + freq *  par[P_OSC1_FINE + paramOffset] * 0.01f;
        
        // overall tune
        float t = par[0] / 440.0f;
        
        freq *= t;
        
        polyBLEP->setFrequency(freq);
        polyBLEP->inc();
        
        
        // bounds check
        phase = checkPhaseSin(phase);
    }
    
    void retriggerNote(){

    }
    
    void init (int oscId, double sampleRate, int samplesPerBlock){
        this->oscId = oscId;
        this-> paramOffset = 8 * (oscId-1);
        this->sampleRate = sampleRate;
        this->sr = sampleRate /  2048.0f;
        this->samplesPerBlock = samplesPerBlock;
        
        waveTable = WaveTable::of();
        oscillator.setSampleRate(sampleRate);
        oscillator.reset();
        
        polyBLEP = new PolyBLEP(sampleRate, PolyBLEP::SINE,  440.0);
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
    
    inline float checkPhaseSin(float phase){
        if(phase < 0){
            while(phase < 0.0f){
                phase += 2048.0f;
           }
            return phase;
        }
        
        if( phase >= 2048.0f){
            while(phase >= 2048.0f){
                phase -= 2048.0f;
            }
        }
        return phase;
    }
    
    CQBLimitedOscillator oscillator;
    
     float * par;
     int oscId;
    
    private:
    WaveTable * waveTable;
    float sampleRate;
    float samplesPerBlock;
    float sr;
    int midiNote;
    int midiNoteCalculated;
    float phase;
    bool sync;
   
    float freq;
    int paramOffset;
    
    PolyBLEP * polyBLEP;
        
};
#endif /* Osc_h */
