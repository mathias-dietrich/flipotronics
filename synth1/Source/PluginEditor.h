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
#include "PitchWheel.h"
#include "ImageFactory.h"
#include "Poti.h"
#include "PotsComponent.h"
#include "KeysComponent.h"

//============Poti==================================================================

class Synth1AudioProcessorEditor  : public AudioProcessorEditor,
    public Button::Listener,  public Slider::Listener, public Timer
{
public:
    Synth1AudioProcessorEditor (Synth1AudioProcessor&);
    ~Synth1AudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
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

    TextButton btnBrowse;
    TextButton btnArp;

    Label timeLabel;
    
    BankLoader *bankLoader;
    
    int paramRange = 0;
    int paramRoot = 0;

    ComboBox viewMode;
    ComboBox viewZoom;
    
    Label progName;
    Label progNumber;

    int maxTime;
    
private:
    Synth1AudioProcessor& processor;
   // Image vumeter; // = ImageCache::getFromMemory (img::meter_png, img::meter_pngSize);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Synth1AudioProcessorEditor)
    
    void buttonClicked (Button* button)  override {
        // Save
        if(button->getRadioGroupId()==16) {
            bankLoader->save();
            Model::of().set();
            Model::of().compareMode = false;
            setDials();
           return;
        }
        
        // Load
        if(button->getRadioGroupId()==17) {
            bankLoader->load();
            processor.loadPatch(Model::of().patchCurrent);
            Model::of().set();
            Model::of().compareMode = false;
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
            Model::of().patchCurrent++;
            if(Model::of().patchCurrent >=127){
                Model::of().patchCurrent = 0;
            }
            processor.loadPatch(Model::of().patchCurrent);
            Model::of().compareMode = false;
            Model::of().set();
            setDials();
            return;
        }
        
        // Progr Down
        if(button->getRadioGroupId()==23) {
            Model::of().patchCurrent--;
            if(Model::of().patchCurrent < 0){
               Model::of().patchCurrent = 127;
            }
            
            processor.loadPatch(Model::of().patchCurrent);
            Model::of().compareMode = false;
            Model::of().set();
            
            setDials();
            return;
        }
        
        // Compare
        if(button->getRadioGroupId()==24) {
            Model::of().compareMode = !Model::of().compareMode;
            Model::of().swap();
            setDials();
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
    
    void setDials() {
        float par[MAXPARAM];
        for(int i =0; i < MAXPARAM;++i){
            par[i] = Model::of().par[i] ;
        }
        
        potsComponent.paramRoot = paramRoot;
        potsComponent.paramRange = paramRange;
        potsComponent.setDials();
        
        // Param Select
        for(int i=0; i < 16; ++i){
            btnParam[i].setToggleState(false, NotificationType::dontSendNotification);
        }
        if(paramRange<16){
            btnParam[paramRange].setToggleState(true, NotificationType::dontSendNotification);
        }
        
        // Program Display
        progNumber.setText(toString(Model::of().patchCurrent+1), NotificationType::dontSendNotification);
        progName.setText(Model::of().patchNameCurrent, NotificationType::dontSendNotification);
        btnCompare.setToggleState(Model::of().compareMode, NotificationType::dontSendNotification);
        
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
        Model::of().isUpdateParams = true;
    }
    
    void sliderValueChanged(Slider *  slider) override {
        int sid = slider->getName().getIntValue();

        // Edits Mode ================================================================
        startEdit();
        int pid = paramRoot * 256 + paramRange * 16 + sid;
        if(Model::of().params[pid].smoothTime > 0){
            Model::of().parTargetDelta[pid] = Model::of().par[pid] - slider->getValue();
        }else{
            Model::of().par[pid] = slider->getValue();
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
    
    void styleMenuChangedView(){
        Model::of().viewModeSetting = viewMode.getSelectedId();
        processor.spectrum.setVisible(false);
        processor.waveComponent.setVisible(false);
        processor.outputComponent.setVisible(false);
        processor.adsrComponent.setVisible(false);
        processor.lfoComponent.setVisible(false);
        processor.curveComponent.setVisible(false);
        switch(Model::of().viewModeSetting){
            case vSpectrum:
                processor.spectrum.setVisible(true);
                break;
                
            case vADSR1:
            case vADSR2:
            case vADSR3:
            case vADSR4:
                processor.adsrComponent.setVisible(true);
                break;
            
           case vWave:
                processor.waveComponent.setVisible(true);
                break;
                
            case vPlot:
                processor.outputComponent.setVisible(true);
                break;
                
            case vLFO1:
            case vLFO2:
            case vLFO3:
            case vLFO4:
                processor.lfoComponent.setVisible(true);
                break;
              
            case vCurve:
                processor.curveComponent.setVisible(true);
                break;
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
    
    void timerCallback() override{
        repaint();
        setDials();
    }
    
    void startEdit(){
        Model::of().compareMode = true;
    }
    
    PotsComponent potsComponent;
    KeysComponent * keysComponent;
};
