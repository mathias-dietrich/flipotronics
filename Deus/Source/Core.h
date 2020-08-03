//
//  Core.h
//  Deus
//
//  Created by Mathias Dietrich on 7/28/20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef Core_h
#define Core_h

#include "Preset.h"
#include "Model.h"
#include "Voice.h"
#include "Matrix.h"
#include "Detector.h"
#include "DelayFX.h"
#include "FileManager.h"

class Core {
protected:
      static Core *instance;
    
public:
    
    Core(){
        instance = this;
        masterVolume = 1.0;
        noOfVoices = 32;
    }
    
    ~Core(){

    }
    
    static Core * of() {
        return instance;
    }
    
    void processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages, int totalNumInputChannels, int totalNumOutputChannels){
        
        ScopedNoDenormals noDenormals;
        
        auto begin = std::chrono::high_resolution_clock::now();
        
        // Handle Midi Messages
        MidiMessage result;
        int samplePosition;
        MidiBuffer::Iterator n(midiMessages);
        
        while(n.getNextEvent (result, samplePosition)){
            if(result.isNoteOn()){
                int note = result.getNoteNumber();
                float velocity = result.getVelocity() / 127.0f;
                int channel = result.getChannel();
                startVoice(channel,note, velocity, 0);
            }
            if(result.isNoteOff()){
                int note = result.getNoteNumber();
                int channel = result.getChannel();
                endVoice(channel,note);
            }
        }
        
        // Prepare audio buffer
        auto* channelDataL = buffer.getWritePointer (0);
        auto* channelDataR = buffer.getWritePointer (1);
        std::fill(channelDataL, channelDataL + samplesPerBlock, 0);
        std::fill(channelDataR, channelDataR + samplesPerBlock, 0);
        
        // Render Voices
        for(int i=0; i < MAXVOICE;++i){
          if(voices[i].active){
              voices[i].render(clock, buffer);
          }
        }

        // Render FX
        delayfx.handle(buffer,  totalNumInputChannels,  totalNumOutputChannels);
        
         for(int i=0; i < samplesPerBlock;++i){
             channelDataL[i] *= masterVolume;
             channelDataR[i] *= masterVolume;
         }
        
        // Move Clock
        clock += samplesPerBlock;
        
        // Detector
        detector.handle(buffer,  totalNumInputChannels,  totalNumOutputChannels);
        
        // Measure time taken
        auto end = std::chrono::high_resolution_clock::now();
        int64 nanoSec = std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
        Model::of()->timeTaken = (Model::of()->timeTaken+nanoSec) * 0.5;
    }
    
    void startVoice(int channel,int note, float velocity, int group){
        int vid = findNewVoice(note, channel);
        //voices[vid].matrix = matrix;
        voices[vid].velocity = velocity;
        if(voices[vid].active){
           voices[vid].noteRetrigger();
           return;
        }
        voices[vid].noteOn(channel, note);
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
    
    int findExistingVoice(int midiChannel, int midiNoteNumber){
       for(int i=0; i < MAXVOICE;i++){
           if(midiChannel == voices[i].midiChannel && midiNoteNumber== voices[i].noteNumber){
               return voices[i].vid;
           }
       }
       return -1;
   }
    
    // Voicepool - find next voice to uae
    int findNewVoice(int midiNoteNumber,int midiChannel){
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
    
    void init(double sampleRate, int samplesPerBlock){
        this->sampleRate = sampleRate;
        this->samplesPerBlock = samplesPerBlock;
        this->blocksPerSeccond = sampleRate / samplesPerBlock;
        maxTimeMsec = 1000 * samplesPerBlock / sampleRate;

        // Voices
        for (int i=0; i<MAXVOICE; ++i) {
           voices[i].vid = i;
           voices[i].init( sampleRate, samplesPerBlock);
           voices[i].active = false;
        }

        delayfx.init(sampleRate,samplesPerBlock );

        detector.init(sampleRate, samplesPerBlock);
        detector.setAttack(20);
        detector.setRelease(200);
    }
    
    void configure(Preset preset){
        
        // Configure FX
        for (int i=0; i<delayfx.getParamCount(); ++i) {
            delayfx.set(i, preset.params[mDelay][i].valF);
        }
        
        // Configure Voices
         for (int i=0; i<MAXVOICE; ++i) {
             voices[i].configure(preset);
         }
    }
    
    void update(E_Module module, int pid, float val){
        Model::of()->preset.params[module][pid].valF = val;
        if(module == mGlobal){
            switch(pid){
                case 0:
                    masterVolume = DecibelToLinear(val);
                break;
                    
                case 1:
                    noOfVoices = val;
                break;
            }
            return;
        }
        if(module == mMacro){
            switch(pid){
                case 16: // tuning
                Model::of()->preset.tuning = val;
                break;
            }
        }
        if(module == mDelay){
            delayfx.set( pid, val);
        }
        for (int i=0; i<MAXVOICE; ++i) {
            voices[i].update(module, pid, val);
        }
    }
    
    Voice voices[MAXVOICE] ;
    float maxTimeMsec;
    
private:
    int sampleRate;
    int samplesPerBlock;
    int blocksPerSeccond;
    int64 clock;
    atomic<float> masterVolume;
    atomic<int>  noOfVoices;
    Detector detector;
    DelayFX delayfx;
};
#endif /* Core_h */
