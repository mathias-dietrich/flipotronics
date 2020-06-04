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
    
    viewModeSetting = 1;
    
    fileManager = new FileManager();
    
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
    btnPanic.setRadioGroupId(24);
    addAndMakeVisible (btnPanic);
    
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
    
    fileManager->load();
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
    pitchWheel.setRange(0, 16384, 1);
    pitchWheel.setValue(8192);
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
    
    progName.setColour (Label::backgroundColourId, Colours::darkgreen);
    progName.setColour (Label::textColourId, Colours::white);
    progName.setJustificationType (Justification::centred);
    progName.setText("Flipotronics", NotificationType::dontSendNotification);
    auto f2 =  progName.getFont();
    f2.setSizeAndStyle(50, 0, 0.5, 0.5);
    f2.setBold(true);
    progName.setFont(f2);
    addAndMakeVisible(progName);
   
    progNumber.setColour (Label::backgroundColourId, Colours::darkgreen);
    progNumber.setColour (Label::textColourId, Colours::white);
    progNumber.setJustificationType (Justification::centred);
    progNumber.setText("1", NotificationType::dontSendNotification);
    auto f =  progNumber.getFont();
    f.setSizeAndStyle(40, 0, 0.5, 0.5);
    f.setBold(true);
    progNumber.setFont(f);
    addAndMakeVisible(progNumber);
}

Synth1AudioProcessorEditor::~Synth1AudioProcessorEditor()
{
    delete fileManager;
}

//==============================================================================
void Synth1AudioProcessorEditor::paint (Graphics& g)
{
    Rectangle<int> r = getLocalBounds();
    int width = r.getWidth();
    int height = r.getHeight() ;
    int half = height / 2 + 128;
    
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
    r.setHeight(410);
    r.setY(315);
    g.fillRect(r);

    rv.setX(840);
    rv.setY(50);
    rv.setWidth(120);
    rv.setHeight(80);
    g.setColour (Colours::lightyellow);
    g.fillRect(rv);
    
    rv.setX(980);
    rv.setY(50);
    rv.setWidth(120);
    rv.setHeight(80);
    g.setColour (Colours::lightyellow);
    g.fillRect(rv);

    
    if(viewModeSetting !=1){
        return;
    }
    
    // Plot
    g.setColour (Colours::white);
    g.drawLine (0, half, width, half, 0.5f);
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
    
    btnSave.setBounds (width-220,  25 , 100,  20);
    btnLoad.setBounds (width-110,  25 , 100,  20);
    
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
    
    // Range Buttons
    btnRange0.setBounds (820,  5, 80,  20);
    btnRange1.setBounds (910,  5, 80,  20);
    btnRange2.setBounds (1000, 5, 80,  20);
    btnRange3.setBounds (1090, 5, 80,  20);
    
    
    btnProgDown.setBounds (840, 265, 80,  20);
    btnProgUp.setBounds (1020, 265, 80,  20);
    btnPanic.setBounds (1000, 290, 80,  20);
    
    // Play Mode
    playMode.setBounds (820, 290, 80,  20);
    viewMode.setBounds (910, 290, 80,  20);
    
    // Live Controller
    pitchWheel.setBounds(1100, 60, 80,  250);
    modWheel.setBounds (1200, 60, 80,  250);
    expWheel.setBounds (1300, 60, 80,  250);
    
    // Lable
    progName.setBounds(840, 140, 260,  60);
    progNumber.setBounds(840, 200, 260,  60);
    
    
   
   
}


