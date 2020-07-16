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
#include "EventHandler.h"
#include "UILoader.h"

//==============================================================================
/**
*/
class DeusAudioProcessorEditor  : public AudioProcessorEditor, public EventHandler
{
public:
    DeusAudioProcessorEditor (DeusAudioProcessor&);
    ~DeusAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    void resizeAll(float prozent)override{
        Desktop::getInstance().setGlobalScaleFactor(1);
       float ws = UIWIDTH;
       int hs = UIHEIGHT;
       setSize (ws * prozent, hs * prozent);
       Desktop::getInstance().setGlobalScaleFactor((float)this->getWidth() / ws);
       repaint();
    }

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    DeusAudioProcessor& processor;
    
    MasterComponent masterComponent;
    UILoader uiloader;
    ComponentFactory *factory;
    Node * node = new Node();
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeusAudioProcessorEditor)
};
