#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "SynthAudioSource.h"
#include "Func.h"
#include "Model.h"
#include "FileManager.h"
#include "BankLoader.h"
#include "img.h"
#include "Color.h"
#include "Curve.h"
#include "SpectrumComponent.h"

//==============================================================================
/**
*/
class Synth1AudioProcessorEditor  : public AudioProcessorEditor,MidiKeyboardStateListener,
    public Button::Listener,  public Slider::Listener,public Timer
{
public:
    Synth1AudioProcessorEditor (Synth1AudioProcessor&);
    ~Synth1AudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    float zoom =440;
    float zoomY = 1;
    
    MidiKeyboardState keyboardState;
    MidiKeyboardComponent keyboardComponent;
    
    Curve curve;
    Adsr adsr1;
    Adsr adsr2;
    Adsr adsr3;
    Adsr adsr4;
    
    TextButton btnParam[16];
    Label btnLabel[8];
    Label rootLabel[4];
    TextButton btnSave;
    TextButton btnLoad;
    TextButton btnCompare;
    
    TextButton btnRange0;
    TextButton btnRange1;
    TextButton btnRange2;
    TextButton btnRange3;
    
    TextButton btnProgUp;
    TextButton btnProgDown;
    TextButton btnPanic;
    TextButton btnBrowse;
    TextButton btnArp;
    
    Label timeLabel;
    
    TextEditor boxes[16];
    Slider dials[16] ;
    
    BankLoader *bankLoader;
    
    int paramRange = 0;
    int paramRoot = 0;
    
    ComboBox playMode;
    ComboBox viewMode;
    ComboBox viewZoom;
    
    Slider pitchWheel;
    Slider modWheel;
    Slider expWheel;
    
    Slider graphZoom;
    Slider graphZoomY;
    
    Label progName;
    Label progNumber;
    
    Model undoModel;
    
    int maxTime;

private:
    Synth1AudioProcessor& processor;
    Image vumeter = ImageCache::getFromMemory (img::meter_png, img::meter_pngSize);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Synth1AudioProcessorEditor)
    
    void drawPlot(Graphics& g, int half, int width, std::atomic<float> * buf ){
        
        // search positive zero crossing
        int offset =0;
        while(buf[offset] > 0){
            ++offset;
        }
        
        while(offset < width){
            if(buf[offset] <0 && buf[offset+1] >=0){
                break;
            }
            ++offset;
        }
        
        int lastX = 0;
        int lastY = half;
        int sr = samplerate * OVERSAMPLING;
        
        for(int i=0; i< width;++i){
            int p = offset + i;
          
            int pos = p  * sr / zoom  / width;
            if(pos >= width){
                pos -= width;
            }
            
            float a = tanh(3.0f * buf[pos]);
            int v = half - a * 180 * zoomY;
             g.drawLine (lastX, lastY, i, v, 1.0f);
            lastX = i;
            lastY = v;
        }
    }
    
    void handleNoteOn (MidiKeyboardState* state, int midiChannel, int midiNoteNumber, float velocity) override
    {
        processor.handleNoteOn(state, midiChannel, midiNoteNumber, velocity);
    }
     
    void handleNoteOff (MidiKeyboardState* state, int midiChannel, int midiNoteNumber, float velocity) override
    {
        processor.handleNoteOff(state, midiChannel, midiNoteNumber, velocity);
    }
    
    void buttonClicked (Button* button)  override // [2]
    {
        // Save
        if(button->getRadioGroupId()==16) {
            bankLoader->save();
            undoModel.set();
            compareMode = false;
            setDials();
           return;
        }
        
        // Load
        if(button->getRadioGroupId()==17) {
            bankLoader->load();
            processor.loadPatch(patchCurrent);
            undoModel.set();
            compareMode = false;
            setDials();
            return;
        }
        
         if(button->getRadioGroupId()==18) {
             paramRoot = 0;
             btnRange0.setToggleState(true, NotificationType::dontSendNotification);
             btnRange1.setToggleState(false, NotificationType::dontSendNotification);
             btnRange2.setToggleState(false, NotificationType::dontSendNotification);
             btnRange3.setToggleState(false, NotificationType::dontSendNotification);
             setButtonRanges();
             return;
         }
        
        if(button->getRadioGroupId()==19) {
            paramRoot = 1;
            btnRange0.setToggleState(false, NotificationType::dontSendNotification);
            btnRange1.setToggleState(true, NotificationType::dontSendNotification);
            btnRange2.setToggleState(false, NotificationType::dontSendNotification);
            btnRange3.setToggleState(false, NotificationType::dontSendNotification);
            setButtonRanges();
            return;
        }
        
        if(button->getRadioGroupId()==20) {
            paramRoot = 2;
            btnRange0.setToggleState(false, NotificationType::dontSendNotification);
            btnRange1.setToggleState(false, NotificationType::dontSendNotification);
            btnRange2.setToggleState(true, NotificationType::dontSendNotification);
            btnRange3.setToggleState(false, NotificationType::dontSendNotification);
            setButtonRanges();
            return;
        }
        
        if(button->getRadioGroupId()==21) {
            paramRoot = 3;
            btnRange0.setToggleState(false, NotificationType::dontSendNotification);
            btnRange1.setToggleState(false, NotificationType::dontSendNotification);
            btnRange2.setToggleState(false, NotificationType::dontSendNotification);
            btnRange3.setToggleState(true, NotificationType::dontSendNotification);
            setButtonRanges();
            return;
        }
        
        // Progr Up
        if(button->getRadioGroupId()==22) {
            patchCurrent++;
            if(patchCurrent >=127){
                patchCurrent = 0;
            }
            processor.loadPatch(patchCurrent);
            compareMode = false;
            undoModel.set();
            setDials();
            return;
        }
        
        // Progr Down
        if(button->getRadioGroupId()==23) {
            patchCurrent--;
            if(patchCurrent < 0){
               patchCurrent = 127;
            }
            
            processor.loadPatch(patchCurrent);
            compareMode = false;
            undoModel.set();
            
            setDials();
            return;
        }
        
        // Compare
        if(button->getRadioGroupId()==24) {
            compareMode = !compareMode;
            undoModel.swap();
            setDials();
            return;
        }
        
        // Panic
        if(button->getRadioGroupId()==25) {
            processor.panic();
            return;
        }
        
        // Browse
        if(button->getRadioGroupId()==26) {
            processor.browse();
            return;
        }
        
        // ARP
        if(button->getRadioGroupId()==27) {
            if(processor.isArpOn){
                btnArp.setButtonText ("Arp");
                btnArp.setToggleState(false, NotificationType::dontSendNotification);
                processor.isArpOn = false;
                processor.panic();
            }else{
                btnArp.setButtonText ("Arp");
                btnArp.setToggleState(true, NotificationType::dontSendNotification);
                processor.isArpOn = true;
            }
            processor.setArp(processor.isArpOn);
            return;
        }
        paramRange = button->getRadioGroupId();
        setDials();
    }
    
    void setDials(){
        for(int i=0; i < 16; ++i){
            int pid = paramRoot * 256 + paramRange * 16 + i;
            dials[i].setRange(params[pid].minVal,params[pid].maxVal,params[pid].stepVal);
            boxes[i].setText(params[pid].name);
            if( params[pid].type == uWaveType){
                dials[i].setTextValueSuffix(" " + getWaveType(E_WaveType(int(par[pid]))));
                dials[i].setValue(par[pid], dontSendNotification);
            }else if( params[pid].type == uFilterType){
                   dials[i].setTextValueSuffix(" " + getFilterTypeString(MultiModeLadderFilterTypes(int(par[pid]))));
                   dials[i].setValue(par[pid], dontSendNotification);
             }
            
            
            else if( params[pid].type == uPhase){
                dials[i].setTextValueSuffix(" degrees");
                dials[i].setValue(par[pid], dontSendNotification);
            }
            else if( params[pid].type == uTimeMsec){
                dials[i].setTextValueSuffix(" msec");
                dials[i].setSkewFactor(0.5);
                dials[i].setValue(par[pid], dontSendNotification);
            }
            else if( params[pid].type == uDb){
                dials[i].setSkewFactor (6);
                dials[i].setTextValueSuffix(" dB");
                dials[i].setValue(par[pid], dontSendNotification);
            }
            else if( params[pid].type == uHZ){
                dials[i].setSkewFactor (0.3);
                dials[i].setTextValueSuffix(" Hz");
                dials[i].setValue(par[pid], dontSendNotification);
            }
            else if( params[pid].type == uBool){
                bool test = par[pid];
                String text = test ? " on" : " off" ;
                dials[i].setTextValueSuffix(text);
            }
            else if( params[pid].type == uCurve){
                dials[i].setSkewFactor(1);
                dials[i].setTextValueSuffix(" %");
                dials[i].setValue(par[pid], dontSendNotification);
            }
            else if( params[pid].type == uMidiNote){
               dials[i].setTextValueSuffix(" " + midiNote(par[pid]));
               dials[i].setValue(par[pid], dontSendNotification);
            }
            else if( params[pid].type == uDevision){
               dials[i].setTextValueSuffix(" " + devision(par[pid]));
               dials[i].setValue(par[pid], dontSendNotification);
            }
            else if( params[pid].type == uArpMode){
                dials[i].setSkewFactor(1);
                if(par[pid]==0){
                     dials[i].setTextValueSuffix(" SEQ");
                }else if (par[pid]==1){
                     dials[i].setTextValueSuffix(" ARP");
                }else{
                    dials[i].setTextValueSuffix(" CHORD");
                }
                dials[i].setValue(par[pid], dontSendNotification);
            }
            else if( params[pid].type == uChordMode){
                switch(((int)par[pid])){
                    case 0:
                     dials[i].setTextValueSuffix(" Singe ");
                    break;
                    
                    case 1:
                     dials[i].setTextValueSuffix(" Quinte ");
                    break;
                        
                    case 2:
                     dials[i].setTextValueSuffix(" Quarte ");
                    break;
                    
                    case 3:
                     dials[i].setTextValueSuffix(" Root ");
                    break;
                        
                    case 4:
                     dials[i].setTextValueSuffix(" Inv 1 ");
                    break;
                    
                    case 5:
                     dials[i].setTextValueSuffix(" Inv 2 ");
                    break;
                }
               dials[i].setValue(par[pid], dontSendNotification);
            }
            else{
                dials[i].setTextValueSuffix("");
                dials[i].setValue(par[pid], dontSendNotification);
            }
        }
        // Param Select
        for(int i=0; i < 16; ++i){
            btnParam[i].setToggleState(false, NotificationType::dontSendNotification);
        }
        if(paramRange<16){
            btnParam[paramRange].setToggleState(true, NotificationType::dontSendNotification);
        }
        progNumber.setText(toString(patchCurrent+1), NotificationType::dontSendNotification);
        progName.setText(patchNameCurrent, NotificationType::dontSendNotification);
        btnCompare.setToggleState(compareMode, NotificationType::dontSendNotification);
        
        switch(paramRoot){
            case 0:
                btnLabel[0].setText("Master", NotificationType::dontSendNotification);
                btnLabel[1].setText("Osci", NotificationType::dontSendNotification);
                btnLabel[2].setText("Filter", NotificationType::dontSendNotification);
                btnLabel[3].setText("Adsr 1", NotificationType::dontSendNotification);
                btnLabel[4].setText("Adsr 3", NotificationType::dontSendNotification);
                btnLabel[5].setText("LFO", NotificationType::dontSendNotification);
                btnLabel[6].setText("", NotificationType::dontSendNotification);
                btnLabel[7].setText("", NotificationType::dontSendNotification);
                break;
                
            case 1:
                btnLabel[0].setText("", NotificationType::dontSendNotification);
                btnLabel[1].setText("", NotificationType::dontSendNotification);
                btnLabel[2].setText("", NotificationType::dontSendNotification);
                btnLabel[3].setText("", NotificationType::dontSendNotification);
                btnLabel[4].setText("", NotificationType::dontSendNotification);
                btnLabel[5].setText("", NotificationType::dontSendNotification);
                btnLabel[6].setText("", NotificationType::dontSendNotification);
                btnLabel[7].setText("", NotificationType::dontSendNotification);
                break;
                
            case 2:
                btnLabel[0].setText("", NotificationType::dontSendNotification);
                btnLabel[1].setText("", NotificationType::dontSendNotification);
                btnLabel[2].setText("", NotificationType::dontSendNotification);
                btnLabel[3].setText("", NotificationType::dontSendNotification);
                btnLabel[4].setText("", NotificationType::dontSendNotification);
                btnLabel[5].setText("", NotificationType::dontSendNotification);
                btnLabel[6].setText("", NotificationType::dontSendNotification);
                btnLabel[7].setText("", NotificationType::dontSendNotification);
                break;
                
            case 3:
                btnLabel[0].setText("", NotificationType::dontSendNotification);
                btnLabel[1].setText("", NotificationType::dontSendNotification);
                btnLabel[2].setText("", NotificationType::dontSendNotification);
                btnLabel[3].setText("", NotificationType::dontSendNotification);
                btnLabel[4].setText("", NotificationType::dontSendNotification);
                btnLabel[5].setText("", NotificationType::dontSendNotification);
                btnLabel[6].setText("", NotificationType::dontSendNotification);
                btnLabel[7].setText("", NotificationType::dontSendNotification);
                break;
        }
        btnArp.setToggleState(processor.isArpOn, NotificationType::dontSendNotification);
        isUpdateParams = true;
    }
    
    void sliderValueChanged(Slider *  slider) override {
        int sid = slider->getName().getIntValue();
        
        // Performances
        
        // Pitch Wheel
        if(sid==100){
            return;
        }
        
        // Mod Wheel
        if(sid==101){
            return;
        }
        
        // Exp Wheel
        if(sid==102){
            return;
        }
        
        // Zoom
        if(sid==103){
            zoom = slider->getValue();
            return;
        }
        // Zoom Y
        if(sid==104){
            zoomY = slider->getValue();
            return;
        }
        
        // Edits Mode ================================================================
        startEdit();
        int pid = paramRoot * 256 + paramRange * 16 + sid;
        if(params[pid].smoothTime > 0){
            parTargetDelta[pid] = par[pid] - slider->getValue();
        }else{
            par[pid] = slider->getValue();
        }
        setDials();
    }
    
    void setButtonRanges(){
        int from = 0;
        int to = 15;
        for(int i=0; i < 16; ++i){
            btnParam[i].setButtonText (toString(paramRoot * 256  + paramRange * 16 + from) + " - " + toString(paramRoot * 256 + paramRange * 16 + to));
            from += 16;
            to += 16;
        }
       setDials();
    }
    
    void styleMenuChanged(){
        switch (playMode.getSelectedId())
        {
            case 1: // Poly
                par[1023] = 1;
                break;
            case 2: // Unisono
                par[1023] = 2;
                break;
            case 3: // Mono
                par[1023] = 3;
                break;
            case 4: // Legato
                par[1023] = 4;
                break;
        }
        setDials();
    }
    
    void styleMenuChangedView(){
        viewModeSetting = viewMode.getSelectedId();
        if(viewModeSetting==2){
            processor.spectrum.setVisible(true);
        }else{
            processor.spectrum.setVisible(false);
        }
        repaint();
    }
          
    void styleMenuChangedViewZoom()
    {
        int ws = 1400;
        int hs = 780;
        float p = 1.0f;
        Desktop::getInstance().setGlobalScaleFactor(1);
        switch (viewZoom.getSelectedId())
        {
            case 1: // 50
                p = 0.5f;
                break;
            case 2: // 75
                p = 0.75f;
                break;
            case 3: // 100
                p = 1.0f;
                break;
            case 4: // 125
                p = 1.25f;
                break;
            case 5: // 150
                p = 1.5f;
                break;
                
            case 6: // 200
                p = 2.0f;
                break;
        }
        setSize (ws * p, hs * p);
        Desktop::getInstance().setGlobalScaleFactor((float)this->getWidth() / ws);
        repaint();
    }
    
    void sliderDragEnded(Slider *) override{
        pitchWheel.setValue(0);
    }
    
    void timerCallback() override{
        repaint();
        setDials();
    }
    
    void startEdit(){
        compareMode = true;
    }
    
    void drawAdsr(Adsr * adsr, Graphics& g, int width, int half){

       adsr->start();
       
       float length = adsr->delayTimeMsec + adsr->attackTimeMsec + adsr->holdTimeMsec + adsr->decayTimeMsec + adsr->releaseTimeMsec;
      
       int SustainTime = length * 5 / 24;
       int releaseSample =  adsr->samplesPerMillisecond * (adsr->delayTimeMsec + adsr->attackTimeMsec + adsr->holdTimeMsec + adsr->decayTimeMsec + SustainTime);
       adsr->releaseTimeStart = releaseSample;
       
       length += SustainTime;
       float ticks = length / width * adsr->samplesPerMillisecond;
       
       int bottom = half + 150;
       int ylast = bottom;
       g.setColour (Colours::red);
       g.drawLine (0, half,width, half, 2.0f);
       
       for(int i=0;i<width;++i){
           int y = 150 + half - 300.0f * adsr->output;
           g.setColour (Colours::yellow);
           g.drawLine (i, ylast, i+1, y, 2.0f);
           if(adsr->state == Adsr::ADSR_RELEASE){
                g.setColour (Colours::blue);
           }else if(adsr->state == Adsr::ADSR_HOLD){
               g.setColour (Colours::yellow);
           }else if(adsr->state == Adsr::ADSR_ATTACK){
               g.setColour (Colours::red);
           }
           else if(adsr->state == Adsr::ADSR_SUSTAIN){
               g.setColour (Colours::grey);
           }
           else{
               g.setColour (Colours::green);
           }
               
           g.drawLine (i, y, i, bottom   , 0.4f);

           adsr->tick(ticks);
           if(adsr->timeLapse >= releaseSample && adsr->state == Adsr::ADSR_SUSTAIN){
               adsr->release();
           }
           ylast = y;
       }
    }
};
