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
    bankLoader = new BankLoader();
    bankLoader->load();
    processor.loadPatch(0);
    Model::of().set();
    Model::of().compareMode = false;
    
    btnCompare.setButtonText ("Compare");
    btnCompare.addListener (this);
    btnCompare.setRadioGroupId(24);
    addAndMakeVisible (btnCompare);
    
    btnSave.setButtonText ("Save");
    btnSave.addListener (this);
    btnSave.setRadioGroupId(16);
    addAndMakeVisible (btnSave);
    
    btnLoad.setButtonText ("Load");
    btnLoad.addListener (this);
    btnLoad.setRadioGroupId(17);
    addAndMakeVisible (btnLoad);
    
    btnProgUp.setButtonText (">");
    btnProgUp.addListener (this);
    btnProgUp.setRadioGroupId(22);
    addAndMakeVisible (btnProgUp);
    
    btnProgDown.setButtonText ("<");
    btnProgDown.addListener (this);
    btnProgDown.setRadioGroupId(23);
    addAndMakeVisible (btnProgDown);
    
    btnBrowse.setButtonText ("Browse");
    btnBrowse.addListener (this);
    btnBrowse.setRadioGroupId(26);
    addAndMakeVisible (btnBrowse);
    
    btnArp.setButtonText ("Arp");
    btnArp.addListener (this);
    btnArp.setRadioGroupId(27);
    addAndMakeVisible (btnArp);
    
    addAndMakeVisible (timeLabel);
    timeLabel.setColour (Label::backgroundColourId, Colours::black);
    timeLabel.setColour (Label::textColourId, Colours::white);
    timeLabel.setJustificationType (Justification::centred);
    
    setDials();
    
    progName.setColour (Label::textColourId, Colours::white);
    progName.setJustificationType (Justification::centred);
    progName.setText("Flipotronics", NotificationType::dontSendNotification);

    auto f2 =  progName.getFont();
    f2.setSizeAndStyle(50, 0, 0.5, 0.5);
    f2.setBold(true);
    progName.setFont(f2);
    addAndMakeVisible(progName);
   
    progNumber.setColour (Label::textColourId, C_PROGNUMBER);
    progNumber.setJustificationType (Justification::centred);
    progNumber.setText("1", NotificationType::dontSendNotification);
    
    auto f =  progNumber.getFont();
    f.setSizeAndStyle(40, 0, 0.5, 0.5);
    f.setBold(true);
    progNumber.setFont(f);
    addAndMakeVisible(progNumber);
    
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
}

Synth1AudioProcessorEditor::~Synth1AudioProcessorEditor(){
    ImageFactory::of().close();
    delete bankLoader;
    delete keysComponent;
}

// ==================================================================================================
// Resize
// ==================================================================================================
void Synth1AudioProcessorEditor::resized() {
    Rectangle<int> r = getLocalBounds();
    int width = r.getWidth();
    int height = r.getHeight();
    
    int hButtons = 80;
    btnCompare.setBounds (width-270, hButtons, 80, 20);
    btnSave.setBounds (width-180, hButtons, 80, 20);
    btnLoad.setBounds (width-90, hButtons, 80, 20);
   
    btnProgDown.setBounds (840, 255, 80, 20);
    btnProgUp.setBounds (1020, 255, 80, 20);
    btnBrowse.setBounds (922, 295, 90, 30);
    btnArp.setBounds (820, 295, 90, 30);
    
    // Drop Downs
    viewMode.setBounds (840, 3400, 120, 20);
    viewZoom.setBounds (width-90, 55, 80, 20);
    
    // Labels
    progName.setBounds(840, 187, 260,  60);
    progNumber.setBounds(930, 255, 80,  30);

    
    // Spectrum
    int componentY = 370;
    int componentHeight = 310;
    processor.spectrum.setBounds(0, componentY, width,  componentHeight);
    processor.waveComponent.setBounds(0, componentY, width,  componentHeight);
    processor.outputComponent.setBounds(0, componentY, width,  componentHeight);
    processor.adsrComponent.setBounds(0, componentY, width,  componentHeight);
    processor.lfoComponent.setBounds(0, componentY, width,  componentHeight);
    processor.curveComponent.setBounds(0, componentY, width,  componentHeight);
    
    potsComponent.setBounds(0, 110, 830,  250);
    keysComponent->setBounds(0, height-90, width,  90);
    paramButtonComponent.setBounds(0, 50, 1230,  250);
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
    
    // Progname
    g.setColour (C_PROGNAME);
    g.fillRoundedRectangle(840, 187, 260,  60, 7);
}

