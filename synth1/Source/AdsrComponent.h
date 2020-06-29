//
//  AdsrComponent.h
//  synth1
//
//  Created by Mathias Dietrich on 21.06.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef AdsrComponent_h
#define AdsrComponent_h

#include "AbstractComponent.h"

class AdsrComponent : public AbstractComponent{
    public:
    
     AdsrComponent () {
         adsr1.uid = -1;
         adsr2.uid = -1;
         adsr3.uid = -1;
         adsr4.uid = -1;
     }
    
     ~AdsrComponent () {
         
     }
    
     void paint (Graphics& g) override{
         Rectangle<int> r = getLocalBounds();
         auto width  = getLocalBounds().getWidth();
         auto height  = getLocalBounds().getHeight();
         int half = height / 2;
         
          float par[MAXPARAM];
               for(int i =0; i < MAXPARAM;++i){
                   par[i] = Model::of().par[i] ;
          }
         
         switch(Model::of().viewModeSetting){
        
             case vADSR1: //ADSR 1
             {
                 adsr1.init(sampleRate,  samplesPerBlock);
                 adsr1.delayTimeMsec = par[P_ADSR1_DELAY];
                 adsr1.attackTimeMsec = par[P_ADSR1_ATTACK];
                 adsr1.holdTimeMsec = par[P_ADSR1_HOLD];
                 adsr1.decayTimeMsec = par[P_ADSR1_DECAY];
                 adsr1.sustainLevel = par[P_ADSR1_SUSTAIN];
                 adsr1.releaseTimeMsec = par[P_ADSR1_RELEASE];
                 
                 // Curves
                 adsr1.setAttackCurve( par[P_ADSR1_ATTACK_CURVE]);
                 adsr1.setDecayCurve( par[P_ADSR1_DECAY_CURVE]);
                 adsr1.setSustainCurve( par[P_ADSR1_SUSTAIN_CURVE]);
                 adsr1.setReleaseCurve( par[P_ADSR1_RELEASE_CURVE]);
                 drawAdsr(&adsr1, g,  width,  half);
                 break;
             }

             case vADSR2: //ADSR 2
             {
                 adsr2.init(sampleRate,  samplesPerBlock);
                 adsr2.delayTimeMsec = par[P_ADSR2_DELAY];
                 adsr2.attackTimeMsec = par[P_ADSR2_ATTACK];
                 adsr2.holdTimeMsec = par[P_ADSR2_HOLD];
                 adsr2.decayTimeMsec = par[P_ADSR2_DECAY];
                 adsr2.sustainLevel = par[P_ADSR2_SUSTAIN];
                 adsr2.releaseTimeMsec = par[P_ADSR2_RELEASE];
                 
                 // Curves
                 adsr2.setAttackCurve( par[P_ADSR2_ATTACK_CURVE]);
                 adsr2.setDecayCurve( par[P_ADSR2_DECAY_CURVE]);
                 adsr2.setSustainCurve( par[P_ADSR2_SUSTAIN_CURVE]);
                 adsr2.setReleaseCurve( par[P_ADSR2_RELEASE_CURVE]);
                 drawAdsr(&adsr2, g,  width,  half);
                 break;
             }
             
             case vADSR3: //ADSR 3
             {
                 adsr3.init(sampleRate,  samplesPerBlock);
                 adsr3.delayTimeMsec = par[P_ADSR3_DELAY];
                 adsr3.attackTimeMsec = par[P_ADSR3_ATTACK];
                 adsr3.holdTimeMsec = par[P_ADSR3_HOLD];
                 adsr3.decayTimeMsec = par[P_ADSR3_DECAY];
                 adsr3.sustainLevel = par[P_ADSR3_SUSTAIN];
                 adsr3.releaseTimeMsec = par[P_ADSR3_RELEASE];
                 
                 // Curves
                 adsr3.setAttackCurve( par[P_ADSR3_ATTACK_CURVE]);
                 adsr3.setDecayCurve( par[P_ADSR3_DECAY_CURVE]);
                 adsr3.setSustainCurve( par[P_ADSR3_SUSTAIN_CURVE]);
                 adsr3.setReleaseCurve( par[P_ADSR3_RELEASE_CURVE]);
                 drawAdsr(&adsr3, g,  width,  half);
                 break;
             }
             
             case vADSR4: //ADSR 4
             {
                 adsr4.init(sampleRate,  samplesPerBlock);
                 adsr4.delayTimeMsec = par[P_ADSR4_DELAY];
                 adsr4.attackTimeMsec = par[P_ADSR4_ATTACK];
                 adsr4.holdTimeMsec = par[P_ADSR4_HOLD];
                 adsr4.decayTimeMsec = par[P_ADSR4_DECAY];
                 adsr4.sustainLevel = par[P_ADSR4_SUSTAIN];
                 adsr4.releaseTimeMsec = par[P_ADSR4_RELEASE];
                 
                 // Curves
                 adsr4.setAttackCurve( par[P_ADSR4_ATTACK_CURVE]);
                 adsr4.setDecayCurve( par[P_ADSR4_DECAY_CURVE]);
                 adsr4.setSustainCurve( par[P_ADSR4_SUSTAIN_CURVE]);
                 adsr4.setReleaseCurve( par[P_ADSR4_RELEASE_CURVE]);
                 drawAdsr(&adsr4, g,  width,  half);
                 break;
             }
         }
     }
    
    void resized() override{
        
    }
    
    void setDials(){
        
    }
    
     void drawAdsr(Adsr * adsr, Graphics& g, int width, int half){
    
           adsr->start();
           
           float length = adsr->delayTimeMsec + adsr->attackTimeMsec + adsr->holdTimeMsec + adsr->decayTimeMsec + adsr->releaseTimeMsec;
          
           int SustainTime = length * 5 / 24;
           int releaseSample =  adsr->samplesPerMillisecond * (adsr->delayTimeMsec + adsr->attackTimeMsec + adsr->holdTimeMsec + adsr->decayTimeMsec + SustainTime);
           adsr->releaseTimeStart = releaseSample;
           
           length += SustainTime;
           float ticks = length / width * adsr->samplesPerMillisecond;
           
           int bottom = half + 150;
           int ylast = bottom;
           g.setColour (Colours::red);
           g.drawLine (0, half,width, half, 2.0f);
           
           for(int i=0;i<width;++i){
               int y = 150 + half - 300.0f * adsr->output;
               g.setColour (Colours::yellow);
               g.drawLine (i, ylast, i+1, y, 2.0f);
               if(adsr->state == Adsr::ADSR_RELEASE){
                    g.setColour (Colours::blue);
               }else if(adsr->state == Adsr::ADSR_HOLD){
                   g.setColour (Colours::yellow);
               }else if(adsr->state == Adsr::ADSR_ATTACK){
                   g.setColour (Colours::red);
               }
               else if(adsr->state == Adsr::ADSR_SUSTAIN){
                   g.setColour (Colours::grey);
               }
               else{
                   g.setColour (Colours::green);
               }
                   
               g.drawLine (i, y, i, bottom   , 0.4f);
    
               adsr->tick(ticks);
               if(adsr->timeLapse >= releaseSample && adsr->state == Adsr::ADSR_SUSTAIN){
                   adsr->release();
               }
               ylast = y;
           }
        }
    
private:

    Adsr adsr1;
    Adsr adsr2;
    Adsr adsr3;
    Adsr adsr4;
};
#endif /* AdsrComponent_h */
