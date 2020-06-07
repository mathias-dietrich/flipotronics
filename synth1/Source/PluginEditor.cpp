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
    setSize (1400, 780);
    keyboardState.addListener (this);
    patchCurrent = 0;
    viewModeSetting = 1;
    
    //fileManager = new FileManager();
    bankLoader = new BankLoader();
    bankLoader->load();
    processor.loadPatch(0);
    
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
    
    btnRange0.setButtonText ("Range 1");
    btnRange0.addListener (this);
    btnRange0.setRadioGroupId(18);
    btnRange0.setToggleState(true, NotificationType::dontSendNotification);
    addAndMakeVisible (btnRange0);
    
    btnRange1.setButtonText ("Range 2");
    btnRange1.addListener (this);
    btnRange1.setRadioGroupId(19);
    addAndMakeVisible (btnRange1);
    
    btnRange2.setButtonText ("Range 3");
    btnRange2.addListener (this);
    btnRange2.setRadioGroupId(20);
    addAndMakeVisible (btnRange2);
    
    btnRange3.setButtonText ("Range 4");
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
    
    modelOld = modelOld.copy();
    setDials();
    
    addAndMakeVisible(playMode);
    playMode.addItem ("Poly", 1);
    playMode.addItem ("Unisono", 2);
    playMode.addItem ("Mono", 3);
    playMode.addItem ("Legato", 4);
    playMode.onChange = [this] { styleMenuChanged(); };
    playMode.setSelectedId(par[1023]);
    
    addAndMakeVisible(viewMode);
    viewMode.addItem ("Wave", 1);
    viewMode.addItem ("Matrix", 2);
    viewMode.addItem ("Debug", 3);
    viewMode.onChange = [this] { styleMenuChangedView(); };
    viewMode.setSelectedId(1);
    
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
    
    graphZoom.setSliderStyle(Slider::SliderStyle::LinearHorizontal );
    graphZoom.setName("103");
    graphZoom.addListener (this);
    graphZoom.setRange(5, 4000,1);
    graphZoom.setValue(zoom);
    addAndMakeVisible(graphZoom);
    
    graphZoomY.setSliderStyle(Slider::SliderStyle::LinearVertical );
    graphZoomY.setName("104");
    graphZoomY.addListener (this);
    graphZoomY.setRange(0.5, 4,0.01);
    graphZoomY.setValue(zoomY);
    graphZoomY.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(graphZoomY);
    
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
    
    // Plot
    Rectangle<int> r = getLocalBounds();

    WaveTable *w = new WaveTable();
    w->init(samplerate, samplesperblock);
    int sr = OVERSAMPLING * samplerate;
    float pos = 0;
    for(int i= 0; i < sr;++i){
        pos += 440  ;
        if(pos >= sr){
            pos -= sr;
        }
        int p = pos;
        scopeBuffer[i] = w->sinBuffer[p];
    }
    delete w;
    
    startTimer(1000 / SCOPEFRAMES);
}

Synth1AudioProcessorEditor::~Synth1AudioProcessorEditor(){
    delete bankLoader;
}

//==============================================================================
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
  
    rv.setWidth(rv.getWidth()-15);
    rv.setHeight(40);
    g.setColour (Colours::white);
    g.setFont (19.0f);
    g.drawFittedText (PRODUCTNAME, rv, Justification::topRight, 1);
    
    g.setColour (Colours::black);
    r.setHeight(380);
    r.setY(315);
    g.fillRect(r);

    g.drawImageWithin(vumeter, 840, 40, 120,80, juce::RectanglePlacement::stretchToFit, false);
    g.drawImageWithin(vumeter, 980, 40, 120,80, juce::RectanglePlacement::stretchToFit, false);

    if(viewModeSetting !=1){
        return;
    }
    
    // Plot
    g.setColour (Colours::white);
    g.drawLine (0, half, width, half, 0.5f);

    g.setColour (Colours::red);
    drawPlot( g, half, width, scopeBuffer );
}

void Synth1AudioProcessorEditor::resized()
{
    Rectangle<int> r = getLocalBounds();
    int width = r.getWidth();
    
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
     keyboardComponent.setBounds (0,  getHeight() - 50, getWidth(),  50);
    
    //timeLabel.setBounds (0,  0, 100,  20);
    for(int i=0; i < 8; ++i){
         btnParam[i].setBounds (10 + i * 100,  5 , 100,  20);
    }
    for(int i=0; i < 8; ++i){
        btnParam[i+8].setBounds (10 + i * 100,  25 , 100,  20);
    }
    
    btnCompare.setBounds (width-270, 30, 80, 20);
    btnSave.setBounds (width-180, 30, 80, 20);
    btnLoad.setBounds (width-90, 30, 80, 20);
    
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
    
    graphZoom.setBounds (0 ,  700, width-10,  20);
    graphZoomY.setBounds (0 ,  312, 20,  385);
    
    // Range Buttons
    btnRange0.setBounds (820, 5, 80, 20);
    btnRange1.setBounds (910, 5, 80, 20);
    btnRange2.setBounds (1000, 5, 80, 20);
    btnRange3.setBounds (1090, 5, 80, 20);
    
    btnProgDown.setBounds (840, 250, 80, 20);
    btnProgUp.setBounds (1020, 250, 80, 20);
    btnPanic.setBounds (1000, 290, 80, 20);
    btnBrowse.setBounds (922, 205, 90, 30);
    
    // Play Mode
    playMode.setBounds (820, 290, 80, 20);
    viewMode.setBounds (910, 290, 80, 20);
    
    // Live Controller
    pitchWheel.setBounds(1100, 60, 80, 250);
    modWheel.setBounds (1200, 60, 80, 250);
    expWheel.setBounds (1300, 60, 80, 250);
    
    // Lable
    progName.setBounds(840, 137, 260,  60);
    progNumber.setBounds(930, 245, 80,  30);
}


