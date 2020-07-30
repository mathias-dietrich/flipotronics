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

class Core;

class IComponent  :  public Component{

public:
    
    IComponent(){
        
    }
    
    virtual ~IComponent () {
        
    }
    
    virtual std::map<int, Param> getParams() = 0;
    virtual void setParams( std::map<int, Param> params) = 0;
    
    void init(float sampleRate, int samplesPerBlock){
        this->samplesPerBlock = samplesPerBlock;
        this->sampleRate = sampleRate;
        this->sr = sampleRate * OVERSAMPLING;
        this->blocksPerSecond = sampleRate / samplesPerBlock;
    }

    void setPoti(Node * node, Poti * p, Param param, float val){
        p->setRange(param.minVal,param.maxVal,param.stepVal);
        p->setTitle(node->title);
        // boxes[i].setText(params[pid].name);
        if( param.type == uWaveType){
           p->setTextValueSuffix(" " + getWaveType(E_WaveType(int(val))));
        }else if( param.type == uFilterType){
              p->setTextValueSuffix(" " + getFilterTypeString(MultiModeLadderFilterTypes(int(val))));
        }
        else if( param.type == uPhase){
           p->setTextValueSuffix(" degrees");
        }
        else if( param.type == uTimeMsec){
           p->setTextValueSuffix(" msec");
           p->setSkewFactor(0.5);
        }
        else if( param.type == uDb){
           p->setSkewFactor (6);
        }
        else if( param.type == uTune){
                  p->setTextValueSuffix(" Hz");
        }
        else if( param.type == uHZ){
           p->setSkewFactor (0.3);
           p->setTextValueSuffix(" Hz");
        }
        else if(param.type == uBool){
           bool test = val;
           String text = test ? " on" : " off" ;
           p->setTextValueSuffix(text);
        }
        else if( param.type == uCurve){
           p->setSkewFactor(1);
           p->setTextValueSuffix(" %");
        }
        else if( param.type == uMidiNote){
          p->setTextValueSuffix(" " + midiNote(val));
        }
        else if( param.type == uDevision){
          p->setTextValueSuffix(" " + devision(val));
        }
        else if( param.type == uArpMode){
           p->setSkewFactor(1);
           if(val==0){
                p->setTextValueSuffix(" SEQ");
           }else if (val==1){
                p->setTextValueSuffix(" ARP");
           }else{
               p->setTextValueSuffix(" CHORD");
           }
        }
        else if( param.type == uChordMode){
           switch(((int)val)){
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
        }
        else{
           p->setTextValueSuffix("");
        }
    }

    
    void clearUi(){
        for(auto it = std::begin(children); it != std::end(children); ++it) {
            IComponent *c = *it;
            c->clearUi();
            delete c;
        }
        children.clear();
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
    
    virtual int getParamCount(){
           return 0;
    }
    
    Core * core;
};

#endif /* IComponent_h */
