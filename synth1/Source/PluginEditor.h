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
#include "PerformanceComponent.h"
#include "LibraryComponent.h"
#include "ArpComponent.h"
#include "SetupComponent.h"

//============Poti==================================================================

class Synth1AudioProcessorEditor  : public AudioProcessorEditor, public Timer, public KeyListener
{
public:
    Synth1AudioProcessorEditor (Synth1AudioProcessor&);
    ~Synth1AudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

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
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Synth1AudioProcessorEditor)

    void setDials() {
        float par[MAXPARAM];
        for(int i =0; i < MAXPARAM;++i){
            par[i] = Model::of().par[i] ;
        }
        Model::of().isUpdateParams = true;
        potsComponent.setDials();
        paramButtonComponent.setDials();
        keysComponent->setDials();
        viewMeterComponent.setDials();
        debugComponent.setDials();
        headerComponent.setDials();
        libraryComponent.setDials();
        arpComponent.setDials();
        performanceComponent.setDials();
        debugComponent.setDials();

        switch( Model::of().masterSel){
            case mEdit:
                libraryComponent.setVisible(false);
                performanceComponent.setVisible(false);
                debugComponent.setVisible(false);
                arpComponent.setVisible(false);
                setupComponent.setVisible(false);
                paramButtonComponent.setVisible(false);
                potsComponent.setVisible(false);
                viewMeterComponent.setVisible(false);
                subComponentsVisible(false);
                break;
                
            case mLibrary:
                performanceComponent.setVisible(false);
                debugComponent.setVisible(false);
                paramButtonComponent.setVisible(false);
                potsComponent.setVisible(false);
                viewMeterComponent.setVisible(false);
                arpComponent.setVisible(false);
                setupComponent.setVisible(false);
                libraryComponent.setVisible(true);
                subComponentsVisible(false);
                break;
                
            case mPerform:
                paramButtonComponent.setVisible(false);
                potsComponent.setVisible(false);
                viewMeterComponent.setVisible(false);
                libraryComponent.setVisible(false);
                arpComponent.setVisible(false);
                setupComponent.setVisible(false);
                performanceComponent.setVisible(true);
                subComponentsVisible(false);
                break;
                
            case mArp:
                performanceComponent.setVisible(false);
                potsComponent.setVisible(false);
                viewMeterComponent.setVisible(false);
                debugComponent.setVisible(false);
                paramButtonComponent.setVisible(false);
                setupComponent.setVisible(false);
                arpComponent.setVisible(true);
                subComponentsVisible(false);
                break;
                
            case mSetup:
                performanceComponent.setVisible(false);
                potsComponent.setVisible(false);
                viewMeterComponent.setVisible(false);
                debugComponent.setVisible(false);
                paramButtonComponent.setVisible(false);
                viewMeterComponent.setVisible(false);
                libraryComponent.setVisible(false);
                arpComponent.setVisible(false);
                setupComponent.setVisible(true);
                subComponentsVisible(false);
                break;
                
            case mDebug:
                performanceComponent.setVisible(false);
                paramButtonComponent.setVisible(true);
                viewMeterComponent.setVisible(true);
                libraryComponent.setVisible(false);
                arpComponent.setVisible(false);
                setupComponent.setVisible(false);
                potsComponent.setVisible(true);
                debugComponent.setVisible(true);
                subComponentsVisible(true);
                break;
            }
    }
    
    void subComponentsVisible(bool show){
        if(show){
            viewMode.setVisible(true);
            styleMenuChangedView();
            return;
        }
        processor.spectrum.setVisible(false);
        processor.waveComponent.setVisible(false);
        processor.outputComponent.setVisible(false);
        processor.adsrComponent.setVisible(false);
        processor.lfoComponent.setVisible(false);
        processor.curveComponent.setVisible(false);
        processor.showTableComponent.setVisible(false);
        viewMode.setVisible(false);
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
    PerformanceComponent performanceComponent;
    LibraryComponent libraryComponent;
    ArpComponent arpComponent;
    SetupComponent setupComponent;
};
