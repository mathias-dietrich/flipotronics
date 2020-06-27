//
//  KeysComponent.h
//  synth1
//
//  Created by Mathias Dietrich on 27.06.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef KeysComponent_h
#define KeysComponent_h
#include <stdio.h>
#include <JuceHeader.h>
#include "CircularBuffer.h"
#include "Func.h"
#include "Color.h"
#include "Poti.h"
#include "PitchWheel.h"
#include "AbstractComponent.h"

class KeysComponent : public AbstractComponent, public MidiKeyboardStateListener,  public Button::Listener, public Slider::Listener{
    
 public:
    KeysComponent(Synth1AudioProcessor& p) : keyboardComponent (keyboardState,
        MidiKeyboardComponent::horizontalKeyboard), processor (p){
        
        keyboardState.addListener (this);
        addAndMakeVisible(keyboardComponent);
        
        pitchWheel.setSliderStyle(Slider::SliderStyle::LinearVertical );
        pitchWheel.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, false, 100, 20);
        pitchWheel.setNumDecimalPlacesToDisplay(2);
        pitchWheel.setName("100");
        pitchWheel.addListener (this);
        pitchWheel.setRange(-8192, 8192, 1);
        pitchWheel.setValue(0);
        addAndMakeVisible(pitchWheel);
        
        modWheel.setSliderStyle(Slider::SliderStyle::LinearVertical );
        modWheel.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, false, 100, 20);
        modWheel.setNumDecimalPlacesToDisplay(2);
        modWheel.setName("101");
        modWheel.addListener (this);
        modWheel.setRange(0, 127,1);
        addAndMakeVisible(modWheel);
        
        expWheel.setSliderStyle(Slider::SliderStyle::LinearVertical );
        expWheel.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, false, 100, 20);
        expWheel.setNumDecimalPlacesToDisplay(2);
        expWheel.setName("102");
        expWheel.addListener (this);
        expWheel.setRange(0, 127,1);
        addAndMakeVisible(expWheel);
        
        btnLatch.setButtonText ("Latch");
        btnLatch.addListener (this);
        btnLatch.setRadioGroupId(28);
        addAndMakeVisible (btnLatch);
        
        btnPanic.setButtonText ("Panic");
        btnPanic.addListener (this);
        btnPanic.setRadioGroupId(25);
        addAndMakeVisible (btnPanic);
        
        playMode.addItem ("Poly", 1);
        playMode.addItem ("Unisono", 2);
        playMode.addItem ("Mono", 3);
        playMode.addItem ("Legato", 4);
        playMode.onChange = [this] { styleMenuChanged(); };
        playMode.setSelectedId(Model::of().par[1023], NotificationType::dontSendNotification);
        addAndMakeVisible(playMode);
    }
    
    ~KeysComponent () {

    }
    
    void buttonClicked (Button* button)  override {
       // Panic
       if(button->getRadioGroupId()==25) {
           processor.panic();
           return;
       }
    }
       
    void paint (Graphics& g) override {
        Rectangle<int> r = getLocalBounds();
        g.setColour (C_KEYBORDAREA);
        g.fillRect(r);
    }
    
    void sliderDragEnded(Slider *) override{
        pitchWheel.setValue(0);
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
    }
    
    void resized() override{
        Rectangle<int> r = getLocalBounds();
        int width = r.getWidth();
        int height = r.getHeight();
        
        keyboardComponent.setBounds (112, 10, 1187,  80);
        keyboardComponent.setKeyWidth(26.5);
        keyboardComponent.setAvailableRange(33, 108);
        
        // Live Controller
        pitchWheel.setBounds(5, 0, 30, 97);
        modWheel.setBounds (40, 0, 30, 97);
        expWheel.setBounds (75, 0, 30, 97);
        
        btnLatch.setBounds (width-90, 8, 80, 22);
        btnPanic.setBounds (width-90, 64, 80, 22);
        
        playMode.setBounds (width-90, 36, 80, 21);
        playMode.setEditableText(false);
    }
    
    void handleNoteOn (MidiKeyboardState* state, int midiChannel, int midiNoteNumber, float velocity) override {
        processor.handleNoteOn(state, midiChannel, midiNoteNumber, velocity);
    }
        
    void handleNoteOff (MidiKeyboardState* state, int midiChannel, int midiNoteNumber, float velocity) override {
        processor.handleNoteOff(state, midiChannel, midiNoteNumber, velocity);
    }
    
    void styleMenuChanged(){
           switch (playMode.getSelectedId())
           {
               case 1: // Poly
                   Model::of().par[1023] = 1;
                   break;
               case 2: // Unisono
                   Model::of().par[1023] = 2;
                   break;
               case 3: // Mono
                   Model::of().par[1023] = 3;
                   break;
               case 4: // Legato
                   Model::of().par[1023] = 4;
                   break;
           }
       }

    MidiKeyboardState keyboardState;
    MidiKeyboardComponent keyboardComponent;
    
private:
    Synth1AudioProcessor& processor;
    PitchWheel pitchWheel;
    PitchWheel modWheel;
    PitchWheel expWheel;
    
    TextButton btnLatch;
    TextButton btnPanic;
    
    ComboBox playMode;
};

#endif /* KeysComponent_h */
