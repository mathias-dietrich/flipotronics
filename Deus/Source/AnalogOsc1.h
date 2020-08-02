//
//  AnlaogOsc1.h
//  Deus
//
//  Created by Mathias Dietrich on 7/30/20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef AnlaogOsc1_h
#define AnlaogOsc1_h

#include "IModule.h"
#include "Model.h"

#include "FilterExtern/Oscillator.h"
#include "FilterExtern/QBLimitedOscillator.h"
#include "FilterExtern/PolyBLEP.h"

class AnalogOsc1 : public IModule{
public:
    
    AnalogOsc1(){
       pulsewidth = 100;
    }

    ~AnalogOsc1(){
       delete polyBLEP;
    }
    
    void init (int sampleRate, int samplesPerBlock) override{
        this->sampleRate = sampleRate;
        this->sr = sampleRate * OVERSAMPLING;
        this->samplesPerBlock = samplesPerBlock;

        // Test
        m_deltaTime = 1.0 / ((double )sampleRate);
        m_phase = 0;
        
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

    void set(int pid, float p) override{
        switch(pid){
            case 0:
                octave = p;
            break;
            case 1:
                semitone = p;
             break;
            case 2:
                finetuning = p;
             break;
            case 3:
                volume = DecibelToLinear(p);
             break;
            case 4:
                wave = (E_WaveType)p;
            break;
            case 5:
                pulsewidth = 100.0f / (p+1);
            break;
        }
    }
    
    int getParamCount() override{
          return 5;
    }
    
    E_Module getType() override{
        return mOSCAnalog1;
    }
    
    void reset(){
        val = 0;
    }
    
    void noteOn(int channel, int note) override{
        this->note = note;
        m_frequency = MidiToFreq(note, 440.0);
        modFreq = 1.0;
        modVol = 1.0;
        
        polyBLEP->setFrequency(m_frequency);
        PolyBLEP::Waveform wf = mapWaveEnum(wave);
        polyBLEP->setWaveform(wf);
        polyBLEP->setPulseWidth(pulsewidth / 100.0f);
    }
    
    void noteOff(int channel, int note)override{
        
    }
    
    float getNextL(float input, bool move) override{
        float val =  getSample(wave);
        
        int midiNoteCalculated = note +  semitone + 12 * octave;
        
        // Freq
        float freq =  MidiToFreq(midiNoteCalculated, tuning);

        // fine Tune
        freq = freq + freq *  finetuning * 0.01f;

        polyBLEP->setFrequency(freq);
        float pulseWidth = pulsewidth / 100.0f;
        polyBLEP->setPulseWidth(pulseWidth);
        polyBLEP->inc();
        
        return val;
    }
    
    float getNextR(float input, bool move) override{
        return 0;
    }
    
    float pitchMod = 1.0f;
    
    float getSample(E_WaveType wt){
        switch(wt){
            case wSin:
                return volume * modVol * polyBLEP->get();
                
            case wSaw:
                return volume * modVol * polyBLEP->get();
                
            case wTriangle:
                return volume * modVol * polyBLEP->get();
                
            case wSquare:
                return volume * modVol * polyBLEP->get();
                
            case wShark:
                 break;
                
            case wWhite:
                return volume * modVol * oscWhite.doOscillate();

            case wPink:
                return volume * modVol * oscPink.doOscillate();;
                
            case wBrown:
                 break;
                
            case wTable:
                 break;
        }
        return 0;
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
    
private:
    
    //Live Params
    atomic<int> octave;
    atomic<int> semitone;
    atomic<float> finetuning;
    atomic<float> volume;
    atomic<E_WaveType> wave;
    atomic<float> pulsewidth;
    atomic<float> modFreq;
    atomic<float> modVol;
    
    int note;
    float val;
    
    float m_phase;
    float m_deltaTime;
    float m_frequency = 440;
    float m_time = 0.0;
    
    int sampleRate;
    int sr;
    int samplesPerBlock;
    
    PolyBLEP * polyBLEP;
    CQBLimitedOscillator oscWhite;
    CQBLimitedOscillator oscPink;
};
#endif /* AnlaogOsc1_h */
