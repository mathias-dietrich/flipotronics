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
#include "ShowTableComponent.h"
#include "MyKeyListener.h"

//============Poti==================================================================

class Synth1AudioProcessorEditor  : public AudioProcessorEditor, public Button::Listener,  public Timer, public KeyListener
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


    int maxTime;
    
     bool keyPressed(const KeyPress &k, Component *c) override{
         std::cout << "key" << k. getTextDescription() << std::endl;
         myListenr.handle(k.getKeyCode(), k.getTextDescription());
         setDials();
         return true;
    }
    
    MyKeyListener myListenr;
    
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
        
       // headerComponent.setVisible(Model::of().showDebugWidgets);
        viewMeterComponent.setVisible(Model::of().showDebugWidgets);
        debugComponent.setVisible(Model::of().showDebugWidgets);
        potsComponent.setVisible(Model::of().showDebugWidgets);
        paramButtonComponent.setVisible(Model::of().showDebugWidgets);
        processor.spectrum.setVisible(Model::of().showDebugWidgets);
        processor.waveComponent.setVisible(Model::of().showDebugWidgets);
        processor.outputComponent.setVisible(Model::of().showDebugWidgets);
        processor.adsrComponent.setVisible(Model::of().showDebugWidgets);
        processor.lfoComponent.setVisible(Model::of().showDebugWidgets);
        processor.curveComponent.setVisible(Model::of().showDebugWidgets);
        processor.showTableComponent.setVisible(Model::of().showDebugWidgets);
        viewMode.setVisible(Model::of().showDebugWidgets);
        btnArp.setVisible(Model::of().showDebugWidgets);
    }
    
    void styleMenuChangedView(){
        Model::of().viewModeSetting = viewMode.getSelectedId();
        processor.spectrum.setVisible(false);
        processor.waveComponent.setVisible(false);
        processor.outputComponent.setVisible(false);
        processor.adsrComponent.setVisible(false);
        processor.lfoComponent.setVisible(false);
        processor.curveComponent.setVisible(false);
        processor.showTableComponent.setVisible(false);
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
              
            case vTable:
                processor.showTableComponent.setVisible(true);
                break;
                
                case vCurve:
                    processor.curveComponent.setVisible(true);
                    break;
        }
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
