#pragma once

#include <JuceHeader.h>
#include "Core.h"
#include "Param.h"
#include "Const.h"
#include "SpectrumComponent.h"
#include "WaveComponent.h"
#include "OutputComponent.h"
#include "AdsrComponent.h"
#include "LfoComponent.h"
#include "CurveComponent.h"
#include "ShowTableComponent.h"

//  https://github.com/ffAudio/ff_meters
//==============================================================================
/**
*/
class Synth1AudioProcessor  : public AudioProcessor, MidiKeyboardStateListener
{
public:
    //==============================================================================
    Synth1AudioProcessor();
    ~Synth1AudioProcessor();
    
    SpectrumComponent spectrum;
    WaveComponent waveComponent;
    OutputComponent outputComponent;
    AdsrComponent adsrComponent;
    LfoComponent lfoComponent;
    CurveComponent curveComponent;
    ShowTableComponent showTableComponent;
    
    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    Core *core;
    
    bool isArpOn;
    
    void reset() override{
        
    }
    
    void close(){
        core->close();
    }
    
    void handleNoteOn (MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity) override {
        core->startVoice( midiChannel,  midiNoteNumber,  velocity,0);
        Model::of().isUpdateParams = true;
    }
     
    void handleNoteOff (MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity) override {
         core->endVoice( midiChannel,  midiNoteNumber);
        Model::of().isUpdateParams = true;
    }
    
    void panic(){
        core->killAllVoice();
    }
    
    void browse(){

    }
    
    void setArp(bool running){
        core->setArp(running);
    }
    
    void loadPatch(int p){
        core->loadPatch(p);
    }
    
    float maxTimeMsec;

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Synth1AudioProcessor)
};
