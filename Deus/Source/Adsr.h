//
//  Adsr.h
//  Deus
//
//  Created by Mathias Dietrich on 8/2/20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef Adsr_h
#define Adsr_h

#include <JuceHeader.h>
#include "Curve.h"

class Adsr : public IModule {
    
  public:
    
    Adsr(){

    }
    
    ~Adsr(){

    }
    
    int getParamCount() override {
        return 8;
    }
   
    E_Module getType() override {
       return mAdsr0;
    }
    
    int uid;
    Curve attackCurve;
    Curve decayCurve;
    float sustainRatio = 0;
    Curve releaseCurve;
    
    float susustainLevelInternal;
    
    void init (int sampleRate, int samplesPerBlock) override{
        this->sampleRate = sampleRate;
        this->samplesPerBlock = samplesPerBlock;
        this->samplesPerMillisecond = 0.001 * sampleRate;
    }
    
    void start(){
        timeLapse = 0;
        state = ADSR_DEL;
        output = 0.0f;
        susustainLevelInternal = sustainLevel;
    }
    
    void release(){
        releaseTimeStart = timeLapse;
        state = ADSR_RELEASE;
    }
    
    void tick(int tickSamples){
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
                if(attackTimeMsec<=1){
                    attackTimeMsec = 1.0;
                }
               output = attackCurve.getScaled(t,attackTimeMsec);
               if(t >= attackTimeMsec ){
                   state = ADSR_HOLD;
                  // if(uid>0)std::cout << "ADSR_HOLD" << uid <<std::endl;
               }
               break;
            }
                
            case ADSR_HOLD:
            {
              int t = timeLapse / samplesPerMillisecond - delayTimeMsec - attackTimeMsec;
              if(t >= holdTimeMsec ){
                  state = ADSR_DECAY;
                  // if(uid>0)std::cout << "ADSR_DECAY" << uid <<std::endl;
              }
              break;
            }
            case ADSR_DECAY:
            {
                int t = timeLapse / samplesPerMillisecond - delayTimeMsec - attackTimeMsec - holdTimeMsec;
                float decayRange = 1.0 - sustainLevel;
                if(decayTimeMsec<1){
                    decayTimeMsec = 1;
                }
                float tableValue = decayCurve.getScaled( t,decayTimeMsec);
                output = (1.0 - tableValue) * decayRange  + sustainLevel;
                if(t >= decayTimeMsec ){
                    state = ADSR_SUSTAIN;
                    // if(uid>0)std::cout << "ADSR_SUSTAIN" << uid <<std::endl;
                }
                break;
            }
            case ADSR_SUSTAIN:
            {
                int t = timeLapse / samplesPerMillisecond - delayTimeMsec - attackTimeMsec - holdTimeMsec - decayTimeMsec;
                
                if(sustainRatio > 0){
                    susustainLevelInternal  =  susustainLevelInternal + susustainLevelInternal * (sustainRatio / 100.0f) * 0.01f * (t / 1000.0f);
                }else if(sustainRatio < 0){
                   susustainLevelInternal  =  susustainLevelInternal - susustainLevelInternal * (abs(sustainRatio) / 100.0f) * 0.01f * (t / 1000.0f);
                }
                
                if(susustainLevelInternal >=1){
                    susustainLevelInternal = 1;
                }
                
                if(susustainLevelInternal < 0){
                    susustainLevelInternal = 0;
                }
                output = susustainLevelInternal;
                break;
            }
            case ADSR_RELEASE:
            {
                int t = (timeLapse - releaseTimeStart) / samplesPerMillisecond;
                if(releaseTimeMsec <= 1.0f){
                    releaseTimeMsec = 1.0f;
                }
                float tableValue = releaseCurve.getScaled( t, releaseTimeMsec);
                output = (1.0f - tableValue) * susustainLevelInternal;
                if(output == 0){
                    state = ADSR_DONE;
                    //if(uid>0)std::cout << "ADSR_DONE" << uid << std::endl;
                }
                break;
            }
                
            case ADSR_OFF:
                break;
                
            case ADSR_DONE:
                break;
        }
        timeLapse += tickSamples;
       // if(uid > 0)std::cout << output << std::endl;
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
    
    void noteOn(int channel, int note) override{
        start();
    }
       
    void noteOff(int channel, int note)override{
        release();
   }
    
    void set(int pid, float p) override{
        switch(pid){
            case 0:
                delayTimeMsec = p;
            break;
                
            case 1:
                attackTimeMsec = p;
            break;
              
            case 2:
                holdTimeMsec = p;
            break;
                
            case 3:
               decayTimeMsec = p;
            break;
                
            case 4:
               sustainLevel = p;
            break;
                
            case 5:
                releaseTimeMsec = p;
            break;
                
            case 6:
                 setAttackCurve(p);
            break;
                
            case 7:
                 setDecayCurve(p);
            break;
                
            case 8:
                 setSustainCurve(p);
            break;
                
            case 9:
                 setReleaseCurve(p);
            break;
        }
    }
   
   float getNextL(float input, bool move)override{
       if(move) tick(1);
       return output;
   }
   
   float getNextR(float input, bool move)override{
      if(move) tick(1);
      return output;
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
