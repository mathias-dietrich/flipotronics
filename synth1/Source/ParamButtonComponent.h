//
//  ParamButtonComponent.h
//  synth1
//
//  Created by Mathias Dietrich on 27.06.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef ParamButtonComponent_h
#define ParamButtonComponent_h

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "SynthAudioSource.h"
#include "Func.h"
#include "Model.h"
#include "FileManager.h"
#include "BankLoader.h"
#include "img.h"
#include "Color.h"
#include "Curve.h"
#include "PitchWheel.h"
#include "ImageFactory.h"
#include "Poti.h"
#include "PotsComponent.h"
#include "KeysComponent.h"

class ParamButtonComponent : public AbstractComponent,  public Button::Listener{
public:
    
    ParamButtonComponent() {
        int from = 0;
        int to = 15;
        for(int i=0; i < 16; ++i){
           addAndMakeVisible (btnParam[i]);
           btnParam[i].setButtonText (toString(from) + " - " + toString(to));
           btnParam[i].addListener (this);
           btnParam[i].setRadioGroupId(i);
           btnParam[i].setToggleState(false, NotificationType::dontSendNotification);
           from += 16;
           to += 16;
        }
        btnParam[0].setToggleState(true, NotificationType::dontSendNotification);
        
        btnRange0.setButtonText ("Synth");
        btnRange0.addListener (this);
        btnRange0.setRadioGroupId(18);
        btnRange0.setToggleState(true, NotificationType::dontSendNotification);
        addAndMakeVisible (btnRange0);
        
        btnRange1.setButtonText ("Wave");
        btnRange1.addListener (this);
        btnRange1.setRadioGroupId(19);
        addAndMakeVisible (btnRange1);
        
        btnRange2.setButtonText ("FX");
        btnRange2.addListener (this);
        btnRange2.setRadioGroupId(20);
        addAndMakeVisible (btnRange2);
        
        btnRange3.setButtonText ("Control");
        btnRange3.addListener (this);
        btnRange3.setRadioGroupId(21);
        addAndMakeVisible (btnRange3);
        
        btnA.setButtonText ("A <");
        btnA.addListener (this);
        btnA.setRadioGroupId(100);
        addAndMakeVisible (btnA);
        btnA.setToggleState(true, NotificationType::dontSendNotification);
        
        btnB.setButtonText ("B");
        btnB.addListener (this);
        btnB.setRadioGroupId(101);
        addAndMakeVisible (btnB);
        
        btnC.setButtonText ("C");
        btnC.addListener (this);
        btnC.setRadioGroupId(102);
        addAndMakeVisible (btnC);
        
        btnD.setButtonText ("D");
        btnD.addListener (this);
        btnD.setRadioGroupId(103);
        addAndMakeVisible (btnD);
        
        for(int i=0; i < 8; ++i){
           addAndMakeVisible (btnLabel[i]);
           btnLabel[i].setColour (Label::textColourId, Colours::green);
           btnLabel[i].setJustificationType (Justification::centred);
           auto f2 =  btnLabel[i].getFont();
           f2.setSizeAndStyle(15, 0, 0.4, 0.4);
           btnLabel[i].setFont(f2);
        }
        
        for(int i=0; i < 4; ++i){
              addAndMakeVisible (rootLabel[i]);
              rootLabel[i].setColour (Label::textColourId, Colours::green);
              rootLabel[i].setJustificationType (Justification::centred);
              auto f2 =  btnLabel[i].getFont();
              f2.setSizeAndStyle(17, 0, 0.4, 0.4);
              rootLabel[i].setFont(f2);
        }
        rootLabel[0].setText("0 - 255", NotificationType::dontSendNotification);
        rootLabel[1].setText("256 - 511", NotificationType::dontSendNotification);
        rootLabel[2].setText("512 - 767", NotificationType::dontSendNotification);
        rootLabel[3].setText("768 - 1023", NotificationType::dontSendNotification);
        
        setDials();
    }
    
    ~ParamButtonComponent(){
        
    }
    
    void buttonClicked (Button* button)  override {
        
        if(button->getRadioGroupId()==18) {
             paramRoot = 0;
             btnRange0.setToggleState(true, NotificationType::dontSendNotification);
             btnRange1.setToggleState(false, NotificationType::dontSendNotification);
             btnRange2.setToggleState(false, NotificationType::dontSendNotification);
             btnRange3.setToggleState(false, NotificationType::dontSendNotification);
             setButtonRanges();
             return;
        }
        
        if(button->getRadioGroupId()==19) {
            paramRoot = 1;
            btnRange0.setToggleState(false, NotificationType::dontSendNotification);
            btnRange1.setToggleState(true, NotificationType::dontSendNotification);
            btnRange2.setToggleState(false, NotificationType::dontSendNotification);
            btnRange3.setToggleState(false, NotificationType::dontSendNotification);
            setButtonRanges();
            return;
        }
        
        if(button->getRadioGroupId()==20) {
            paramRoot = 2;
            btnRange0.setToggleState(false, NotificationType::dontSendNotification);
            btnRange1.setToggleState(false, NotificationType::dontSendNotification);
            btnRange2.setToggleState(true, NotificationType::dontSendNotification);
            btnRange3.setToggleState(false, NotificationType::dontSendNotification);
            setButtonRanges();
            return;
        }
        
        if(button->getRadioGroupId()==21) {
            paramRoot = 3;
            btnRange0.setToggleState(false, NotificationType::dontSendNotification);
            btnRange1.setToggleState(false, NotificationType::dontSendNotification);
            btnRange2.setToggleState(false, NotificationType::dontSendNotification);
            btnRange3.setToggleState(true, NotificationType::dontSendNotification);
            setButtonRanges();
            return;
        }
        
        // A
        if(button->getRadioGroupId()==100) {
            btnA.setToggleState(true, NotificationType::dontSendNotification);
            btnA.setButtonText("A <");
            btnB.setButtonText("B");
            btnC.setButtonText("C");
            btnD.setButtonText("D");

            btnB.setToggleState(false, NotificationType::dontSendNotification);
            btnC.setToggleState(false, NotificationType::dontSendNotification);
            btnD.setToggleState(false, NotificationType::dontSendNotification);
            Model::of().editGroup = 0;
            return;
        }
        // B
        if(button->getRadioGroupId()==101) {
            btnA.setButtonText("A");
            btnB.setButtonText("B <");
            btnC.setButtonText("C");
            btnD.setButtonText("D");
            
            btnA.setToggleState(false, NotificationType::dontSendNotification);
            btnB.setToggleState(true, NotificationType::dontSendNotification);
            btnC.setToggleState(false, NotificationType::dontSendNotification);
            btnD.setToggleState(false, NotificationType::dontSendNotification);
            Model::of().editGroup = 1;
            return;
        }
        // C
        if(button->getRadioGroupId()==102) {
            btnA.setButtonText("A");
            btnB.setButtonText("B");
            btnC.setButtonText("C <");
            btnD.setButtonText("D");
            
            btnA.setToggleState(false, NotificationType::dontSendNotification);
            btnB.setToggleState(false, NotificationType::dontSendNotification);
            btnC.setToggleState(true, NotificationType::dontSendNotification);
            btnD.setToggleState(false, NotificationType::dontSendNotification);
            Model::of().editGroup = 2;
            return;
        }
        // D
        if(button->getRadioGroupId()==103) {
            btnA.setButtonText("A");
            btnB.setButtonText("B");
            btnC.setButtonText("C");
            btnD.setButtonText("D <");
            
            btnA.setToggleState(false, NotificationType::dontSendNotification);
            btnB.setToggleState(false, NotificationType::dontSendNotification);
            btnC.setToggleState(false, NotificationType::dontSendNotification);
            btnD.setToggleState(true, NotificationType::dontSendNotification);
            Model::of().editGroup = 3;
            return;
        }
        
        paramRange = button->getRadioGroupId();
        setDials();
    }
    
    void setDials() override{
        float par[MAXPARAM];
        for(int i =0; i < MAXPARAM;++i){
            par[i] = Model::of().par[i] ;
        }
        
        if(potsComponent != nullptr){
            potsComponent->paramRoot = paramRoot;
            potsComponent->paramRange = paramRange;
            potsComponent->setDials();
        }
        
        // Param Select
        for(int i=0; i < 16; ++i){
            btnParam[i].setToggleState(false, NotificationType::dontSendNotification);
        }
        if(paramRange<16){
            btnParam[paramRange].setToggleState(true, NotificationType::dontSendNotification);
        }
        
        switch(paramRoot){
           case 0:
               btnLabel[0].setText("Master", NotificationType::dontSendNotification);
               btnLabel[1].setText("Osci", NotificationType::dontSendNotification);
               btnLabel[2].setText("Filter", NotificationType::dontSendNotification);
               btnLabel[3].setText("Adsr 1", NotificationType::dontSendNotification);
               btnLabel[4].setText("Adsr 3", NotificationType::dontSendNotification);
               btnLabel[5].setText("LFO", NotificationType::dontSendNotification);
               btnLabel[6].setText("", NotificationType::dontSendNotification);
               btnLabel[7].setText("", NotificationType::dontSendNotification);
               break;
               
           case 1:
               btnLabel[0].setText("", NotificationType::dontSendNotification);
               btnLabel[1].setText("", NotificationType::dontSendNotification);
               btnLabel[2].setText("", NotificationType::dontSendNotification);
               btnLabel[3].setText("", NotificationType::dontSendNotification);
               btnLabel[4].setText("", NotificationType::dontSendNotification);
               btnLabel[5].setText("", NotificationType::dontSendNotification);
               btnLabel[6].setText("", NotificationType::dontSendNotification);
               btnLabel[7].setText("", NotificationType::dontSendNotification);
               break;
               
           case 2:
               btnLabel[0].setText("", NotificationType::dontSendNotification);
               btnLabel[1].setText("", NotificationType::dontSendNotification);
               btnLabel[2].setText("", NotificationType::dontSendNotification);
               btnLabel[3].setText("", NotificationType::dontSendNotification);
               btnLabel[4].setText("", NotificationType::dontSendNotification);
               btnLabel[5].setText("", NotificationType::dontSendNotification);
               btnLabel[6].setText("", NotificationType::dontSendNotification);
               btnLabel[7].setText("", NotificationType::dontSendNotification);
               break;
               
           case 3:
               btnLabel[0].setText("", NotificationType::dontSendNotification);
               btnLabel[1].setText("", NotificationType::dontSendNotification);
               btnLabel[2].setText("", NotificationType::dontSendNotification);
               btnLabel[3].setText("", NotificationType::dontSendNotification);
               btnLabel[4].setText("", NotificationType::dontSendNotification);
               btnLabel[5].setText("", NotificationType::dontSendNotification);
               btnLabel[6].setText("", NotificationType::dontSendNotification);
               btnLabel[7].setText("", NotificationType::dontSendNotification);
               break;
        }
    }
    
    void setButtonRanges(){
           int from = 0;
           int to = 15;
           for(int i=0; i < 16; ++i){
               btnParam[i].setButtonText (toString(paramRoot * 256  + paramRange * 16 + from) + " - " + toString(paramRoot * 256 + paramRange * 16 + to));
               from += 16;
               to += 16;
           }
          setDials();
       }
    
    void paint (Graphics&) override{
        
    }
    
    void resized() override{
    // Buttons
       for(int i=0; i < 8; ++i){
            btnParam[i].setBounds (10 + i * 100,  5 , 100,  20);
       }
       for(int i=0; i < 8; ++i){
           btnParam[i+8].setBounds (10 + i * 100,  25 , 100,  20);
       }
        
        int xVal = 835;
       
        btnRange0.setBounds (xVal, 5, 60, 20);
        btnRange1.setBounds (xVal+70, 5, 60, 20);
        btnRange2.setBounds (xVal+140, 5, 60, 20);
        btnRange3.setBounds (xVal+210, 5, 60, 20);
        
         int yVal = 5;
        btnA.setBounds (xVal+280, yVal, 60, 20);
        btnB.setBounds (xVal+350, yVal, 60, 20);
        btnC.setBounds (xVal+420, yVal, 60, 20);
        btnD.setBounds (xVal+490, yVal, 60, 20);
        
        for(int i=0; i < 8; ++i){
            btnLabel[i].setBounds (10 + i * 100, 43, 100, 18);;
        }
        
        rootLabel[0].setBounds (xVal, 25, 60, 20);
        rootLabel[1].setBounds (xVal+70, 25, 60, 20);
        rootLabel[2].setBounds (xVal+140, 25, 60, 20);
        rootLabel[3].setBounds (xVal+210, 25, 60, 20);
    }
    
     PotsComponent * potsComponent;
    
private:
    int paramRoot = 0;
    int paramRange = 0;
    
    Label btnLabel[8];
    Label rootLabel[4];
   
    TextButton btnRange0;
    TextButton btnRange1;
    TextButton btnRange2;
    TextButton btnRange3;
    TextButton btnParam[16];
    
    TextButton btnA;
    TextButton btnB;
    TextButton btnC;
    TextButton btnD;
};

#endif /* ParamButtonComponent_h */
