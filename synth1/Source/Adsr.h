//
//  Adsr.h
//  synth1
//
//  Created by Mathias Dietrich on 07.06.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef Adsr_h
#define Adsr_h

#include <JuceHeader.h>
#include "Note.h"

class Adsr {       // The class
    
  public:
    Adsr(){

    }
    
    ~Adsr(){

    }
    
    void init (double sampleRate, int samplesPerBlock){
        this->sampleRate = sampleRate;
        this->samplesPerBlock = samplesPerBlock;
    }
    
    void start(){
        timeLapse = 0;
        state = ADSR_DEL;
        vol = 0;
    }
    
    void tick(){
        switch(state){
            case ADSR_DEL:
                if(delayTimeMsec ==0){
                    state = ADSR_ATTACK;
                    break;
                }
                if(timeLapse >= delayTimeMsec * 0.001f * sampleRate)  {
                    state = ADSR_ATTACK;
                }
                break;
                
            case ADSR_ATTACK:
            {
                if(attackTimeMsec==0){
                    attackTimeMsec = 2;
                }
               int noSamples =  attackTimeMsec * 0.001f * sampleRate  ;
               float add = 1.0f / noSamples;
               vol += add;
               if(vol >= 1.0){
                   vol = 1.0;
                   state = ADSR_DECAY;
               }
                break;
            }
            
            case ADSR_DECAY:
            {
                if(decayTimeMsec==0){
                      decayTimeMsec = 2;
                 }
                int noSamples = decayTimeMsec * 0.001f * sampleRate;
                float sub = 1.0f / noSamples * (1.0 - sustainLevel);
                vol -= sub;
                if(vol <= sustainLevel){
                    vol = sustainLevel;
                    state = ADSR_SUSTAIN;
                }
                break;
            }
            
            case ADSR_SUSTAIN:
            {
                break;
            }
            
            case ADSR_RELEASE:
            {
                if(releaseTimeMsec==0){
                     releaseTimeMsec = 2;
                }
                int noSamples = releaseTimeMsec * 0.001 * sampleRate;
                float sub = sustainLevel / noSamples;
                vol -= sub;
                if(vol <= 0){
                    state = ADSR_DONE;
                }
                break;
            }
            
            case ADSR_DONE:
            {
                // do nothing, Voice will go back into the Pool
                vol = 0;
                break;
             }
                
            case ADSR_OFF:
            {
                vol = 0;
                break;
            }
        }
        ++timeLapse;
    }
    
    int attackTimeMsec;
    int decayTimeMsec;
    int releaseTimeMsec;
    float sustainLevel;
    int delayTimeMsec;
    enum AdsrState{ADSR_DEL, ADSR_ATTACK, ADSR_DECAY, ADSR_SUSTAIN,ADSR_RELEASE, ADSR_OFF, ADSR_DONE};
    float vol;
    AdsrState state = ADSR_OFF;
    int timeLapse = 0;
    
private:
    int sampleRate;
    int samplesPerBlock;
   
    
};
#endif /* Adsr_h */
