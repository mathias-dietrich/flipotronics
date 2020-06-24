#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Const.h"
#include "WaveTable.h"
#include "Func.h"

//==============================================================================
Synth1AudioProcessorEditor::Synth1AudioProcessorEditor (Synth1AudioProcessor& p) : 
    AudioProcessorEditor (&p),
    keyboardComponent (keyboardState, MidiKeyboardComponent::horizontalKeyboard),
    processor (p)
{
    getLookAndFeel().setColour (Slider::thumbColourId, Colours::orange);
    addAndMakeVisible (keyboardComponent);
 
    keyboardState.addListener (this);
    patchCurrent = 0;
    viewModeSetting = 1;
    
    ImageFactory::of().init();
    
    curve.set(0);
    
    //fileManager = new FileManager();
    bankLoader = new BankLoader();
    bankLoader->load();
    processor.loadPatch(0);
    Model::of().set();
    compareMode = false;

    int from = 0;
    int to = 15;
    for(int i=0; i < 16; ++i){
        addAndMakeVisible (btnParam[i]);
        btnParam[i].setButtonText (toString(from) + " - " + toString(to));
        btnParam[i].addListener (this);
        btnParam[i].setRadioGroupId(i);
        btnParam[i].setToggleState(false, NotificationType::dontSendNotification);
        from += 16;
        to += 16;
    }
    for(int i=0; i < 8; ++i){
       addAndMakeVisible (btnLabel[i]);
       btnLabel[i].setColour (Label::textColourId, Colours::yellow);
       btnLabel[i].setJustificationType (Justification::centred);
       auto f2 =  btnLabel[i].getFont();
       f2.setSizeAndStyle(15, 0, 0.4, 0.4);
       btnLabel[i].setFont(f2);
    }
    
    for(int i=0; i < 4; ++i){
          addAndMakeVisible (rootLabel[i]);
          rootLabel[i].setColour (Label::textColourId, Colours::yellow);
          rootLabel[i].setJustificationType (Justification::centred);
          auto f2 =  btnLabel[i].getFont();
          f2.setSizeAndStyle(17, 0, 0.4, 0.4);
          rootLabel[i].setFont(f2);
    }
    rootLabel[0].setText("0 - 255", NotificationType::dontSendNotification);
    rootLabel[1].setText("256 - 511", NotificationType::dontSendNotification);
    rootLabel[2].setText("512 - 767", NotificationType::dontSendNotification);
    rootLabel[3].setText("768 - 1023", NotificationType::dontSendNotification);
    
    btnParam[0].setToggleState(true, NotificationType::dontSendNotification);
    
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
    
    btnRange0.setButtonText ("Synth");
    btnRange0.addListener (this);
    btnRange0.setRadioGroupId(18);
    btnRange0.setToggleState(true, NotificationType::dontSendNotification);
    addAndMakeVisible (btnRange0);
    
    btnRange1.setButtonText ("Wave");
    btnRange1.addListener (this);
    btnRange1.setRadioGroupId(19);
    addAndMakeVisible (btnRange1);
    
    btnRange2.setButtonText ("FX");
    btnRange2.addListener (this);
    btnRange2.setRadioGroupId(20);
    addAndMakeVisible (btnRange2);
    
    btnRange3.setButtonText ("Control");
    btnRange3.addListener (this);
    btnRange3.setRadioGroupId(21);
    addAndMakeVisible (btnRange3);
    
    btnProgUp.setButtonText (">");
    btnProgUp.addListener (this);
    btnProgUp.setRadioGroupId(22);
    addAndMakeVisible (btnProgUp);
    
    btnProgDown.setButtonText ("<");
    btnProgDown.addListener (this);
    btnProgDown.setRadioGroupId(23);
    addAndMakeVisible (btnProgDown);
    
    btnPanic.setButtonText ("Panic");
    btnPanic.addListener (this);
    btnPanic.setRadioGroupId(25);
    addAndMakeVisible (btnPanic);
    
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
    
    for(int i=0; i < 16; ++i){
        addAndMakeVisible (dials[i]);
        dials[i].setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag );
        dials[i].setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 100, 20);
        dials[i].setNumDecimalPlacesToDisplay(2);
        dials[i].setName(toString(i));
        dials[i].addListener (this);
        addAndMakeVisible (boxes[i]);
        boxes[i].setJustification(Justification::horizontallyCentred);
    }
    
    setDials();
    
    pitchWheel.setSliderStyle(Slider::SliderStyle::LinearVertical );
    pitchWheel.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 100, 20);
    pitchWheel.setNumDecimalPlacesToDisplay(2);
    pitchWheel.setName("100");
    pitchWheel.addListener (this);
    pitchWheel.setRange(-8192, 8192, 1);
    pitchWheel.setValue(0);
    addAndMakeVisible(pitchWheel);
    
    modWheel.setSliderStyle(Slider::SliderStyle::LinearVertical );
    modWheel.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 100, 20);
    modWheel.setNumDecimalPlacesToDisplay(2);
    modWheel.setName("101");
    modWheel.addListener (this);
    modWheel.setRange(0, 127,1);
    addAndMakeVisible(modWheel);
    
    expWheel.setSliderStyle(Slider::SliderStyle::LinearVertical );
    expWheel.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 100, 20);
    expWheel.setNumDecimalPlacesToDisplay(2);
    expWheel.setName("102");
    expWheel.addListener (this);
    expWheel.setRange(0, 127,1);
    addAndMakeVisible(expWheel);
    
    progName.setColour (Label::backgroundColourId, C_DARKGREY);
    progName.setColour (Label::textColourId, Colours::white);
    progName.setJustificationType (Justification::centred);
    progName.setText("Flipotronics", NotificationType::dontSendNotification);
    auto f2 =  progName.getFont();
    f2.setSizeAndStyle(50, 0, 0.5, 0.5);
    f2.setBold(true);
    progName.setFont(f2);
    addAndMakeVisible(progName);
   
   // progNumber.setColour (Label::backgroundColourId, C_DARKGREY);
    progNumber.setColour (Label::textColourId, Colours::white);
    progNumber.setJustificationType (Justification::centred);
    progNumber.setText("1", NotificationType::dontSendNotification);
    
    auto f =  progNumber.getFont();
    f.setSizeAndStyle(40, 0, 0.5, 0.5);
    f.setBold(true);
    progNumber.setFont(f);
    addAndMakeVisible(progNumber);
    
    // Dropdowns
    addAndMakeVisible(playMode);
    playMode.addItem ("Poly", 1);
    playMode.addItem ("Unisono", 2);
    playMode.addItem ("Mono", 3);
    playMode.addItem ("Legato", 4);
    playMode.onChange = [this] { styleMenuChanged(); };
    playMode.setSelectedId(par[1023], NotificationType::dontSendNotification);

    addAndMakeVisible(viewMode);
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
    viewMode.addItem ("Curve 4", vCurve);
    viewMode.addItem ("Wave", vWave);
    viewMode.addItem ("Debug", vDebug);
    viewMode.onChange = [this] { styleMenuChangedView(); };
    viewModeSetting = vWave;
    viewMode.setSelectedId(viewModeSetting, NotificationType::dontSendNotification);

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
    addChildComponent(processor.spectrum);
    addChildComponent(processor.outputComponent);
    addChildComponent(processor.adsrComponent);
    addAndMakeVisible(processor.waveComponent);
    addChildComponent(processor.lfoComponent);

    startTimer(1000 / SCOPEFRAMES);
    setSize (1400, 780);
}

Synth1AudioProcessorEditor::~Synth1AudioProcessorEditor(){
    delete bankLoader;
}



// ==================================================================================================
// Resize
// ==================================================================================================
void Synth1AudioProcessorEditor::resized()
{
    Rectangle<int> r = getLocalBounds();
    int width = r.getWidth();
    int height = r.getHeight();
    
    // Keyboard
    keyboardComponent.setBounds (100,  height - 50, 1200,  50);
    
    // Buttons
    for(int i=0; i < 8; ++i){
         btnParam[i].setBounds (10 + i * 100,  5 , 100,  20);
    }
    for(int i=0; i < 8; ++i){
        btnParam[i+8].setBounds (10 + i * 100,  25 , 100,  20);
    }
    for(int i=0; i < 8; ++i){
        btnLabel[i].setBounds (10 + i * 100, 43, 100, 18);;
    }
    
    int hButtons = 30;
    btnCompare.setBounds (width-270, hButtons, 80, 20);
    btnSave.setBounds (width-180, hButtons, 80, 20);
    btnLoad.setBounds (width-90, hButtons, 80, 20);
    
    int xVal = 835;
       btnRange0.setBounds (xVal, 5, 60, 20);
       btnRange1.setBounds (xVal+70, 5, 60, 20);
       btnRange2.setBounds (xVal+140, 5, 60, 20);
       btnRange3.setBounds (xVal+210, 5, 60, 20);
       
       rootLabel[0].setBounds (xVal, 25, 60, 20);
       rootLabel[1].setBounds (xVal+70, 25, 60, 20);
       rootLabel[2].setBounds (xVal+140, 25, 60, 20);
       rootLabel[3].setBounds (xVal+210, 25, 60, 20);
       
       btnProgDown.setBounds (840, 205, 80, 20);
       btnProgUp.setBounds (1020, 205, 80, 20);
       btnPanic.setBounds (1000, 290, 80, 20);
       btnBrowse.setBounds (922, 245, 90, 30);
       btnArp.setBounds (820, 245, 90, 30);
    
    // Sliders
    int dialY = 60;
    for(int i=0; i < 8; ++i){
         boxes[i].setBounds (10  + i * 100,  dialY, 100,  20);
         dials[i].setBounds (10  + i * 100,  dialY+20, 100,  100);
    }
   
    dialY += 130;
    
    for(int i=0; i < 8; ++i){
            boxes[i+8].setBounds (10  + i * 100,  dialY, 100,  20);
            dials[i+8].setBounds (10  + i * 100,  dialY+20, 100,  100);
    }
    
    // Live Controller
    pitchWheel.setBounds(1230, 60, 50, 250);
    modWheel.setBounds (1290, 60, 50, 250);
    expWheel.setBounds (1350, 60, 50, 250);
    
    // Drop Downs
    playMode.setBounds (820, 290, 80, 20);
    viewMode.setBounds (910, 290, 80, 20);
    viewZoom.setBounds (width-90, 0, 80, 20);
    
    // Labels
    progName.setBounds(840, 137, 260,  60);
    progNumber.setBounds(930, 205, 80,  30);
    
    // Spectrum
    processor.spectrum.setBounds(0, 320, width,  400);
    processor.waveComponent.setBounds(0, 320, width,  400);
    processor.outputComponent.setBounds(0, 320, width,  400);
    processor.adsrComponent.setBounds(0, 320, width,  400);
    processor.lfoComponent.setBounds(0, 320, width,  400);
}

// ==================================================================================================
// paint
// ==================================================================================================
void Synth1AudioProcessorEditor::paint (Graphics& g)
{
    Rectangle<int> r = getLocalBounds();
    int width = r.getWidth();
    int height = r.getHeight() ;
    int half = height / 2 + 120;
    
    // BG
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    // Version
    Rectangle<int> rv = getLocalBounds();
  
    rv.setWidth(rv.getWidth()-120);
    rv.setHeight(40);
    g.setColour (Colours::white);
    g.setFont (17.0f);
    g.drawFittedText (PRODUCTNAME, rv, Justification::topRight, 1);
    
    // Debug speed of render
    rv.setY(17);
    g.setFont (11.0f);
  
    // Time taken in the Render Loop
    float taken = timeTaken * 0.000001f;
    if(taken > processor.maxTimeMsec){
        g.setColour (Colours::red);
    }else{
        g.setColour (Colours::yellow);
    }
    g.drawFittedText (String(taken) + " - " + String(processor.maxTimeMsec), rv, Justification::topRight, 1);
    
    g.setColour (Colours::white);
    rv.setY(67);
    rv.setX(width-280);
    rv.setWidth(200);
    g.setFont (15.0f);
    g.drawFittedText ("Peak: " + String(sumPeak), rv, Justification::topLeft, 1);
    
    rv.setY(85);
    g.drawFittedText ("RMS: " + String(sumRMS,2), rv, Justification::topLeft, 1);
    
    // VU Meter
    g.setColour (Colours::black);
    r.setHeight(380);
    r.setY(315);
    g.fillRect(r);

    g.drawImageWithin(ImageFactory::of().png[eMeter], 840, 50, 120,80, juce::RectanglePlacement::stretchToFit, false);
    g.drawImageWithin(ImageFactory::of().png[eMeter], 980, 50, 120,80, juce::RectanglePlacement::stretchToFit, false);
    
    // Display Graph
    if(viewModeSetting == vCurve){
        curve.set(par[1022]);
        g.setColour (Colours::white);
        int ylast = half + 150;
        int w = 300; // width
        int xOffset = 500;
        for(int i=0;i<w;++i){
            int y = 150 + half - 300.0f * curve.getScaled(i , w) ;
             g.drawLine (xOffset + i, ylast, i + xOffset+1, y, 1.0f);
            ylast = y;
        }
    }
}
