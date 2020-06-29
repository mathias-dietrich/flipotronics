#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Const.h"
#include "WaveTable.h"
#include "Func.h"

//==============================================================================
Synth1AudioProcessorEditor::Synth1AudioProcessorEditor (Synth1AudioProcessor& p) : 
    AudioProcessorEditor (&p),processor (p){

    Model::of().patchCurrent = 0;

    ImageFactory::of().init();
    
    //fileManager = new FileManager();
        BankLoader::of().load();
    processor.loadPatch(0);
    Model::of().set();
    Model::of().compareMode = false;
    
    btnArp.setButtonText ("Arp");
    btnArp.addListener (this);
    btnArp.setRadioGroupId(27);
    addAndMakeVisible (btnArp);
    
    addAndMakeVisible (timeLabel);
    timeLabel.setColour (Label::backgroundColourId, Colours::black);
    timeLabel.setColour (Label::textColourId, Colours::white);
    timeLabel.setJustificationType (Justification::centred);
    
    // Dropdowns
    viewMode.addItem ("Ouput", vPlot);
    viewMode.addItem ("Spectrum", vSpectrum);
    viewMode.addItem ("ADSR 1", vADSR1);
    viewMode.addItem ("ADSR 2", vADSR2);
    viewMode.addItem ("ADSR 3", vADSR3);
    viewMode.addItem ("ADSR 4", vADSR4);
    viewMode.addItem ("LFO 1", vLFO1);
    viewMode.addItem ("LFO 2", vLFO2);
    viewMode.addItem ("LFO 3", vLFO3);
    viewMode.addItem ("LFO 4", vLFO4);
    viewMode.addItem ("Curve", vCurve);
    viewMode.addItem ("Wave", vWave);
    viewMode.addItem ("Debug", vDebug);
    viewMode.onChange = [this] { styleMenuChangedView(); };
    Model::of().viewModeSetting = vWave;
    viewMode.setSelectedId(Model::of().viewModeSetting, NotificationType::dontSendNotification);
    addAndMakeVisible(viewMode);
        
    addAndMakeVisible(viewZoom);
    viewZoom.addItem ("50%", 1);
    viewZoom.addItem ("75%", 2);
    viewZoom.addItem ("100%", 3);
    viewZoom.addItem ("125%", 4);
    viewZoom.addItem ("150%", 5);
    viewZoom.addItem ("200%", 6);
    viewZoom.onChange = [this] { styleMenuChangedViewZoom(); };
    
    viewZoom.setSelectedId(3,  NotificationType::dontSendNotification);
    
    // Components
    headerComponent.processor = &processor;
    addAndMakeVisible(headerComponent);
    addChildComponent(processor.spectrum);
    addChildComponent(processor.outputComponent);
    addChildComponent(processor.adsrComponent);
    addAndMakeVisible(processor.waveComponent);
    addChildComponent(processor.lfoComponent);
    addChildComponent(processor.curveComponent);
    addAndMakeVisible(potsComponent);
        
    keysComponent = new KeysComponent(p);
    addAndMakeVisible(keysComponent);
        
    addAndMakeVisible(paramButtonComponent);
    addAndMakeVisible(viewMeterComponent);
    addAndMakeVisible(debugComponent);
    debugComponent.processor = &processor;

    startTimer(1000 / SCOPEFRAMES);
    setSize (1400, 780);
        
    setDials();
}

Synth1AudioProcessorEditor::~Synth1AudioProcessorEditor(){
    ImageFactory::of().close();
    delete keysComponent;
}

// ==================================================================================================
// Resize
// ==================================================================================================
void Synth1AudioProcessorEditor::resized() {
    Rectangle<int> r = getLocalBounds();
    int width = r.getWidth();
    int height = r.getHeight();
   
    btnArp.setBounds (840, 310, 120, 25);
    
    // Drop Downs
    viewMode.setBounds (840, 340, 120, 20);
    viewZoom.setBounds (width-90, 55, 80, 20);
    
    // Spectrum
    int componentY = 370;
    int componentHeight = 310;
    processor.spectrum.setBounds(0, componentY, width,  componentHeight);
    processor.waveComponent.setBounds(0, componentY, width,  componentHeight);
    processor.outputComponent.setBounds(0, componentY, width,  componentHeight);
    processor.adsrComponent.setBounds(0, componentY, width,  componentHeight);
    processor.lfoComponent.setBounds(0, componentY, width,  componentHeight);
    processor.curveComponent.setBounds(0, componentY, width,  componentHeight);
    
    potsComponent.setBounds(0, 110, 830,  260);
    
    keysComponent->setBounds(0, height-90, width,  90);
    paramButtonComponent.setBounds(0, 50, 1230,  60);
    paramButtonComponent.potsComponent = &potsComponent;
    paramButtonComponent.setDials();
    
    viewMeterComponent.setBounds(840, 100, 260,  80);
    debugComponent.setBounds(width-280, 110, 270,  250);
    headerComponent.setBounds(0, 0, width,  50);
    /*
    debugComponent.setVisible(false);
    viewMeterComponent.setVisible(false);
    paramButtonComponent.setVisible(false);
    keysComponent->setVisible(false);
    potsComponent.setVisible(false);
     */
}

// ==================================================================================================
// paint
// ==================================================================================================

inline const char * const BoolToString(bool b)
{
  return b ? "true" : "false";
}

void Synth1AudioProcessorEditor::paint (Graphics& g)
{
    Rectangle<int> r = getLocalBounds();
    int width = r.getWidth();
    int height = r.getHeight() ;

    // BG
    g.fillAll (C_BACKGROUND);
    

}

