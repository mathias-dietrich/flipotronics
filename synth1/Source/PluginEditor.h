#pragma once

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

//============Poti==================================================================
/**
*/
class Synth1AudioProcessorEditor  : public AudioProcessorEditor,MidiKeyboardStateListener,
    public Button::Listener,  public Slider::Listener,public Timer
{
public:
    Synth1AudioProcessorEditor (Synth1AudioProcessor&);
    ~Synth1AudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    MidiKeyboardState keyboardState;
    MidiKeyboardComponent keyboardComponent;
    
    Curve curve;

    TextButton btnParam[16];
    Label btnLabel[8];
    Label rootLabel[4];
    TextButton btnSave;
    TextButton btnLoad;
    TextButton btnCompare;
    
    TextButton btnRange0;
    TextButton btnRange1;
    TextButton btnRange2;
    TextButton btnRange3;
    
    TextButton btnProgUp;
    TextButton btnProgDown;
    TextButton btnPanic;
    TextButton btnBrowse;
    TextButton btnArp;
    
    Label timeLabel;
    
   // TextEditor boxes[16];
    Poti dials[16] ;
    
    BankLoader *bankLoader;
    
    int paramRange = 0;
    int paramRoot = 0;
    
    ComboBox playMode;
    ComboBox viewMode;
    ComboBox viewZoom;
    
    PitchWheel pitchWheel;
    PitchWheel modWheel;
    PitchWheel expWheel;
    
    Label progName;
    Label progNumber;

    int maxTime;

private:
    Synth1AudioProcessor& processor;
   // Image vumeter; // = ImageCache::getFromMemory (img::meter_png, img::meter_pngSize);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Synth1AudioProcessorEditor)
    
    void handleNoteOn (MidiKeyboardState* state, int midiChannel, int midiNoteNumber, float velocity) override
    {
        processor.handleNoteOn(state, midiChannel, midiNoteNumber, velocity);
    }
     
    void handleNoteOff (MidiKeyboardState* state, int midiChannel, int midiNoteNumber, float velocity) override
    {
        processor.handleNoteOff(state, midiChannel, midiNoteNumber, velocity);
    }
    
    void buttonClicked (Button* button)  override // [2]
    {
        // Save
        if(button->getRadioGroupId()==16) {
            bankLoader->save();
            Model::of().set();
            compareMode = false;
            setDials();
           return;
        }
        
        // Load
        if(button->getRadioGroupId()==17) {
            bankLoader->load();
            processor.loadPatch(patchCurrent);
            Model::of().set();
            compareMode = false;
            setDials();
            return;
        }
        
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
        
        // Progr Up
        if(button->getRadioGroupId()==22) {
            patchCurrent++;
            if(patchCurrent >=127){
                patchCurrent = 0;
            }
            processor.loadPatch(patchCurrent);
            compareMode = false;
            Model::of().set();
            setDials();
            return;
        }
        
        // Progr Down
        if(button->getRadioGroupId()==23) {
            patchCurrent--;
            if(patchCurrent < 0){
               patchCurrent = 127;
            }
            
            processor.loadPatch(patchCurrent);
            compareMode = false;
            Model::of().set();
            
            setDials();
            return;
        }
        
        // Compare
        if(button->getRadioGroupId()==24) {
            compareMode = !compareMode;
            Model::of().swap();
            setDials();
            return;
        }
        
        // Panic
        if(button->getRadioGroupId()==25) {
            processor.panic();
            return;
        }
        
        // Browse
        if(button->getRadioGroupId()==26) {
            processor.browse();
            return;
        }
        
        // ARP
        if(button->getRadioGroupId()==27) {
            if(processor.isArpOn){
                btnArp.setButtonText ("Arp");
                btnArp.setToggleState(false, NotificationType::dontSendNotification);
                processor.isArpOn = false;
                processor.panic();
            }else{
                btnArp.setButtonText ("Arp");
                btnArp.setToggleState(true, NotificationType::dontSendNotification);
                processor.isArpOn = true;
            }
            processor.setArp(processor.isArpOn);
            return;
        }
        paramRange = button->getRadioGroupId();
        setDials();
    }
    
    void setDials(){
        for(int i=0; i < 16; ++i){
            int pid = paramRoot * 256 + paramRange * 16 + i;
            dials[i].setRange(params[pid].minVal,params[pid].maxVal,params[pid].stepVal);
            dials[i].setTitle(params[pid].name);
           // boxes[i].setText(params[pid].name);
            if( params[pid].type == uWaveType){
                dials[i].setTextValueSuffix(" " + getWaveType(E_WaveType(int(par[pid]))));
                dials[i].setValue(par[pid], dontSendNotification);
            }else if( params[pid].type == uFilterType){
                   dials[i].setTextValueSuffix(" " + getFilterTypeString(MultiModeLadderFilterTypes(int(par[pid]))));
                   dials[i].setValue(par[pid], dontSendNotification);
            }
            else if( params[pid].type == uPhase){
                dials[i].setTextValueSuffix(" degrees");
                dials[i].setValue(par[pid], dontSendNotification);
            }
            else if( params[pid].type == uTimeMsec){
                dials[i].setTextValueSuffix(" msec");
                dials[i].setSkewFactor(0.5);
                dials[i].setValue(par[pid], dontSendNotification);
            }
            else if( params[pid].type == uDb){
                dials[i].setSkewFactor (6);
                dials[i].setTextValueSuffix(" dB");
                dials[i].setValue(par[pid], dontSendNotification);
            }
            else if( params[pid].type == uHZ){
                dials[i].setSkewFactor (0.3);
                dials[i].setTextValueSuffix(" Hz");
                dials[i].setValue(par[pid], dontSendNotification);
            }
            else if( params[pid].type == uBool){
                bool test = par[pid];
                String text = test ? " on" : " off" ;
                dials[i].setTextValueSuffix(text);
            }
            else if( params[pid].type == uCurve){
                dials[i].setSkewFactor(1);
                dials[i].setTextValueSuffix(" %");
                dials[i].setValue(par[pid], dontSendNotification);
            }
            else if( params[pid].type == uMidiNote){
               dials[i].setTextValueSuffix(" " + midiNote(par[pid]));
               dials[i].setValue(par[pid], dontSendNotification);
            }
            else if( params[pid].type == uDevision){
               dials[i].setTextValueSuffix(" " + devision(par[pid]));
               dials[i].setValue(par[pid], dontSendNotification);
            }
            else if( params[pid].type == uArpMode){
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
            else if( params[pid].type == uChordMode){
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
        // Param Select
        for(int i=0; i < 16; ++i){
            btnParam[i].setToggleState(false, NotificationType::dontSendNotification);
        }
        if(paramRange<16){
            btnParam[paramRange].setToggleState(true, NotificationType::dontSendNotification);
        }
        progNumber.setText(toString(patchCurrent+1), NotificationType::dontSendNotification);
        progName.setText(patchNameCurrent, NotificationType::dontSendNotification);
        btnCompare.setToggleState(compareMode, NotificationType::dontSendNotification);
        
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
        btnArp.setToggleState(processor.isArpOn, NotificationType::dontSendNotification);
        isUpdateParams = true;
    }
    
    void sliderValueChanged(Slider *  slider) override {
        int sid = slider->getName().getIntValue();
        
        // Performances
        
        // Pitch Wheel
        if(sid==100){
            return;
        }
        
        // Mod Wheel
        if(sid==101){
            return;
        }
        
        // Exp Wheel
        if(sid==102){
            return;
        }

        // Edits Mode ================================================================
        startEdit();
        int pid = paramRoot * 256 + paramRange * 16 + sid;
        if(params[pid].smoothTime > 0){
            parTargetDelta[pid] = par[pid] - slider->getValue();
        }else{
            par[pid] = slider->getValue();
        }
        setDials();
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
    
    void styleMenuChanged(){
        switch (playMode.getSelectedId())
        {
            case 1: // Poly
                par[1023] = 1;
                break;
            case 2: // Unisono
                par[1023] = 2;
                break;
            case 3: // Mono
                par[1023] = 3;
                break;
            case 4: // Legato
                par[1023] = 4;
                break;
        }
        setDials();
    }
    
    void styleMenuChangedView(){
        viewModeSetting = viewMode.getSelectedId();
        processor.spectrum.setVisible(false);
        processor.waveComponent.setVisible(false);
        processor.outputComponent.setVisible(false);
        processor.adsrComponent.setVisible(false);
        processor.lfoComponent.setVisible(false);

        switch(viewModeSetting){
            case vSpectrum:
                processor.spectrum.setVisible(true);
                break;
                
            case vADSR1:
            case vADSR2:
            case vADSR3:
            case vADSR4:
                processor.adsrComponent.setVisible(true);
                break;
            
           case vWave:
                processor.waveComponent.setVisible(true);
                break;
                
            case vPlot:
                processor.outputComponent.setVisible(true);
                break;
                
            case vLFO1:
            case vLFO2:
            case vLFO3:
            case vLFO4:
                processor.lfoComponent.setVisible(true);
                break;
        }
        repaint();
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
    
    void sliderDragEnded(Slider *) override{
        pitchWheel.setValue(0);
    }
    
    void timerCallback() override{
        repaint();
        setDials();
    }
    
    void startEdit(){
        compareMode = true;
    }
};
