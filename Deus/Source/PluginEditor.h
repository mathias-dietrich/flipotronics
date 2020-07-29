/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

#include "Inc.h"
#include "MasterComponent.h"
#include "EventHandler.h"
#include "UILoader.h"
#include "KeysListener.h"

//==============================================================================
/**
*/
class DeusAudioProcessorEditor : public AudioProcessorEditor, public EventHandler, public Timer, public KeyListener
{
public:
    DeusAudioProcessorEditor (DeusAudioProcessor&);
    ~DeusAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    void configure() override{
        // Load a new Preset
        Preset preset;
        
        // Configure the UI
        
        
        // Configure the Processor
        processor.core->configure(preset);
    }
    
    void timerCallback() override{
        if(lastZoom != Model::of()->global.lastGuiZoom){
            lastZoom = Model::of()->global.lastGuiZoom;
            resizeUi(lastZoom);
        }
    }
    
    void resizeUi(int sel)override{
        Model::of()->global.lastGuiZoom = sel;
        float p = 1.0;
        switch (sel)
        {
            case 1: // 50
                p = 0.5f;
                break;
            case 2: //
                p = 0.6f;
                break;
            case 3: //
                p = 0.7f;
                break;
            case 4: //
                p = 0.8f;
                break;
            case 5: //
                p = 0.9f;
                break;
            case 6: //
                p = 1.0f;
                break;
            case 7: //
                p = 1.2f;
                break;
            case 8: //
                p = 1.4f;
                break;
            case 9: //
                p = 1.6f;
                break;
            case 10: //
                p = 1.8f;
                break;
            case 11: //
                p = 2.0f;
                break;
        }
        
        Desktop::getInstance().setGlobalScaleFactor(1);
        float ws = UIWIDTH;
        int hs = UIHEIGHT;
        setSize (ws * p, hs * p);
        Desktop::getInstance().setGlobalScaleFactor((float)this->getWidth() / ws);
       
        repaint();
        masterComponent.setDials();
    }
    
     void update()override {
         if(Model::of()->masterSel != masterSelLast){
             
             masterSelLast = Model::of()->masterSel;
             masterComponent.clearUi();
             node->clearAll();
             switch(masterSelLast){
                 case mEdit:
                    uiloader.load(node, "master.xml");
                 break;
                     
                case mLibrary:
                    uiloader.load(node, "library.xml");
                break;
                     
                case mPerform:
                    uiloader.load(node, "perform.xml");
                break;
                     
                case mArp:
                    uiloader.load(node, "arp.xml");
                break;
                     
                case mSetup:
                     uiloader.load(node, "setup.xml");
                break;
                     
                case mDebug:
                     uiloader.load(node, "debug.xml");
                break;
             }
              masterComponent.build(node);
             masterComponent.resized();
        }
    }
    
     bool keyPressed (const KeyPress &key, Component *originatingComponent) override{
         return listener.keyPressed(key, originatingComponent);
    }
      
     
    bool  keyStateChanged (bool isKeyDown, Component *originatingComponent) override {
        return listener.keyStateChanged(isKeyDown, originatingComponent);
    }

private:
    E_Master masterSelLast = mEdit;
    int lastZoom;
    
    DeusAudioProcessor& processor;
    MasterComponent masterComponent;
    UILoader uiloader;
    Node * node = new Node();
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeusAudioProcessorEditor)
    KeysListener listener;
};
