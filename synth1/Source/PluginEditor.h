/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class Synth1AudioProcessorEditor  : public AudioProcessorEditor
{
public:
    Synth1AudioProcessorEditor (Synth1AudioProcessor&);
    ~Synth1AudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

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
};
