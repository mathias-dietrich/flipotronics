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
    
    curve.set(0);
    
    //fileManager = new FileManager();
    bankLoader = new BankLoader();
    bankLoader->load();
    processor.loadPatch(0);
    undoModel.set();
    compareMode = false;
    
    
    adsr1.uid = -1;
    adsr2.uid = -1;
    adsr3.uid = -1;
    adsr4.uid = -1;
    
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
    
    addAndMakeVisible(playMode);
    playMode.addItem ("Poly", 1);
    playMode.addItem ("Unisono", 2);
    playMode.addItem ("Mono", 3);
    playMode.addItem ("Legato", 4);
    playMode.onChange = [this] { styleMenuChanged(); };
    playMode.setSelectedId(par[1023], NotificationType::dontSendNotification);
    
    addAndMakeVisible(viewMode);
    viewMode.addItem ("Ouput", 1);
    viewMode.addItem ("ADSR 1", 2);
    viewMode.addItem ("ADSR 2", 3);
    viewMode.addItem ("ADSR 3", 4);
    viewMode.addItem ("ADSR 4", 5);
    viewMode.addItem ("LFO 1", 6);
    viewMode.addItem ("LFO 2", 7);
    viewMode.addItem ("LFO 3", 8);
    viewMode.addItem ("LFO 4", 9);
    viewMode.addItem ("Curve 4", 10);
    viewMode.addItem ("Matrix", 11);
    viewMode.addItem ("Debug", 12);
    viewMode.onChange = [this] { styleMenuChangedView(); };
    viewModeSetting = 2;
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
    
    setSize (1400, 780);
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
  
    rv.setWidth(rv.getWidth()-120);
    rv.setHeight(40);
    g.setColour (Colours::white);
    g.setFont (17.0f);
    g.drawFittedText (PRODUCTNAME, rv, Justification::topRight, 1);
    
    g.setColour (Colours::black);
    r.setHeight(380);
    r.setY(315);
    g.fillRect(r);

    g.drawImageWithin(vumeter, 840, 50, 120,80, juce::RectanglePlacement::stretchToFit, false);
    g.drawImageWithin(vumeter, 980, 50, 120,80, juce::RectanglePlacement::stretchToFit, false);

    switch(viewModeSetting){
        case 1:
            // Plot
            g.setColour (Colours::white);
            g.drawLine (0, half, width, half, 0.5f);

            g.setColour (Colours::red);
            drawPlot( g, half, width, scopeBuffer );
            break;
            
        case 2: //ADSR 1
        {
            adsr1.init(samplerate,  samplesperblock);
            adsr1.delayTimeMsec = par[P_ADSR1_DELAY];
            adsr1.attackTimeMsec = par[P_ADSR1_ATTACK];
            adsr1.holdTimeMsec = par[P_ADSR1_HOLD];
            adsr1.decayTimeMsec = par[P_ADSR1_DECAY];
            adsr1.sustainLevel = par[P_ADSR1_SUSTAIN];
            adsr1.releaseTimeMsec = par[P_ADSR1_RELEASE];
            
            // Curves
            adsr1.setAttackCurve( par[P_ADSR1_ATTACK_CURVE]);
            adsr1.setDecayCurve( par[P_ADSR1_DECAY_CURVE]);
            adsr1.setSustainCurve( par[P_ADSR1_SUSTAIN_CURVE]);
            adsr1.setReleaseCurve( par[P_ADSR1_RELEASE_CURVE]);
            drawAdsr(&adsr1, g,  width,  half);
            break;
        }

        case 3: //ADSR 2
        {
            adsr2.init(samplerate,  samplesperblock);
            adsr2.delayTimeMsec = par[P_ADSR2_DELAY];
            adsr2.attackTimeMsec = par[P_ADSR2_ATTACK];
            adsr2.holdTimeMsec = par[P_ADSR2_HOLD];
            adsr2.decayTimeMsec = par[P_ADSR2_DECAY];
            adsr2.sustainLevel = par[P_ADSR2_SUSTAIN];
            adsr2.releaseTimeMsec = par[P_ADSR2_RELEASE];
            
            // Curves
            adsr2.setAttackCurve( par[P_ADSR2_ATTACK_CURVE]);
            adsr2.setDecayCurve( par[P_ADSR2_DECAY_CURVE]);
            adsr2.setSustainCurve( par[P_ADSR2_SUSTAIN_CURVE]);
            adsr2.setReleaseCurve( par[P_ADSR2_RELEASE_CURVE]);
            drawAdsr(&adsr2, g,  width,  half);
            break;
        }
        
        case 4: //ADSR 3
        {
            adsr3.init(samplerate,  samplesperblock);
            adsr3.delayTimeMsec = par[P_ADSR3_DELAY];
            adsr3.attackTimeMsec = par[P_ADSR3_ATTACK];
            adsr3.holdTimeMsec = par[P_ADSR3_HOLD];
            adsr3.decayTimeMsec = par[P_ADSR3_DECAY];
            adsr3.sustainLevel = par[P_ADSR3_SUSTAIN];
            adsr3.releaseTimeMsec = par[P_ADSR3_RELEASE];
            
            // Curves
            adsr3.setAttackCurve( par[P_ADSR3_ATTACK_CURVE]);
            adsr3.setDecayCurve( par[P_ADSR3_DECAY_CURVE]);
            adsr3.setSustainCurve( par[P_ADSR3_SUSTAIN_CURVE]);
            adsr3.setReleaseCurve( par[P_ADSR3_RELEASE_CURVE]);
            drawAdsr(&adsr3, g,  width,  half);
            break;
        }
        
        case 5: //ADSR 4
        {
            adsr4.init(samplerate,  samplesperblock);
            adsr4.delayTimeMsec = par[P_ADSR4_DELAY];
            adsr4.attackTimeMsec = par[P_ADSR4_ATTACK];
            adsr4.holdTimeMsec = par[P_ADSR4_HOLD];
            adsr4.decayTimeMsec = par[P_ADSR4_DECAY];
            adsr4.sustainLevel = par[P_ADSR4_SUSTAIN];
            adsr4.releaseTimeMsec = par[P_ADSR4_RELEASE];
            
            // Curves
            adsr4.setAttackCurve( par[P_ADSR4_ATTACK_CURVE]);
            adsr4.setDecayCurve( par[P_ADSR4_DECAY_CURVE]);
            adsr4.setSustainCurve( par[P_ADSR4_SUSTAIN_CURVE]);
            adsr4.setReleaseCurve( par[P_ADSR4_RELEASE_CURVE]);
            drawAdsr(&adsr4, g,  width,  half);
            break;
        }
            
        case 6:  // LFO 1
        {
            break;
        }
            
        case 7:  // LFO 2
        {
            break;
        }
        
        case 8:  // LFO 3
        {
            break;
        }
        
        case 9:  // LFO 4
        {
            break;
        }
            
        case 10:
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
            break;
    }
}

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
    
    graphZoom.setBounds (0 ,  700, width-10,  20);
    graphZoomY.setBounds (0 ,  312, 20,  385);
    
    // Live Controller
    pitchWheel.setBounds(1100, 60, 80, 250);
    modWheel.setBounds (1200, 60, 80, 250);
    expWheel.setBounds (1300, 60, 80, 250);
    
   
    // Drop Downs
    playMode.setBounds (820, 290, 80, 20);
    viewMode.setBounds (910, 290, 80, 20);
    viewZoom.setBounds (width-90, 0, 80, 20);
    
    // Labels
    progName.setBounds(840, 137, 260,  60);
    progNumber.setBounds(930, 205, 80,  30);
}


