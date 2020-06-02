/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Const.h"
#include "WaveTable.h"

//==============================================================================
Synth1AudioProcessorEditor::Synth1AudioProcessorEditor (Synth1AudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p), 
    keyboardComponent (keyboardState, MidiKeyboardComponent::horizontalKeyboard)
{

    addAndMakeVisible (keyboardComponent);
    setSize (800, 600);
    keyboardState.addListener (this);
    //startTimer (400);
}

Synth1AudioProcessorEditor::~Synth1AudioProcessorEditor()
{
}

//==============================================================================
void Synth1AudioProcessorEditor::paint (Graphics& g)
{
    
    Rectangle<int> r = getLocalBounds();
    int width = r.getWidth();
    int height = r.getHeight();
    int half = height / 2;
    
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText (VERSION, r, Justification::topRight, 1);
                            // [13]
    g.drawLine (0, half, width, half, 1.0f);
    WaveTable *w = new WaveTable();
    w->init(width, width);
    
    auto buf = w->sinBuffer;
    g.setColour (Colours::red);
    drawsome( g,  half,  width,  buf );
    
    buf = w->triangleBuffer;
    g.setColour (Colours::green);
    drawsome( g,  half,  width,  buf );
    
    buf = w->sawBuffer;
    g.setColour (Colours::blue);
    drawsome( g,  half,  width,  buf );

    buf = w->squareBuffer;
    g.setColour (Colours::yellow);
    drawsome( g,  half,  width,  buf );
    
    buf = w->whiteBuffer;
    g.setColour (Colours::white);
    //drawsome( g,  half,  width,  buf );
    
    delete w;
}

void Synth1AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
     keyboardComponent.setBounds (0,  getHeight() - 50, getWidth(),  50);
}


