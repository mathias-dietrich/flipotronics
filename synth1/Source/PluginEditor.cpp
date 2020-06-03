#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Const.h"
#include "WaveTable.h"
#include "Func.h"

//==============================================================================
Synth1AudioProcessorEditor::Synth1AudioProcessorEditor (Synth1AudioProcessor& p) : 
    AudioProcessorEditor (&p), processor (p),
    keyboardComponent (keyboardState, MidiKeyboardComponent::horizontalKeyboard)
{
    getLookAndFeel().setColour (Slider::thumbColourId, Colours::orange);
    addAndMakeVisible (keyboardComponent);
    setSize (1400, 780);
    keyboardState.addListener (this);
    
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
    
    addAndMakeVisible (timeLabel);
    timeLabel.setColour (Label::backgroundColourId, Colours::black);
    timeLabel.setColour (Label::textColourId, Colours::white);
    timeLabel.setJustificationType (Justification::centred);
    
    for(int i=0; i < 16; ++i){
        addAndMakeVisible (dials[i]);
        dials[i].setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag );
        dials[i].setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 100, 20);
        dials[i].setNumDecimalPlacesToDisplay(2);
        addAndMakeVisible (boxes[i]);
        boxes[i].setJustification(Justification::horizontallyCentred);
    }
    
    fileManager->load();
    setDials();
    
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
    
    btnRange0.setBounds (820,  5, 80,  20);
    btnRange1.setBounds (910,  5, 80,  20);
    btnRange2.setBounds (1000, 5, 80,  20);
    btnRange3.setBounds (1090, 5, 80,  20);
}


