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
    factory = new ComponentFactory();
    masterComponent.init(UIWIDTH, UIHEIGHT);
    masterComponent.factory = factory;
    uiloader.load(node, "master.xml");
    masterComponent.build(node);
    masterComponent.handler = this;
    addAndMakeVisible(masterComponent);
    masterComponent.resized();
}

DeusAudioProcessorEditor::~DeusAudioProcessorEditor()
{
     // delete masterComponent;
    delete node;
    delete factory;
}

//==============================================================================
void DeusAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void DeusAudioProcessorEditor::resized()
{
    masterComponent.setBounds(0,0,UIWIDTH,UIHEIGHT);
    
}
