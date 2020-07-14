//
//  AbstractComponent.h
//  synth1
//
//  Created by Mathias Dietrich on 25.06.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef AbstractComponent_h
#define AbstractComponent_h

#include <stdio.h>
#include <JuceHeader.h>
#include "Widget.h"
#include "Poti.h"

class AbstractComponent  :  public Component{

public:
    
    AbstractComponent(){
        
    }
    
    virtual ~AbstractComponent () {
        
    }
    
    void init(float sampleRate, int samplesPerBlock){
        this->samplesPerBlock = samplesPerBlock;
        this->sampleRate = sampleRate;
        this->sr = sampleRate * OVERSAMPLING;
        this->blocksPerSecond = sampleRate / samplesPerBlock;
    }

    virtual void setDials()=0;
    
    virtual void build(Node node)=0;
    
    float sampleRate;
    int samplesPerBlock;
    float sr;
    int blocksPerSecond;
    
    std::vector<AbstractComponent *> children;
    std::vector<Widget *> widgets;
    Node node;
    
    
    void setPoti(int pid, Poti * p){
        p->setRange(Model::of().params[pid].minVal,Model::of().params[pid].maxVal,Model::of().params[pid].stepVal);
        p->setTitle(Model::of().params[pid].name);
        // boxes[i].setText(params[pid].name);
        if( Model::of().params[pid].type == uWaveType){
           p->setTextValueSuffix(" " + getWaveType(E_WaveType(int(Model::of().par[pid]))));
           p->setValue(Model::of().par[pid], dontSendNotification);
        }else if( Model::of().params[pid].type == uFilterType){
              p->setTextValueSuffix(" " + getFilterTypeString(MultiModeLadderFilterTypes(int(Model::of().par[pid]))));
              p->setValue(Model::of().par[pid], dontSendNotification);
        }
        else if( Model::of().params[pid].type == uPhase){
           p->setTextValueSuffix(" degrees");
           p->setValue(Model::of().par[pid], dontSendNotification);
        }
        else if( Model::of().params[pid].type == uTimeMsec){
           p->setTextValueSuffix(" msec");
           p->setSkewFactor(0.5);
           p->setValue(Model::of().par[pid], dontSendNotification);
        }
        else if( Model::of().params[pid].type == uDb){
           p->setSkewFactor (6);
           p->setTextValueSuffix(" dB");
           p->setValue(Model::of().par[pid], dontSendNotification);
        }
        else if( Model::of().params[pid].type == uHZ){
           p->setSkewFactor (0.3);
           p->setTextValueSuffix(" Hz");
           p->setValue(Model::of().par[pid], dontSendNotification);
        }
        else if( Model::of().params[pid].type == uBool){
           bool test = Model::of().par[pid];
           String text = test ? " on" : " off" ;
           p->setTextValueSuffix(text);
        }
        else if( Model::of().params[pid].type == uCurve){
           p->setSkewFactor(1);
           p->setTextValueSuffix(" %");
           p->setValue(Model::of().par[pid], dontSendNotification);
        }
        else if( Model::of().params[pid].type == uMidiNote){
          p->setTextValueSuffix(" " + midiNote(Model::of().par[pid]));
          p->setValue(Model::of().par[pid], dontSendNotification);
        }
        else if( Model::of().params[pid].type == uDevision){
          p->setTextValueSuffix(" " + devision(Model::of().par[pid]));
          p->setValue(Model::of().par[pid], dontSendNotification);
        }
        else if( Model::of().params[pid].type == uArpMode){
           p->setSkewFactor(1);
           if(Model::of().par[pid]==0){
                p->setTextValueSuffix(" SEQ");
           }else if (Model::of().par[pid]==1){
                p->setTextValueSuffix(" ARP");
           }else{
               p->setTextValueSuffix(" CHORD");
           }
           p->setValue(Model::of().par[pid], dontSendNotification);
        }
        else if( Model::of().params[pid].type == uChordMode){
           switch(((int)Model::of().par[pid])){
               case 0:
                p->setTextValueSuffix(" Singe ");
               break;
               
               case 1:
                p->setTextValueSuffix(" Quinte ");
               break;
                   
               case 2:
                p->setTextValueSuffix(" Quarte ");
               break;
               
               case 3:
                p->setTextValueSuffix(" Root ");
               break;
                   
               case 4:
                p->setTextValueSuffix(" Inv 1 ");
               break;
               
               case 5:
                p->setTextValueSuffix(" Inv 2 ");
               break;
           }
          p->setValue(Model::of().par[pid], dontSendNotification);
        }
        else{
           p->setTextValueSuffix("");
           p->setValue(Model::of().par[pid], dontSendNotification);
        }
    }
    
private:

};

#endif /* AbstractComponent_h */
