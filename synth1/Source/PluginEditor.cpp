#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Const.h"
#include "WaveTable.h"
#include "Func.h"

//==============================================================================
Synth1AudioProcessorEditor::Synth1AudioProcessorEditor (Synth1AudioProcessor& p) : 
    AudioProcessorEditor (&p),processor (p){
    
    Node rootNode;
    uiLoader.loadRoot(rootNode);
    rootComponent = new RootComponent();
    rootComponent->build(rootNode);

    addKeyListener(this);
        
    Model::of().patchCurrent = 0;
    ImageFactory::of().init();
    Model::of().set();
    Model::of().compareMode = false;
    
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
    viewMode.addItem ("Table", vTable);
        
    viewMode.onChange = [this] { styleMenuChangedView(); };
    Model::of().viewModeSetting = vPlot;
    viewMode.setSelectedId(Model::of().viewModeSetting, NotificationType::dontSendNotification);
    addAndMakeVisible(viewMode);
    
    // Components
    headerComponent.processor = &processor;
    addAndMakeVisible(headerComponent);
    addChildComponent(processor.spectrum);
    addAndMakeVisible(processor.outputComponent);
    addChildComponent(processor.adsrComponent);
    addAndMakeVisible(processor.waveComponent);
    addChildComponent(processor.lfoComponent);
    addChildComponent(processor.curveComponent);
    addChildComponent(processor.showTableComponent);
    addAndMakeVisible(potsComponent);
        
    addAndMakeVisible(rootComponent);
        
    keysComponent = new KeysComponent(p);
    addAndMakeVisible(keysComponent);
        
    addAndMakeVisible(paramButtonComponent);
    addAndMakeVisible(viewMeterComponent);
    addAndMakeVisible(debugComponent);
    debugComponent.processor = &processor;
        
    addChildComponent(performanceComponent);
    addChildComponent(libraryComponent);
    addChildComponent(arpComponent);
    addChildComponent(setupComponent);
        
    startTimer(1000 / SCOPEFRAMES);
    setSize (1400, 780);
        
    setDials();
        
       // auto window = dynamic_cast<ResizableWindow*>(getTopLevelComponent());
        //window->setFullScreen(true);

       // String windowsPlace = window->getWindowStateAsString();
}

Synth1AudioProcessorEditor::~Synth1AudioProcessorEditor(){
    ImageFactory::of().close();
    delete keysComponent;
    delete rootComponent;
}

// ==================================================================================================
// Resize
// ==================================================================================================
void Synth1AudioProcessorEditor::resized() {
    Rectangle<int> r = getLocalBounds();
    int width = r.getWidth();
    int height = r.getHeight();
   
    // Drop Downs
    viewMode.setBounds (width - 120, 350, 120, 20);
    viewMode.setSelectedId(1);

    // Spectrum
    int componentY = 370;
    int componentHeight = 310;
    processor.spectrum.setBounds(0, componentY, width,  componentHeight);
    processor.waveComponent.setBounds(0, componentY, width,  componentHeight);
    processor.outputComponent.setBounds(0, componentY, width,  componentHeight);
    processor.adsrComponent.setBounds(0, componentY, width,  componentHeight);
    processor.lfoComponent.setBounds(0, componentY, width,  componentHeight);
    processor.curveComponent.setBounds(0, componentY, width,  componentHeight);
    processor.showTableComponent.setBounds(0, componentY, width,  componentHeight);
    
    potsComponent.setBounds(0, 110, 830,  260);
    
    keysComponent->setBounds(0, height-90, width,  90);
    paramButtonComponent.setBounds(0, 50, width,  60);
    paramButtonComponent.potsComponent = &potsComponent;
    paramButtonComponent.setDials();
    
    viewMeterComponent.setBounds(840, 100, 260,  80);
   
    headerComponent.setBounds(0, 0, width,  50);
    performanceComponent.setBounds(0,50, width,  630);
    libraryComponent.setBounds(0,50, width,  630);
    arpComponent.setBounds(0,50, width,  630);
    setupComponent.setBounds(0,50, width,  630);
    rootComponent->setBounds(0,50, width,  630);
    debugComponent.setBounds(width-280,80, 270,  260);
}

// ==================================================================================================
// paint
// ==================================================================================================

inline const char * const BoolToString(bool b) {
  return b ? "true" : "false";
}

void Synth1AudioProcessorEditor::paint (Graphics& g) {
    // BG
    g.fillAll (C_BACKGROUND);
}

