//
//  Core.hpp
//  synth1
//
//  Created by Mathias Dietrich on 30.05.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef Core_hpp
#define Core_hpp

#include <stdio.h>
#include <JuceHeader.h>

#include "Arp.h"
#include "Voice.h"
#include "Const.h"
#include "ParamBuilder.h"
#include "PatchLoader.h"


// https://docs.juce.com/master/tutorial_synth_using_midi_input.html

class Core {
    
  public:
    Core(){
        patchLoader = new PatchLoader();
        ParamBuilder *b = new ParamBuilder();
        b->build();
        delete b;
        arp = new Arp();
    }
    
    ~Core(){
        delete arp;
        delete patchLoader;
    }
    
    stk::Filter * filter;
    
    void loadPatch(int p){
        patchLoader->load(p);
    }

    void handle(AudioBuffer<float>& buffer, MidiBuffer& midiMessages,int totalNumInputChannels, int totalNumOutputChannels);
    
    void init (double sampleRate, int samplesPerBlock);
    
    void startVoice(int midiChannel, int midiNoteNumber, float velocity){
        int vid = findNewVoice();
        voices[vid].midiChannel = midiChannel;
        voices[vid].noteNumber = midiNoteNumber;
        voices[vid].velocity = velocity;
        voices[vid].reset();

        std::cout <<  "Starting Voice midiNoteNumber:" << midiNoteNumber << " velocity:" << velocity << std::endl;
    }
    
    void endVoice(int midiChannel, int midiNoteNumber){
        int vid = findExistingVoice(midiChannel, midiNoteNumber);
        voices[vid].noteOff();
        std::cout <<  "End Voice midiNoteNumber:" << midiNoteNumber  << std::endl;
    }
    
    void killVoice(int midiChannel, int midiNoteNumber){
        int vid = findExistingVoice(midiChannel, midiNoteNumber);
        voices[vid].active = false;
        std::cout << "Kill Voice midiNoteNumber:" << midiNoteNumber  << std::endl;
    }
    
    void killAllVoice(){
        for(int i=0; i < MAXVOICE;i++){
            voices[i].kill();
        }
         std::cout << "Kill All Voice midiNoteNumber:" << std::endl;
    }
    
    int findNewVoice(){
        for(int i=0; i < MAXVOICE;i++){
            if(!voices[i].active){
                voices[i].now = Time::currentTimeMillis();
                return voices[i].vid;
            }
        }
        // TODO find oldest voice
        return -1;
    }
    
    int findExistingVoice(int midiChannel, int midiNoteNumber){
        for(int i=0; i < MAXVOICE;i++){
            if(midiChannel == voices[i].midiChannel && midiNoteNumber== voices[i].noteNumber){
                return voices[i].vid;
            }
        }
        return -1;
    }
    
    int updateCounter = 0;
    int scopeCounter = 0;
    PatchLoader *patchLoader;
    Voice voices[32] ;
    
private:
    Arp *arp;
    double clock = 0;
    int sampleRate;
    int samplesPerBlock;
    double m_frequency = 440;
};

#endif /* Core_hpp */
