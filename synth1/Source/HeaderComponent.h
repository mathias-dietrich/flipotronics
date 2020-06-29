//
//  HeaderComponent.h
//  synth1
//
//  Created by Mathias Dietrich on 28.06.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef HeaderComponent_h
#define HeaderComponent_h

#include "AbstractComponent.h"
#include "MasterPoti.h"
#include "OutputMeter.h"
#include "MasterSwitch.h"
#include "MasterPoti.h"

class HeaderComponent:  public AbstractComponent, public Slider::Listener, public Button::Listener{
   public:
   
    HeaderComponent () {
        
        potiMasterVol.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag );
        potiMasterVol.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, false, 100, 20);
        potiMasterVol.addListener (this);
        potiMasterVol.setRange(0-96, 18, 0.01);
        potiMasterVol.setSkewFactor (6);
        
        addAndMakeVisible(potiMasterVol);
        addAndMakeVisible(outputMeter);
        addAndMakeVisible(switch0);
        addAndMakeVisible(switch1);
        addAndMakeVisible(switch2);
        addAndMakeVisible(switch3);
        addAndMakeVisible(switch4);
        addAndMakeVisible(switch5);
        addAndMakeVisible(switchSave);
        
        btnProgUp.setButtonText (">");
        btnProgUp.addListener (this);
        btnProgUp.setRadioGroupId(22);
        addAndMakeVisible (btnProgUp);
        
        btnProgDown.setButtonText ("<");
        btnProgDown.addListener (this);
        btnProgDown.setRadioGroupId(23);
        addAndMakeVisible (btnProgDown);
        
        btnBrowse.setButtonText ("Browse");
        btnBrowse.addListener (this);
        btnBrowse.setRadioGroupId(26);
        addAndMakeVisible (btnBrowse);
        
        progName.setColour (Label::textColourId, C_PTACHNAME);
        progName.setJustificationType (Justification::centred);
        progName.setText("Flipotronics", NotificationType::dontSendNotification);
    
        auto f2 =  progName.getFont();
        f2.setSizeAndStyle(45, 0, 0.5, 0.5);
        f2.setBold(true);
        progName.setFont(f2);
        addAndMakeVisible(progName);
       
        progNumber.setColour (Label::textColourId,C_PTACHNAME);
        progNumber.setJustificationType (Justification::centred);
        progNumber.setText("1", NotificationType::dontSendNotification);
        
        progAuthor.setColour (Label::textColourId,C_PTACHNAME);
        addAndMakeVisible(progAuthor);
        progAuthor.setText("Hot Dreams - by Crazy Cat", NotificationType::dontSendNotification);
        
        auto f =  progNumber.getFont();
        f.setSizeAndStyle(20, 0, 0.5, 0.5);
        f.setBold(true);
        progNumber.setFont(f);
        addAndMakeVisible(progNumber);
        
        btnCompare.setButtonText ("Compare");
        btnCompare.addListener (this);
        btnCompare.setRadioGroupId(24);
        addAndMakeVisible (btnCompare);
        
        btnSave.setButtonText ("Save");
        btnSave.addListener (this);
        btnSave.setRadioGroupId(16);
        addAndMakeVisible (btnSave);
        
        btnLoad.setButtonText ("Load");
        btnLoad.addListener (this);
        btnLoad.setRadioGroupId(17);
        addAndMakeVisible (btnLoad);
        
        setDials();
    }
   
    ~HeaderComponent () {
      
    }
    
    void buttonClicked (Button* button)  override {

        // Save
        if(button->getRadioGroupId()==16) {
            BankLoader::of().save();
            Model::of().set();
            Model::of().compareMode = false;
            setDials();
           return;
        }
        
        // Load
        if(button->getRadioGroupId()==17) {
            BankLoader::of().load();
            processor->loadPatch(Model::of().patchCurrent);
            Model::of().set();
            Model::of().compareMode = false;
            setDials();
            return;
        }
        
           // Progr Up
           if(button->getRadioGroupId()==22) {
               Model::of().patchCurrent++;
               if(Model::of().patchCurrent >=127){
                   Model::of().patchCurrent = 0;
               }
               processor->loadPatch(Model::of().patchCurrent);
               Model::of().compareMode = false;
               Model::of().set();
               setDials();
               return;
           }
           
           // Progr Down
           if(button->getRadioGroupId()==23) {
               Model::of().patchCurrent--;
               if(Model::of().patchCurrent < 0){
                  Model::of().patchCurrent = 127;
               }
               
               processor->loadPatch(Model::of().patchCurrent);
               Model::of().compareMode = false;
               Model::of().set();
               setDials();
               return;
           }
           
           // Compare
           if(button->getRadioGroupId()==24) {
               Model::of().compareMode = !Model::of().compareMode;
               Model::of().swap();
               return;
           }
           
           // Browse
           if(button->getRadioGroupId()==26) {
               processor->browse();
               return;
           }
    }
        
    void paint (Graphics& g) override{
        Rectangle<int> r = getLocalBounds();
        auto width  = getLocalBounds().getWidth();
        auto height  = getLocalBounds().getHeight();
        
        g.fillAll (Colours::black);

        r.setX(5);
        r.setY(5);
        r.setWidth(100);
        r.setHeight(45);
        g.setColour(C_BRANDTITLE);
        Font f = fontLoader.getAntaro();
        f.setHeight(40.0f);
        f.setBold(true);
        g.setFont(f);
        g.drawFittedText (PRODUCTNAME, r, Justification::topLeft, 1);
         
        f.setHeight(11.0f);
        f.setBold(false);
        f.setItalic(true);
        g.setFont(f);
        g.drawFittedText (COMPANYNAME, r, Justification::bottomRight, 1);
        
        // Progname
        g.setColour (C_PROGNAME);
        g.fillRoundedRectangle(width/2-180, 2, 360,  46, 7);
        
        // ProgNumber
        g.setColour (C_PROGNAME);
        g.fillRoundedRectangle(885, 25, 45,  25, 7);
    }
    
    void setDials() override{
        progNumber.setText(toString(Model::of().patchCurrent+1), NotificationType::dontSendNotification);
        progName.setText(Model::of().patchNameCurrent, NotificationType::dontSendNotification);
        btnCompare.setToggleState(Model::of().compareMode, NotificationType::dontSendNotification);
        potiMasterVol.setValue(Model::of().par[P_MASTERVOL], dontSendNotification);
    }
    
    void resized() override{
        Rectangle<int> r = getLocalBounds();
        auto width  = r.getWidth();
        auto height  = r.getHeight();
        potiMasterVol.setBounds(width-80,6,40,40);
        outputMeter.setBounds(width-40,0,40,50);
        
        switch0.setBounds(150,0,50,50);
        switch1.setBounds(205,0,50,50);
        switch2.setBounds(260,0,50,50);
        switch3.setBounds(315,0,50,50);
        switch4.setBounds(370,0,50,50);
        switch5.setBounds(425,0,50,50);
        switchSave.setBounds(490,0,25,25);
        
        btnProgDown.setBounds (885, 3, 20, 20);
        btnProgUp.setBounds (910, 3, 20, 20);
       
        // Labels
        progName.setBounds(width/2-180, 5, 360,  40);
        progNumber.setBounds(880, 25, 60,  25);
        progAuthor.setBounds(930, 30, 200,  20);
        
        btnBrowse.setBounds (1000, 5, 70, 20);
        btnCompare.setBounds (1075, 5, 70, 20);
        btnSave.setBounds (1150, 5, 70, 20);
        btnLoad.setBounds (1225, 5, 70, 20);
    }
    
     void sliderValueChanged(Slider *  slider) override {
        Model::of().par[P_MASTERVOL] = slider->getValue();
     }
        
    Synth1AudioProcessor * processor;
    
private:
    FontLoader fontLoader;
    MasterPoti potiMasterVol;
    OutputMeter outputMeter;
    MasterSwitch switch0;
    MasterSwitch switch1;
    MasterSwitch switch2;
    MasterSwitch switch3;
    MasterSwitch switch4;
    MasterSwitch switch5;
    MasterSwitch switchSave;
    
    TextButton btnProgUp;
    TextButton btnProgDown;
    TextButton btnBrowse;
    TextButton btnSave;
    TextButton btnLoad;
    TextButton btnCompare;
    
    Label progName;
    Label progNumber;
    Label progAuthor;
    
};
#endif /* HeaderComponent_h */
