/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DeusAudioProcessorEditor::DeusAudioProcessorEditor (DeusAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (UIWIDTH, UIHEIGHT);
    masterComponent.init(UIWIDTH, UIHEIGHT);
    addAndMakeVisible(masterComponent);
}

DeusAudioProcessorEditor::~DeusAudioProcessorEditor()
{
}

//==============================================================================
void DeusAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    /*
    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
     */
}

void DeusAudioProcessorEditor::resized()
{
    masterComponent.setBounds(0,0,UIWIDTH,UIHEIGHT);
}
