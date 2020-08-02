//
//  HeaderComponent.h
//  Deus
//
//  Created by Mathias Dietrich on 15.07.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef HeaderComponent_h
#define HeaderComponent_h

#include <JuceHeader.h>

#include "IComponent.h"
#include "FontLoader.h"
#include "MasterPoti.h"
#include "OutputMeter.h"
#include "MasterSwitch.h"
#include "MasterPoti.h"
#include "EventHandler.h"
#include "FileManager.h"

class HeaderComponent:  public IComponent, public Button::Listener, public Timer{
   public:
   
    HeaderComponent () {
        
        potiMasterVol.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag );
        potiMasterVol.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, false, 100, 20);
        potiMasterVol.addListener (this);
        potiMasterVol.setRange(-96, 6, 0.01);
        potiMasterVol.setSkewFactor (6);

        addAndMakeVisible(potiMasterVol);
        addAndMakeVisible(outputMeter);
        
        // mEdit, mLibrary, mPerform, mArp, mSetup
        
        switch0.setButtonText("Edit");
        switch0.masterSel = mEdit;
        switch0.setToggleState(true, NotificationType::dontSendNotification);
        switch0.setRadioGroupId(100);
        switch0.addListener (this);
        addAndMakeVisible(switch0);
        
        switch1.setButtonText("Library");
        switch1.masterSel = mLibrary;
        switch1.setRadioGroupId(101);
        switch1.addListener (this);
        addAndMakeVisible(switch1);
        
        switch2.masterSel = mPerform;
        switch2.setButtonText("Perform");
        switch2.setRadioGroupId(102);
        switch2.addListener (this);
        addAndMakeVisible(switch2);
        
        switch3.masterSel = mArp;
        switch3.setButtonText("Arp");
        switch3.setRadioGroupId(103);
        switch3.addListener (this);
        addAndMakeVisible(switch3);
        
        switch4.masterSel = mSetup;
        switch4.setButtonText("Setup");
        switch4.setRadioGroupId(104);
        switch4.addListener (this);
        addAndMakeVisible(switch4);
        
        switch5.masterSel = mDebug;
        switch5.setButtonText("Debug");
        switch5.setRadioGroupId(105);
        switch5.addListener (this);
        addAndMakeVisible(switch5);
        
        // switchSave.setButtonText("S");
        switchSave.addListener (this);
        switchSave.setRadioGroupId(106);
 
        addAndMakeVisible(switchSave);
        
        btnProgUp.setButtonText (">");
        btnProgUp.addListener (this);
        btnProgUp.setRadioGroupId(22);
        addAndMakeVisible (btnProgUp);
        
        btnProgDown.setButtonText ("<");
        btnProgDown.addListener (this);
        btnProgDown.setRadioGroupId(23);
        addAndMakeVisible (btnProgDown);
        
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

        addAndMakeVisible(viewZoom);
        viewZoom.addItem ("50%", 1);
        viewZoom.addItem ("60%", 2);
        viewZoom.addItem ("70%", 3);
        viewZoom.addItem ("80%", 4);
        viewZoom.addItem ("90%", 5);
        viewZoom.addItem ("100%", 6);
        viewZoom.addItem ("110%", 7);
        viewZoom.addItem ("120%", 8);
        viewZoom.addItem ("140%", 9);
        viewZoom.addItem ("160%", 10);
        viewZoom.addItem ("180%", 11);
        viewZoom.addItem ("200%", 12);
        viewZoom.onChange = [this] { styleMenuChangedViewZoom(); };
        viewZoom.setSelectedId(Model::of()->global.lastGuiZoom,  NotificationType::dontSendNotification);
        
        addAndMakeVisible(noOfVoices);
        for(int i=1;i<33;i++){
            noOfVoices.addItem (String(i), i);
        }
        
        setDials();
        
        
        startTimer(200);
    }
   
    ~HeaderComponent () {
      
    }
    
    void styleMenuChangedViewZoom()
    {
        eventHandler->resizeUi(viewZoom.getSelectedId());
        Core::of()->update(mGlobal, 1, noOfVoices.getSelectedId());
    }

    void timerCallback() override{
        outputMeter.repaint();
    }
    
    void buttonClicked (Button* button)  override {

        // Save
        if(button->getRadioGroupId()==106) {
            
                fileManager.save();
            
           // BankLoader::of().save();
           // Model::of().set();
           // Model::of().compareMode = false;
        }
        
        /*
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
         */
        
        // Edit
        if(button->getRadioGroupId()==100) {
            Model::of()->masterSel = mEdit;
        }
        
        // Lib
       if(button->getRadioGroupId()==101) {
           Model::of()->masterSel = mLibrary;
       }
        
      // Perform
      if(button->getRadioGroupId()==102) {
          Model::of()->masterSel = mPerform;
      }
        
      // Arp
        if(button->getRadioGroupId()==103) {
            Model::of()->masterSel = mArp;
        }
        
        // Setup
        if(button->getRadioGroupId()==104) {
            Model::of()->masterSel = mSetup;
        }
        
        // Debug
        if(button->getRadioGroupId()==105) {
            Model::of()->masterSel = mDebug;
        }
        setDials();
        eventHandler->update();
    }
    
    void paint (Graphics& g) override{
        Rectangle<int> r = getLocalBounds();
        auto width  = getLocalBounds().getWidth();
        //auto height  = getLocalBounds().getHeight();
        
        g.fillAll (C_BLACK);
        
        Image img = ImageFactory::of().get("header.png");
         g.drawImageAt(img, 0, 0);

        r.setX(5);
        r.setY(5);
        r.setWidth(100);
        r.setHeight(45);
        g.setColour(C_BRANDTITLE);
        Font f = fontLoader.getAntaro();
   
        f.setHeight(13.0f);
        f.setBold(false);
        f.setItalic(true);
        g.setFont(f);
       // g.drawFittedText (COMPANYNAME, r, Justification::bottomLeft, 1);
        
        // Progname
        g.setColour (C_PROGNAME);
        g.fillRoundedRectangle(width/2-180, 2, 360,  46, 7);
        
        // ProgNumber
        g.setColour (C_PROGNAME);
        g.fillRoundedRectangle(885, 25, 45,  25, 7);
    }
    
    void setDials() override{
        switch0.setToggleState(Model::of()->masterSel==mEdit, NotificationType::dontSendNotification);
        switch1.setToggleState(Model::of()->masterSel==mLibrary, NotificationType::dontSendNotification);
        switch2.setToggleState(Model::of()->masterSel==mPerform, NotificationType::dontSendNotification);
        switch3.setToggleState(Model::of()->masterSel==mArp, NotificationType::dontSendNotification);
        switch4.setToggleState(Model::of()->masterSel==mSetup, NotificationType::dontSendNotification);
        switch5.setToggleState(Model::of()->masterSel==mDebug, NotificationType::dontSendNotification);
        
       // progNumber.setText(toString(Model::of().patchCurrent+1), NotificationType::dontSendNotification);
       // progName.setText(Model::of().patchNameCurrent, NotificationType::dontSendNotification);
        //btnCompare.setToggleState(Model::of().compareMode, NotificationType::dontSendNotification);
       // potiMasterVol.setValue(Model::of().par[P_MASTERVOL], dontSendNotification);
        if(processor){
          //  btnArp.setToggleState(processor->isArpOn, NotificationType::dontSendNotification);
        }
        viewZoom.setSelectedId(Model::of()->global.lastGuiZoom,  NotificationType::dontSendNotification);
    }
    
    void resized() override{
        Rectangle<int> r = getLocalBounds();
        auto width  = r.getWidth();
       // auto height  = r.getHeight();
        
        viewZoom.setBounds (width-75, 3, 70, 16);
        noOfVoices.setBounds (width-75, 25, 70, 16);
        noOfVoices.setText("32");
        
        potiMasterVol.setBounds(width-160,6,40,40);
        outputMeter.setBounds(width-120,0,40,50);
        
        
        switch0.setBounds(150,1,50,48);
        switch1.setBounds(205,1,50,48);
        switch2.setBounds(260,1,50,48);
        switch3.setBounds(315,1,50,48);
        switch4.setBounds(370,1,50,48);
        switch5.setBounds(425,1,50,48);
        switchSave.setBounds(510,2,25,25);
        switchSave.setImages(false,true,true,ImageFactory::of().png[eFloppy],1.0f,{},ImageFactory::of().png[eFloppyOver],1.0f,{}, ImageFactory::of().png[eFloppyDown],1.0f,{});
        
        btnProgDown.setBounds (885, 3, 20, 20);
        btnProgUp.setBounds (910, 3, 20, 20);
       
        // Labels
        progName.setBounds(width/2-180, 5, 360,  40);
        progNumber.setBounds(880, 25, 60,  25);
        progAuthor.setBounds(930, 30, 200,  20);
        
        btnCompare.setBounds (485, 30, 50, 18);
    }
    
     void sliderValueChanged(Slider *  slider) override {
         Core::of()->update(mGlobal, 0, slider->getValue());
         setDials();
     }

    ComboBox viewZoom;
    ComboBox noOfVoices;

    
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
    ImageButton switchSave;
    
    TextButton btnProgUp;
    TextButton btnProgDown;
    TextButton btnCompare;
    
    Label progName;
    Label progNumber;
    Label progAuthor;
    
    Process * processor;
 
    private:
    FileManager fileManager;

};

#endif /* HeaderComponent_h */
