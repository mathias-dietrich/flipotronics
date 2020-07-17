//
//  IComponent.h
//  Deus
//
//  Created by Mathias Dietrich on 15.07.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef IComponent_h
#define IComponent_h
#include <JuceHeader.h>

#include "Inc.h"
#include "IWidget.h"
#include "Poti.h"
#include "Model.h"
#include "EventHandler.h"
#include "IFactory.h"

class IComponent  :  public Component{

public:
    
    IComponent(){
        
    }
    
    virtual ~IComponent () {
        
    }
    
    void init(float sampleRate, int samplesPerBlock){
        this->samplesPerBlock = samplesPerBlock;
        this->sampleRate = sampleRate;
        this->sr = sampleRate * OVERSAMPLING;
        this->blocksPerSecond = sampleRate / samplesPerBlock;
    }

    void setPoti(Node * node, Poti * p){
        Model *m = Model::of();
        int pid = node->paramId;
        p->setRange(m->params[pid].minVal,m->params[pid].maxVal,m->params[pid].stepVal);
        p->setTitle(node->title);
        // boxes[i].setText(params[pid].name);
        if( m->params[pid].type == uWaveType){
           p->setTextValueSuffix(" " + getWaveType(E_WaveType(int(m->par[pid]))));
           p->setValue(m->par[pid], dontSendNotification);
        }else if( m->params[pid].type == uFilterType){
              p->setTextValueSuffix(" " + getFilterTypeString(MultiModeLadderFilterTypes(int(m->par[pid]))));
              p->setValue(m->par[pid], dontSendNotification);
        }
        else if( m->params[pid].type == uPhase){
           p->setTextValueSuffix(" degrees");
           p->setValue(m->par[pid], dontSendNotification);
        }
        else if( m->params[pid].type == uTimeMsec){
           p->setTextValueSuffix(" msec");
           p->setSkewFactor(0.5);
           p->setValue(m->par[pid], dontSendNotification);
        }
        else if( m->params[pid].type == uDb){
           p->setSkewFactor (6);
           p->setTextValueSuffix(" dB");
           p->setValue(m->par[pid], dontSendNotification);
        }
        else if( m->params[pid].type == uHZ){
           p->setSkewFactor (0.3);
           p->setTextValueSuffix(" Hz");
           p->setValue(m->par[pid], dontSendNotification);
        }
        else if( m->params[pid].type == uBool){
           bool test = m->par[pid];
           String text = test ? " on" : " off" ;
           p->setTextValueSuffix(text);
        }
        else if( m->params[pid].type == uCurve){
           p->setSkewFactor(1);
           p->setTextValueSuffix(" %");
           p->setValue(m->par[pid], dontSendNotification);
        }
        else if( m->params[pid].type == uMidiNote){
          p->setTextValueSuffix(" " + midiNote(m->par[pid]));
          p->setValue(m->par[pid], dontSendNotification);
        }
        else if( m->params[pid].type == uDevision){
          p->setTextValueSuffix(" " + devision(m->par[pid]));
          p->setValue(m->par[pid], dontSendNotification);
        }
        else if( m->params[pid].type == uArpMode){
           p->setSkewFactor(1);
           if(m->par[pid]==0){
                p->setTextValueSuffix(" SEQ");
           }else if (m->par[pid]==1){
                p->setTextValueSuffix(" ARP");
           }else{
               p->setTextValueSuffix(" CHORD");
           }
           p->setValue(m->par[pid], dontSendNotification);
        }
        else if( m->params[pid].type == uChordMode){
           switch(((int)m->par[pid])){
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
          p->setValue(m->par[pid], dontSendNotification);
        }
        else{
           p->setTextValueSuffix("");
           p->setValue(m->par[pid], dontSendNotification);
        }
    }
    
    int width;
    int height;
    
    Rectangle<int> getRec(){
        Rectangle<int> r = {0,0,width,height};
        return r;
    }
    
    Rectangle<float> getRecf(){
        Rectangle<float> r = {0,0,(float)width,(float)height};
        return r;
    }
    virtual void setDials()=0;
    virtual void build(Node * node)=0;
    
    EventHandler * eventHandler;

    IFactory * factory;
    IComponent *current;
    Node * node;
    float sampleRate;
    int samplesPerBlock;
    float sr;
    int blocksPerSecond;
    std::vector<IComponent *> children;
    std::vector<Widget *> widgets;

};

#endif /* IComponent_h */
