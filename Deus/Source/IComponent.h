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
#include "WidgetFactory.h"

class Core;

class IComponent :  public Component,  public Slider::Listener{

public:
    
    IComponent(){
        
    }
    
    virtual ~IComponent () {
        
    }
    
    virtual void sliderValueChanged(Slider *  slider) override {
   
    }
    
    void init(float sampleRate, int samplesPerBlock){
        this->samplesPerBlock = samplesPerBlock;
        this->sampleRate = sampleRate;
        this->sr = sampleRate * OVERSAMPLING;
        this->blocksPerSecond = sampleRate / samplesPerBlock;
    }

    virtual void setPoti(Node * node, Poti * p, float val){
        E_UnitType type = node->unitType;
        p->setRange(node->minValue,node->maxValue,node->step);
        p->setTitle(node->title);
        if(type == uWaveType){
           p->setTextValueSuffix(" " + getWaveType(E_WaveType(int(val))));
        }else if(type == uFilterType){
              p->setTextValueSuffix(" " + getFilterTypeString(MultiModeLadderFilterTypes(int(val))));
        }
        else if(type == uPhase){
           p->setTextValueSuffix(" degrees");
        }
        else if(type == uTimeMsec){
           p->setTextValueSuffix(" msec");
           p->setSkewFactor(0.5);
        }
        else if(type == uDb){
           p->setSkewFactor (6);
        }
        else if(type == uTune){
                  p->setTextValueSuffix(" Hz");
        }
        else if(type == uHZ){
           p->setSkewFactor (0.3);
           p->setTextValueSuffix(" Hz");
        }
        else if(type == uBool){
           bool test = val;
           String text = test ? " on" : " off" ;
           p->setTextValueSuffix(text);
        }
        else if(type == uCurve){
           p->setSkewFactor(1);
           p->setTextValueSuffix(" %");
        }
        else if(type == uMidiNote){
          p->setTextValueSuffix(" " + midiNote(val));
        }
        else if(type == uDevision){
          p->setTextValueSuffix(" " + devision(val));
        }
        else if(type == uArpMode){
           p->setSkewFactor(1);
           if(val==0){
                p->setTextValueSuffix(" SEQ");
           }else if (val==1){
                p->setTextValueSuffix(" ARP");
           }else{
               p->setTextValueSuffix(" CHORD");
           }
        }
        else if(type == uChordMode){
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
    
   virtual void build(Node * node) {
        std::cout << node->name << std::endl;
        int pid = 0;
        for(auto it = std::begin(node->children); it != std::end(node->children); ++it){
            Node *n = *it;
                
            Param p;
            p.name = n->title;
            p.minVal = n->minValue;
            p.maxVal = n->maxValue;
            p.stepVal = n->step;
            p.type = n->unitType;
            p.pid = n->paramId;
            p.module = n->module;
            params[pid] = p;
                
            if(n->name.compare("poti")==0){
                Poti *wc = (Poti *) WidgetFactory::of()->get(n->name);
                wc->node = n;
                addAndMakeVisible(wc);
                wc->setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag );
                wc->setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 100, 20);
                wc->setNumDecimalPlacesToDisplay(2);
                wc->setName(toString(pid));
                wc->addListener (this);
                wc->setTitle(n->title);
                setPoti(n, wc, Model::of()->preset.params[n->module][n->paramId].valF);
                widgets.push_back(wc);
            }
            if(n->name.compare("masterpoti")==0){
                MasterPoti *wc = (MasterPoti *) WidgetFactory::of()->get(n->name);
                wc->node = n;
                addAndMakeVisible(wc);
                wc->setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag );
                wc->setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, false, 50, 15);
                wc->setNumDecimalPlacesToDisplay(2);
                wc->setName(toString(pid));
                wc->setTitle(n->title);
                wc->addListener (this);
                wc->setRange(n->minValue, n->maxValue, n->step);
                wc->setValue(Model::of()->preset.params[n->module][n->paramId].valF);
                widgets.push_back(wc);
            }
                
            ++pid;
        }
        setDials();
    }
    
    virtual void setDials()=0;
    
    
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
    std::map<int, Param> params;
};

#endif /* IComponent_h */
