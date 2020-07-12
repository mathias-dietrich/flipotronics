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

        btnArp.setButtonText ("Arp");
        btnArp.addListener (this);
        btnArp.setRadioGroupId(27);
        addAndMakeVisible (btnArp);
        
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
        viewZoom.addItem ("75%", 2);
        viewZoom.addItem ("100%", 3);
        viewZoom.addItem ("125%", 4);
        viewZoom.addItem ("150%", 5);
        viewZoom.addItem ("200%", 6);
        viewZoom.onChange = [this] { styleMenuChangedViewZoom(); };
        
        viewZoom.setSelectedId(3,  NotificationType::dontSendNotification);
        
        setDials();
        
    }
   
    ~HeaderComponent () {
      
    }
    
    void styleMenuChangedViewZoom()
    {
        int ws = 1400;
        int hs = 780;
        float p = 1.0f;
        Desktop::getInstance().setGlobalScaleFactor(1);
        switch (viewZoom.getSelectedId())
        {
            case 1: // 50
                p = 0.5f;
                break;
            case 2: // 75
                p = 0.75f;
                break;
            case 3: // 100
                p = 1.0f;
                break;
            case 4: // 125
                p = 1.25f;
                break;
            case 5: // 150
                p = 1.5f;
                break;
                
            case 6: // 200
                p = 2.0f;
                break;
        }
        setSize (ws * p, hs * p);
        Desktop::getInstance().setGlobalScaleFactor((float)this->getWidth() / ws);
        repaint();
    }
    
    void build(Node node) override{
           
       }
    
    void buttonClicked (Button* button)  override {

        // Save
        if(button->getRadioGroupId()==106) {
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

        
        // Edit
        if(button->getRadioGroupId()==100) {
            switch0.setToggleState(true, NotificationType::dontSendNotification);
            switch1.setToggleState(false, NotificationType::dontSendNotification);
            switch2.setToggleState(false, NotificationType::dontSendNotification);
            switch3.setToggleState(false, NotificationType::dontSendNotification);
            switch4.setToggleState(false, NotificationType::dontSendNotification);
            switch5.setToggleState(false, NotificationType::dontSendNotification);
            Model::of().masterSel = mEdit;
            return;
        }
        
        // Lib
       if(button->getRadioGroupId()==101) {
           switch0.setToggleState(false, NotificationType::dontSendNotification);
           switch1.setToggleState(true, NotificationType::dontSendNotification);
           switch2.setToggleState(false, NotificationType::dontSendNotification);
           switch3.setToggleState(false, NotificationType::dontSendNotification);
           switch4.setToggleState(false, NotificationType::dontSendNotification);
           switch5.setToggleState(false, NotificationType::dontSendNotification);
           Model::of().masterSel = mLibrary;
           processor->browse();
           return;
       }
        
        // Perform
      if(button->getRadioGroupId()==102) {
          switch0.setToggleState(false, NotificationType::dontSendNotification);
          switch1.setToggleState(false, NotificationType::dontSendNotification);
          switch2.setToggleState(true, NotificationType::dontSendNotification);
          switch3.setToggleState(false, NotificationType::dontSendNotification);
          switch4.setToggleState(false, NotificationType::dontSendNotification);
          switch5.setToggleState(false, NotificationType::dontSendNotification);
          Model::of().masterSel = mPerform;
          return;
      }
        
    // Arp
        if(button->getRadioGroupId()==103) {
            switch0.setToggleState(false, NotificationType::dontSendNotification);
            switch1.setToggleState(false, NotificationType::dontSendNotification);
            switch2.setToggleState(false, NotificationType::dontSendNotification);
            switch3.setToggleState(true, NotificationType::dontSendNotification);
            switch4.setToggleState(false, NotificationType::dontSendNotification);
            switch5.setToggleState(false, NotificationType::dontSendNotification);
            Model::of().masterSel = mArp;
            return;
        }
        
        // Setup
        if(button->getRadioGroupId()==104) {
            switch0.setToggleState(false, NotificationType::dontSendNotification);
            switch1.setToggleState(false, NotificationType::dontSendNotification);
            switch2.setToggleState(false, NotificationType::dontSendNotification);
            switch3.setToggleState(false, NotificationType::dontSendNotification);
            switch4.setToggleState(true, NotificationType::dontSendNotification);
            switch5.setToggleState(false, NotificationType::dontSendNotification);
            Model::of().masterSel = mSetup;
            return;
        }
        
        // Debug
        if(button->getRadioGroupId()==105) {
            switch0.setToggleState(false, NotificationType::dontSendNotification);
            switch1.setToggleState(false, NotificationType::dontSendNotification);
            switch2.setToggleState(false, NotificationType::dontSendNotification);
            switch3.setToggleState(false, NotificationType::dontSendNotification);
            switch4.setToggleState(false, NotificationType::dontSendNotification);
            switch5.setToggleState(true, NotificationType::dontSendNotification);
            Model::of().masterSel = mDebug;
            return;
        }
        
        // ARP
           if(button->getRadioGroupId()==27) {
               if(processor->isArpOn){
                   btnArp.setButtonText ("Arp");
                   btnArp.setToggleState(false, NotificationType::dontSendNotification);
                   processor->isArpOn = false;
                   processor->panic();
               }else{
                   btnArp.setButtonText ("Arp");
                   btnArp.setToggleState(true, NotificationType::dontSendNotification);
                   processor->isArpOn = true;
               }
               processor->setArp(processor->isArpOn);
               return;
           }
    }
        
    void paint (Graphics& g) override{
        Rectangle<int> r = getLocalBounds();
        auto width  = getLocalBounds().getWidth();
        //auto height  = getLocalBounds().getHeight();
        
        g.fillAll (C_BLACK);

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
        if(processor){
            btnArp.setToggleState(processor->isArpOn, NotificationType::dontSendNotification);
        }
    }
    
    void resized() override{
        Rectangle<int> r = getLocalBounds();
        auto width  = r.getWidth();
        auto height  = r.getHeight();
        potiMasterVol.setBounds(width-80,6,40,40);
        outputMeter.setBounds(width-40,0,40,50);
        
        switch0.setBounds(150,1,50,48);
        switch1.setBounds(205,1,50,48);
        switch2.setBounds(260,1,50,48);
        switch3.setBounds(315,1,50,48);
        switch4.setBounds(370,1,50,48);
        switch5.setBounds(425,1,50,48);
        switchSave.setBounds(490,1,25,25);
        switchSave.setImages(false,true,true,ImageFactory::of().png[eFloppy],1.0f,{},ImageFactory::of().png[eFloppy],1.0f,{}, ImageFactory::of().png[eFloppy],1.0f,{});
        
        btnProgDown.setBounds (885, 3, 20, 20);
        btnProgUp.setBounds (910, 3, 20, 20);
       
        // Labels
        progName.setBounds(width/2-180, 5, 360,  40);
        progNumber.setBounds(880, 25, 60,  25);
        progAuthor.setBounds(930, 30, 200,  20);
        
        btnCompare.setBounds (1080, 5, 70, 20);
        viewZoom.setBounds (1160, 5, 70, 20);
        btnArp.setBounds (1240, 5, 70, 20);
    }
    
     void sliderValueChanged(Slider *  slider) override {
        Model::of().par[P_MASTERVOL] = slider->getValue();
     }
        
    Synth1AudioProcessor * processor;
    ComboBox viewZoom;
    
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
    TextButton btnArp;
    
    Label progName;
    Label progNumber;
    Label progAuthor;
    
};
#endif /* HeaderComponent_h */
