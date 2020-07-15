/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

#include "Inc.h"
#include "MasterComponent.h"

//==============================================================================
/**
*/
class DeusAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    DeusAudioProcessorEditor (DeusAudioProcessor&);
    ~DeusAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    DeusAudioProcessor& processor;
    
    MasterComponent masterComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeusAudioProcessorEditor)
};
