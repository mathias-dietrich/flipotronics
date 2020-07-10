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
#include "Player.h"
#include "Func.h"
#include "AudioSampleFifo.h"
#include "Delay.h"
#include "Detector.h"
#include "BankLoader.h"
#include "ModMatrix.h"
#include "Matrix.h"
#include "ControllerMapping.h"

// https://docs.juce.com/master/tutorial_synth_using_midi_input.html

class Core : public Player{
    
  public:
    
    Matrix matrix;
    ModMatrix modMatrix;
    ControllerMapping controllerMapping;
    
    AbstractFifo test { 1024 };
    AudioSampleFifo<float> fifo;
    
    Detector detector;
    
    Core() : Player(){
        patchLoader = new PatchLoader();
        paramBuilder = new ParamBuilder();
        paramBuilder->build();
        arp = new Arp();
        arp->setPlayer(this);
    }
    
    ~Core(){
        delete arp;
        delete patchLoader;
        delete paramBuilder;
        delete filter;
    }
    
    void close(){
        arp->stop();
    }
    
    void loadPatch(int p){
        patchLoader->load(p);
    }

    void handle(AudioBuffer<float>& buffer, MidiBuffer& midiMessages,int totalNumInputChannels, int totalNumOutputChannels);
    
    void init (double sampleRate, int samplesPerBlock);
    
     void startVoice(int midiChannel, int midiNoteNumber, float velocity){
         startVoice( midiChannel,  midiNoteNumber,  velocity, 0);
        // startVoice( midiChannel,  midiNoteNumber,  velocity, 1);
         //startVoice( midiChannel,  midiNoteNumber,  velocity, 2);
         //startVoice( midiChannel,  midiNoteNumber,  velocity, 3);
     }
    
    void startVoice(int midiChannel, int midiNoteNumber, float velocity, int group){
        int vid = findNewVoice(midiNoteNumber, midiChannel);
        voices[vid].velocity = velocity;
        float p[MAXPARAM];
           for(int i =0; i < MAXPARAM;++i){
               p[i] = Model::of().par[i + group * MAXPARAM] ;
           }
        if(voices[vid].active){
            voices[vid].retrigger(p + group * MAXPARAM);
            return;
        }
        
        voices[vid].midiChannel = midiChannel;
        voices[vid].noteOn(midiNoteNumber, p + group * MAXPARAM);
        //std::cout <<  "Starting Voice midiNoteNumber:" << midiNoteNumber << " velocity:" << velocity << std::endl;
    }
    
    void endVoice(int midiChannel, int midiNoteNumber){
        int vid = findExistingVoice(midiChannel, midiNoteNumber);
        voices[vid].noteOff();
        //std::cout <<  "End Voice midiNoteNumber:" << midiNoteNumber  << std::endl
    }
    
    void killVoice(int midiChannel, int midiNoteNumber){
        int vid = findExistingVoice(midiChannel, midiNoteNumber);
        voices[vid].active = false;
        //std::cout << "Kill Voice midiNoteNumber:" << midiNoteNumber  << std::endl;
    }
    
    void killAllVoice(){
        for(int i=0; i < MAXVOICE;i++){
            voices[i].kill();
        }
        //std::cout << "Kill All Voice midiNoteNumber:" << std::endl;
    }
    
    // Voicepool - find next voice to uae
    int findNewVoice(int midiNoteNumber,int midiChannel){
        
        // E>xisting Voice?
        for(int i=0; i < MAXVOICE;i++){
            if(midiNoteNumber==voices[i].noteNumber && midiChannel==voices[i].midiChannel){
                return i;
            }
        }
        
        // Innactive Voice available?
        for(int i=0; i < MAXVOICE;i++){
            if(!voices[i].active){
                voices[i].now = Time::currentTimeMillis();
                return voices[i].vid;
            }
        }
        
        // Find oldest Voice
        int64 oldest = Time::currentTimeMillis();
        int posFoundVoice;
        for(int i=0; i < MAXVOICE;i++){
            if(voices[i].now < oldest){
                posFoundVoice = i;
            }
        }
        return posFoundVoice;
    }
    
    int findExistingVoice(int midiChannel, int midiNoteNumber){
        for(int i=0; i < MAXVOICE;i++){
            if(midiChannel == voices[i].midiChannel && midiNoteNumber== voices[i].noteNumber){
                return voices[i].vid;
            }
        }
        return -1;
    }
    
    void setArp(bool running){
        if(running){
             arp->start();
        }else{
             arp->stop();
        }
    }
    
    int updateCounter = 0;
    PatchLoader *patchLoader;
    Voice voices[32] ;
    Delay delay;
    
private:
    Arp *arp;
    double clock = 0;
    int sampleRate;
    int samplesPerBlock;
    int blocksPerSeccond;
    double m_frequency = 440;
    ParamBuilder *paramBuilder;
    stk::Filter * filter;
    int timeAllowedMsec;
    
    int samplePlayerPos;
    
    float p[MAXPARAM];
};

#endif /* Core_hpp */
