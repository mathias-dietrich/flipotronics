#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DeusAudioProcessorEditor::DeusAudioProcessorEditor (DeusAudioProcessor& p) : AudioProcessorEditor (&p), processor (p) {
    setSize (UIWIDTH, UIHEIGHT);
    masterComponent.init(UIWIDTH, UIHEIGHT);
    masterComponent.eventHandler = this;
    
    // build Model
    fileManager.load();
    
    // load UI
    uiloader.load(node, "master.xml");
    masterComponent.build(node);
    addAndMakeVisible(masterComponent);
    
   
    masterComponent.resized();
    
    
    
    startTimer(200);
    
    addKeyListener(this);
}

DeusAudioProcessorEditor::~DeusAudioProcessorEditor() {
    delete node;
}

//==============================================================================
void DeusAudioProcessorEditor::paint (Graphics& g) {
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void DeusAudioProcessorEditor::resized() {
    masterComponent.setBounds(0,0,UIWIDTH,UIHEIGHT);
}
