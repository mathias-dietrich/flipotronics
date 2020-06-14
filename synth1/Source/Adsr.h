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
#include "Curve.h"

class Adsr {       // The class
    
  public:
    Adsr(){

    }
    
    ~Adsr(){

    }
    
    Curve attackCurve;
    Curve decayCurve;
    Curve sustainCurve;
    Curve releaseCurve;
    
    void init (double sampleRate, int samplesPerBlock){
        this->sampleRate = sampleRate;
        this->samplesPerBlock = samplesPerBlock;
        this->samplesPerMillisecond = 0.001 * sampleRate;
    }
    
    void start(){
        timeLapse = 0;
        state = ADSR_DEL;
        output = 0.0f;
    }
    
    void tick(){
        switch(state){
            case ADSR_DEL:
                if(timeLapse >= delayTimeMsec * samplesPerMillisecond)  {
                    state = ADSR_ATTACK;
                    output = 0.5f;
                }
                break;
        }
         ++timeLapse;
    }
                /*
            case ADSR_ATTACK:
            {
                if(attackTimeMsec==0){
                    attackTimeMsec = 2;
                }
               int noSamples =  attackTimeMsec * 0.001f * sampleRate  ;
               float add = 1.0f / noSamples;
               output += add;
               if(output >= 1.0){
                   output = 1.0;
                   state = ADSR_DECAY;
               }
                break;
            }
                
            case ADSR_HOLD:

             break;
            
            case ADSR_DECAY:
            {
                if(decayTimeMsec==0){
                      decayTimeMsec = 2;
                 }
                int noSamples = decayTimeMsec * 0.001f * sampleRate;
                float sub = (1.0 - sustainLevel) / noSamples;
                output -= sub;
                if(output <= sustainLevel){
                    output = sustainLevel;
                    state = ADSR_SUSTAIN;
                }
                break;
            }
            
            case ADSR_SUSTAIN:
            {
                break; // wait for key releae
            }
            
            case ADSR_RELEASE:
            {
                if(releaseTimeMsec==0){
                    output = 0;
                    state = ADSR_DONE;
                    return;
                }
                float noSamples = releaseTimeMsec * 0.001f * sampleRate;
                float sub = sustainLevel / noSamples;
                output -= sub;
                if(output <= 0){
                    state = ADSR_DONE;
                }
                break;
            }
            
            case ADSR_DONE:
            {
                // do nothing, Voice will go back into the Pool
                output = 0;
                break;
             }
                
            case ADSR_OFF:
            {
                output = 0;
                break;
            }
        }
       
    }
                 */
    
    int attackTimeMsec;
    int decayTimeMsec;
    int releaseTimeMsec;
    float sustainLevel;
    
    void setAttackCurve(int prozent){
        attackCurve.set(prozent);
    }
    
    void setDecayCurve(int prozent){
        decayCurve.set(prozent);
    }
    
    void setSustainCurve(int prozent){
        sustainCurve.set(prozent);
    }
    
    void setReleaseCurve(int prozent){
        releaseCurve.set(prozent);
    }

    float ampTarget;
    float pitchTarget;
    float filterTarget;
    float fxTarget;
    
    int trigger;
    float triggerTreshold;
    int delayTimeMsec;
    int holdTimeMsec;
    
    
    enum AdsrState{ADSR_DEL, ADSR_ATTACK, ADSR_HOLD, ADSR_DECAY, ADSR_SUSTAIN,ADSR_RELEASE, ADSR_OFF, ADSR_DONE};
    float output;
    AdsrState state = ADSR_OFF;
    int timeLapse = 0;
    
    int sampleRate;
    int samplesPerBlock;
    int samplesPerMillisecond;
private:

   
    
};
#endif /* Adsr_h */
