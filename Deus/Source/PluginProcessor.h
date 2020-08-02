/*
  ==============================================================================
Atom Synth, flipotoronics.com - Author: Mathias Dietrich
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "Inc.h"
#include "IModule.h"
#include "Core.h"

//==============================================================================
/**
*/
class DeusAudioProcessor  : public AudioProcessor
{
    
protected:
      static DeusAudioProcessor *instance;
    
public:
    //==============================================================================
    DeusAudioProcessor();
    ~DeusAudioProcessor();
    
    static DeusAudioProcessor * of(){
        return instance;
    }

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    void handleNoteOn (MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity)  {
        core.startVoice( midiChannel,  midiNoteNumber,  velocity,0);
    }
        
    void handleNoteOff (MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity)  {
        core.endVoice( midiChannel,  midiNoteNumber);
    }

    void panic(){
        core.killAllVoice();
    }
    
    Core core;
    FileManager fileManager;

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeusAudioProcessor)
};
