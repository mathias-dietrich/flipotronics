/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "SynthAudioSource.h"
#include "Func.h"
#include "Model.h"
#include "FileManager.h"
//==============================================================================
/**
*/
class Synth1AudioProcessorEditor  : public AudioProcessorEditor,MidiKeyboardStateListener,
    public Button::Listener,  public Slider::Listener
{
public:
    Synth1AudioProcessorEditor (Synth1AudioProcessor&);
    ~Synth1AudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    MidiKeyboardState keyboardState;
    MidiKeyboardComponent keyboardComponent;
    
    TextButton btnParam[16];
    TextButton btnSave;
    TextButton btnLoad;
    
    TextButton btnRange0;
    TextButton btnRange1;
    TextButton btnRange2;
    TextButton btnRange3;
    
    TextButton btnProgUp;
    TextButton btnProgDown;
    TextButton btnPanic;
    
    Label timeLabel;
    
    TextEditor boxes[16];
    Slider dials[16] ;
    
    FileManager *fileManager;
    
    int paramRange = 0;
    int paramRoot = 0;
    
    ComboBox playMode;
    ComboBox viewMode;
    
    Slider pitchWheel;
    Slider modWheel;
    Slider expWheel;
    
    Label progName;
    Label progNumber;

private:

    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Synth1AudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Synth1AudioProcessorEditor)
    
    void drawsome(Graphics& g, int half, int width, float * buf ){
        int lastX = 0;
        int lastY = half;
        for(int i=0; i< width;++i){
            int v = half - buf[i * OVERSAMPLING] * 200;
             g.drawLine (lastX, lastY, i, v, 1.0f);
            lastX = i;
            lastY = v;
        }
    }
    
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
             fileManager->save();
           return;
        }
        
        // Load
        if(button->getRadioGroupId()==17) {
            fileManager->load();
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
        
        if(button->getRadioGroupId()==22) {
           // Progr Up
            patchCurrent++;
            if(patchCurrent >=128){
                patchCurrent = 1;
            }
            setDials();
            return;
        }
        
        if(button->getRadioGroupId()==23) {
            patchCurrent--;
            if(patchCurrent < 1){
               patchCurrent = 128;
            }
            setDials();
            return;
        }
        
        // Panic
        if(button->getRadioGroupId()==24) {
            processor.panic();
            return;
        }
        
        paramRange = button->getRadioGroupId();
        setDials();
    }
    
    void setDials(){
        for(int i=0; i < 16; ++i){
            int pid = paramRoot * 256 + paramRange * 16 + i;
            boxes[i].setText(params[pid].name);
            dials[i].setRange(params[pid].minVal,params[pid].maxVal,params[pid].stepVal);
            dials[i].setValue(par[pid], dontSendNotification);
        }
        // Param Select
        for(int i=0; i < 16; ++i){
            btnParam[i].setToggleState(false, NotificationType::dontSendNotification);
        }
        btnParam[paramRange].setToggleState(true, NotificationType::dontSendNotification);
        progNumber.setText(toString(patchCurrent), NotificationType::dontSendNotification);
    }
    
    void sliderValueChanged(Slider *  slider) override {
        int sid = slider->getName().getIntValue();
        
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
        par[paramRoot * 256 + paramRange * 16 + sid] = slider->getValue();
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
        switch (viewMode.getSelectedId())
        {
            case 1: // Wave
                viewModeSetting = 1;
                break;
            case 2: // Matrix
                viewModeSetting = 2;
                break;
            case 3: // debug
                viewModeSetting = 3;
                break;
        }
        repaint();
    }
    
    
    void sliderDragEnded(Slider *) override{
        pitchWheel.setValue(8192);
    }

};
