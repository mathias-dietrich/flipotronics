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

    PolyBLEP::Waveform mapWaveEnum(E_WaveType type){
        switch(type){
            case wSin:
                return PolyBLEP::COSINE;
                
            case wSaw:
                return PolyBLEP::SAWTOOTH;
                
            case wTriangle:
                return PolyBLEP::MODIFIED_TRIANGLE;
                
            case wSquare:
                return PolyBLEP::MODIFIED_SQUARE;
                
            case wShark:
                return PolyBLEP::MODIFIED_SQUARE;
                
            case wWhite:
                return PolyBLEP::SAWTOOTH;
                
            case wPink:
                return PolyBLEP::SAWTOOTH;
                
            case wBrown:
                return PolyBLEP::SAWTOOTH;
                
            case wTable:
                return PolyBLEP::SAWTOOTH;
        }
        return PolyBLEP::COSINE;
    }
    
    float getSample(E_WaveType wt){
        switch(wt){
            case wSin:
                return modVol * polyBLEP->get();
                
            case wSaw:
                return modVol * polyBLEP->get();
                
            case wTriangle:
                return modVol * polyBLEP->get();
                
            case wSquare:
                return modVol * polyBLEP->get();
                
            case wShark:
                 break;
                
            case wWhite:
                return modVol * oscWhite.doOscillate();

            case wPink:
                return modVol * oscPink.doOscillate();;
                
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
        
        if(oscId == 3){
            freq = freq / 2.0f;
        }
        polyBLEP->setFrequency(freq);
        PolyBLEP::Waveform wf = mapWaveEnum(((E_WaveType)par[P_OSC1_WAV + paramOffset]));
        polyBLEP->setWaveform(wf);
        polyBLEP->setPulseWidth(par[P_OSC1_PULSE + paramOffset] / 100.0f);
        modFreq = 1;
        modVol = 1;
    }
    
    void move(){
        
        // Noge
        midiNoteCalculated = midiNote + par[P_OSC1_SEMI + paramOffset] + 12 * par[P_OSC1_OCT + paramOffset];
        
        // Freq
        freq = Model::of().tuneTable[midiNoteCalculated] * Model::of().tuneMulti[midiNoteCalculated % 12];

        // fine Tune
        freq = freq + freq *  par[P_OSC1_FINE + paramOffset] * 0.01f;
        
        // overall tune
        float t = par[0] / 440.0f;
        freq *= t * modFreq;
        
        if(oscId < 3){
            PolyBLEP::Waveform wf = mapWaveEnum(((E_WaveType)par[P_OSC1_WAV + paramOffset]));
            polyBLEP->setWaveform(wf);
        }
        
        if(oscId == 3){
            freq = freq / 2.0f;
        }
        polyBLEP->setFrequency(freq);
        float pulseWidth = par[P_OSC1_PULSE + paramOffset] / 100.0f;
        polyBLEP->setPulseWidth(pulseWidth);
        polyBLEP->inc();
        
        // bounds check
        //phase++;
        //phase = checkPos(phase);
       
    }
    
    void retriggerNote(){

    }
    
    void init (int oscId, double sampleRate, int samplesPerBlock){
        this->oscId = oscId;
        this-> paramOffset = 0;
        if(oscId==2){
            this-> paramOffset = 8;
        }
        
        this->sampleRate = sampleRate;
        this->sr = sampleRate  * OVERSAMPLING;
        this->samplesPerBlock = samplesPerBlock;
        
        oscWhite.setSampleRate(sampleRate);
        oscWhite.m_uWaveform = COscillator::NOISE;
        oscWhite.reset();
        oscWhite.startOscillator();
        
        oscPink.setSampleRate(sampleRate);
        oscPink.reset();
        oscPink.m_uWaveform = COscillator::PNOISE;
        oscPink.startOscillator();
        
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
    
   
    
     float * par;
     int oscId;
    float modFreq = 1;
    float modVol = 1;
    
    private:
    //WaveTable * waveTable;
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
    
     CQBLimitedOscillator oscWhite;
     CQBLimitedOscillator oscPink;
    
        
};
#endif /* Osc_h */
