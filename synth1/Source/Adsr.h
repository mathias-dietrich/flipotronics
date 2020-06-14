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
    float sustainRatio = 0;
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
    
    void release(){
        
        releaseTimeStart = timeLapse;
        state = ADSR_RELEASE;
    }
    
    void tick(){
        
        switch(state){
            case ADSR_DEL:
            {
                if(timeLapse >= delayTimeMsec * samplesPerMillisecond)  {
                    state = ADSR_ATTACK;
                }
                break;
            }
            case ADSR_ATTACK:
            {
               int t = timeLapse / samplesPerMillisecond - delayTimeMsec;
               output = attackCurve.getScaled(t,attackTimeMsec);
               if(t >= attackTimeMsec ){
                   state = ADSR_HOLD;
               }
               break;
            }
                
            case ADSR_HOLD:
            {
              int t = timeLapse / samplesPerMillisecond - delayTimeMsec - attackTimeMsec;
              if(t >= holdTimeMsec ){
                  state = ADSR_DECAY;
              }
              break;
            }
            case ADSR_DECAY:
            {
                int t = timeLapse / samplesPerMillisecond - delayTimeMsec - attackTimeMsec - holdTimeMsec;
                float decayRange = 1.0 - sustainLevel;
                float tableValue = decayCurve.getScaled( t,decayTimeMsec);
                output = (1.0 - tableValue) * decayRange  + sustainLevel;
                if(t >= decayTimeMsec ){
                    state = ADSR_SUSTAIN;
                }
                break;
            }
            case ADSR_SUSTAIN:
            {
                int t = timeLapse / samplesPerMillisecond - delayTimeMsec - attackTimeMsec - holdTimeMsec - decayTimeMsec;
                
                if(sustainRatio > 0){
                    sustainLevel  =  sustainLevel + sustainLevel * (sustainRatio / 100.0f) * 0.01f * (t / 1000.0f);
                }else if(sustainRatio < 0){
                   sustainLevel  =  sustainLevel - sustainLevel * (abs(sustainRatio) / 100.0f) * 0.01f * (t / 1000.0f);
                }
                
                if(sustainLevel >=1){
                    sustainLevel = 1;
                }
                
                if(sustainLevel < 0){
                    sustainLevel = 0;
                }
                output = sustainLevel;
                break;
            }
            case ADSR_RELEASE:
            {
                int t = (timeLapse - releaseTimeStart)/ samplesPerMillisecond;
                float tableValue = releaseCurve.getScaled( t, releaseTimeMsec);
                output = (1.0 - tableValue) * sustainLevel;
                if(output < 0.00001){
                    output = 0;
                    state = ADSR_OFF;
                }
                break;
            }
        }
         ++timeLapse;
    }
    
    void setAttackCurve(int prozent){
        attackCurve.set(prozent);
    }
    
    void setDecayCurve(int prozent){
        decayCurve.set(prozent);
    }
    
    void setSustainCurve(int prozent){
        sustainRatio = prozent;
    }
    
    void setReleaseCurve(int prozent){
        releaseCurve.set(prozent);
    }

    float output;
   
    // Trigger
    int trigger;
    float triggerTreshold;
    
    // times
     int timeLapse = 0;
    int releaseTimeStart = 0;
    int delayTimeMsec;
    int holdTimeMsec;
    int attackTimeMsec;
    int decayTimeMsec;
    int releaseTimeMsec;
    
    float sustainLevel;
    
    // Targets
    float ampTarget;
    float pitchTarget;
    float filterTarget;
    float fxTarget;
    
    //
    int sampleRate;
    int samplesPerBlock;
    int samplesPerMillisecond;
    
    enum AdsrState{ADSR_DEL, ADSR_ATTACK, ADSR_HOLD, ADSR_DECAY, ADSR_SUSTAIN,ADSR_RELEASE, ADSR_OFF, ADSR_DONE};
    AdsrState state = ADSR_OFF;
private:

   
    
};
#endif /* Adsr_h */
