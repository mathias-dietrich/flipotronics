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
#include "ParamButtonComponent.h"
#include "ViewMeterComponent.h"
#include "DebugComponent.h"
#include "FontLoader.h"
#include "HeaderComponent.h"

//============Poti==================================================================

class Synth1AudioProcessorEditor  : public AudioProcessorEditor, public Button::Listener,  public Timer
{
public:
    Synth1AudioProcessorEditor (Synth1AudioProcessor&);
    ~Synth1AudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    TextButton btnArp;

    Label timeLabel;

    int paramRange = 0;
    int paramRoot = 0;

    ComboBox viewMode;
    ComboBox viewZoom;

    int maxTime;
    
private:
    Synth1AudioProcessor& processor;
   // Image vumeter; // = ImageCache::getFromMemory (img::meter_png, img::meter_pngSize);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Synth1AudioProcessorEditor)
    
    void buttonClicked (Button* button)  override {

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
    }
    
    void setDials() {
        float par[MAXPARAM];
        for(int i =0; i < MAXPARAM;++i){
            par[i] = Model::of().par[i] ;
        }

        btnArp.setToggleState(processor.isArpOn, NotificationType::dontSendNotification);
        
        Model::of().isUpdateParams = true;
        potsComponent.setDials();
        paramButtonComponent.setDials();
        keysComponent->setDials();
        viewMeterComponent.setDials();
        debugComponent.setDials();
        headerComponent.setDials();
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
    ParamButtonComponent paramButtonComponent;
    KeysComponent * keysComponent;
    ViewMeterComponent viewMeterComponent;
    DebugComponent debugComponent;
    HeaderComponent headerComponent;
};
