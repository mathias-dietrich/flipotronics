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
    Label timeLabel;
    
    TextEditor boxes[16];
    Slider dials[16] ;
    
    FileManager *fileManager;
    
    int btnRange = 0;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Synth1AudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Synth1AudioProcessorEditor)
    
    void drawsome(Graphics& g, int half, int width, float * buf ){
        int lastX = 0;
        int lastY = half;
        for(int i=0; i< width;++i){
            int v = half - buf[i] * 200;
             g.drawLine (lastX, lastY, i, v, 1.0f);
            lastX = i;
            lastY = v;
        }
    }
    
    void timerCallback()
    {
        keyboardComponent.grabKeyboardFocus();
        //stopTimer();
    }
    
    void handleNoteOn (MidiKeyboardState* state, int midiChannel, int midiNoteNumber, float velocity) override
    {
        processor.handleNoteOn(state, midiChannel, midiNoteNumber, velocity);
    }
     
    void handleNoteOff (MidiKeyboardState* state, int midiChannel, int midiNoteNumber, float velocity) override
    {
        processor.handleNoteOn(state, midiChannel, midiNoteNumber, velocity);
    }
    
    void buttonClicked (Button* button)  override // [2]
    {
        btnRange = button->getRadioGroupId();
        
        // Save
        if(btnRange==16) {
             fileManager->save();
           return;
        }
        
        // Load
        if(btnRange==17) {
            fileManager->load();
            btnRange = 0;
            setDials();
            return;
        }
    
        // Param Select
        for(int i=0; i < 16; ++i){
            btnParam[i].setToggleState(false, NotificationType::dontSendNotification);
        }
        btnParam[btnRange].setToggleState(true, NotificationType::dontSendNotification);
        setDials();
    }
    
    void setDials(){
        for(int i=0; i < 16; ++i){
            boxes[i].setText("Param " + toString( btnRange * 16 + i));
            dials[i].setValue(par[btnRange * 16 + i]);
        }
    }
    
    void sliderValueChanged(Slider *  slider) override
    {
        int sid = slider->getName().getIntValue();
        par[btnRange * 16 + sid] = slider->getValue();
    }
};
