//
//  PotsComponent.h
//  synth1
//
//  Created by Mathias Dietrich on 27.06.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef PotsComponent_h
#define PotsComponent_h
#include <stdio.h>
#include <JuceHeader.h>
#include "CircularBuffer.h"
#include "Func.h"
#include "Color.h"
#include "Poti.h"
#include "AbstractComponent.h"

class PotsComponent : public AbstractComponent, public Slider::Listener {
    
 public:
    PotsComponent(){
      for(int i=0; i < 16; ++i){
             dials[i].setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag );
             dials[i].setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 100, 20);
             dials[i].setNumDecimalPlacesToDisplay(2);
             dials[i].setName(toString(i));
             dials[i].addListener (this);
             addAndMakeVisible (dials[i]);
    }
    }
    
    ~PotsComponent () {
           
    }
       
    void paint (Graphics& g) override {
        
    }
    
    void resized() override{
        int dialY = 0;///60;
         for(int i=0; i < 8; ++i){
             dials[i].setBounds (10  + i * 100,  dialY, 100,  120);
         }
        
        dialY = 130;
        for(int i=0; i < 8; ++i){
            dials[i+8].setBounds (10  + i * 100,  dialY, 100,  120);
        }
    }
    
     void sliderValueChanged(Slider *  slider) override {
            int sid = slider->getName().getIntValue();
            startEdit();
            int pid = paramRoot * 256 + paramRange * 16 + sid + Model::of().editGroup * MAXPARAM;

            if(Model::of().params[sid].smoothTime > 0){
                Model::of().parTargetDelta[pid] = Model::of().par[pid] - slider->getValue();
            }else{
                Model::of().par[pid] = slider->getValue();
            }
            setDials();
        }
    
    void startEdit(){
           Model::of().compareMode = true;
    }
    
    void setDials() override{
        float par[MAXPARAM];
        
        for(int i =0; i < MAXPARAM;++i){
            par[i] = Model::of().par[i + Model::of().editGroup * MAXPARAM] ;
        }
        for(int i=0; i < 16; ++i){
            int pid = paramRoot * 256 + paramRange * 16 + i;
            dials[i].setRange(Model::of().params[pid].minVal,Model::of().params[pid].maxVal,Model::of().params[pid].stepVal);
            dials[i].setTitle(Model::of().params[pid].name);
           // boxes[i].setText(params[pid].name);
            if( Model::of().params[pid].type == uWaveType){
                dials[i].setTextValueSuffix(" " + getWaveType(E_WaveType(int(par[pid]))));
                dials[i].setValue(par[pid], dontSendNotification);
            }else if( Model::of().params[pid].type == uFilterType){
                   dials[i].setTextValueSuffix(" " + getFilterTypeString(MultiModeLadderFilterTypes(int(par[pid]))));
                   dials[i].setValue(par[pid], dontSendNotification);
            }
            else if( Model::of().params[pid].type == uPhase){
                dials[i].setTextValueSuffix(" degrees");
                dials[i].setValue(par[pid], dontSendNotification);
            }
            else if( Model::of().params[pid].type == uTimeMsec){
                dials[i].setTextValueSuffix(" msec");
                dials[i].setSkewFactor(0.5);
                dials[i].setValue(par[pid], dontSendNotification);
            }
            else if( Model::of().params[pid].type == uDb){
                dials[i].setSkewFactor (6);
                dials[i].setTextValueSuffix(" dB");
                dials[i].setValue(par[pid], dontSendNotification);
            }
            else if( Model::of().params[pid].type == uHZ){
                dials[i].setSkewFactor (0.3);
                dials[i].setTextValueSuffix(" Hz");
                dials[i].setValue(par[pid], dontSendNotification);
            }
            else if( Model::of().params[pid].type == uBool){
                bool test = par[pid];
                String text = test ? " on" : " off" ;
                dials[i].setTextValueSuffix(text);
            }
            else if( Model::of().params[pid].type == uCurve){
                dials[i].setSkewFactor(1);
                dials[i].setTextValueSuffix(" %");
                dials[i].setValue(par[pid], dontSendNotification);
            }
            else if( Model::of().params[pid].type == uMidiNote){
               dials[i].setTextValueSuffix(" " + midiNote(par[pid]));
               dials[i].setValue(par[pid], dontSendNotification);
            }
            else if( Model::of().params[pid].type == uDevision){
               dials[i].setTextValueSuffix(" " + devision(par[pid]));
               dials[i].setValue(par[pid], dontSendNotification);
            }
            else if( Model::of().params[pid].type == uArpMode){
                dials[i].setSkewFactor(1);
                if(par[pid]==0){
                     dials[i].setTextValueSuffix(" SEQ");
                }else if (par[pid]==1){
                     dials[i].setTextValueSuffix(" ARP");
                }else{
                    dials[i].setTextValueSuffix(" CHORD");
                }
                dials[i].setValue(par[pid], dontSendNotification);
            }
            else if( Model::of().params[pid].type == uChordMode){
                switch(((int)par[pid])){
                    case 0:
                     dials[i].setTextValueSuffix(" Singe ");
                    break;
                    
                    case 1:
                     dials[i].setTextValueSuffix(" Quinte ");
                    break;
                        
                    case 2:
                     dials[i].setTextValueSuffix(" Quarte ");
                    break;
                    
                    case 3:
                     dials[i].setTextValueSuffix(" Root ");
                    break;
                        
                    case 4:
                     dials[i].setTextValueSuffix(" Inv 1 ");
                    break;
                    
                    case 5:
                     dials[i].setTextValueSuffix(" Inv 2 ");
                    break;
                }
               dials[i].setValue(par[pid], dontSendNotification);
            }
            else{
                dials[i].setTextValueSuffix("");
                dials[i].setValue(par[pid], dontSendNotification);
            }
        }
    }
    
    int paramRoot;
    int paramRange;
    
private:

     Poti dials[16] ;
};

#endif /* PotsComponent_h */
