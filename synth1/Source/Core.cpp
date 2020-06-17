//
//  Core.cpp
//  synth1
//
//  Created by Mathias Dietrich on 30.05.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#include "Core.h"


using namespace std;

void Core::init (double sampleRate, int samplesPerBlock){
    this->sampleRate = sampleRate;
    this->samplesPerBlock = samplesPerBlock;
    this->blocksPerSeccond = sampleRate / samplesPerBlock;
    WaveTable::of()->init(sampleRate,samplesPerBlock );

    patchCurrent = 1;
    
    // ARP
   // arp->init(sampleRate, samplesPerBlock);
    //arp->setPlayer(this);

    // Voices
    for (int i=0; i<MAXVOICE; ++i) {
        voices[i].vid = i;
        voices[i].init( sampleRate, samplesPerBlock);
        voices[i].active = false;
    }
    
    // Tuning
    for (int i=0; i<256; ++i) {
        tuneTable[i] = MidiToFreq(i,440);
    }
    for (int i=0; i<12; ++i) {
        tuneMulti[i] = 1.0;
    }
    
    // FX
    delay.init( sampleRate, samplesPerBlock);
    
    timeAllowedMsec =  samplesPerBlock / sampleRate * 1000 ;
}

void Core::handle(AudioBuffer<float>& buffer, MidiBuffer& midiMessages, int totalNumInputChannels, int totalNumOutputChannels) {
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
            startVoice(channel,note, velocity);
        }
        if(result.isNoteOff()){
            int note = result.getNoteNumber();
            int channel = result.getChannel();
            endVoice(channel,note);
        }
    }
    
    // Update Parameter
    if(updateCounter % UPDATEDEVIDER == 0){
        
        // handle Smoothing
        float c = sampleRate * 0.001f * UPDATEDEVIDER;
        for(int i =0; i < MAXPARAM;++i){
            if(params[i].smoothTime > 0){
                if(abs(par[i]) < abs(par[i] + parTargetDelta[i]) - 0.001){
                    float delta =  parTargetDelta[i] /  (params[i].smoothTime *c);
                    par[i] = par[i] + delta;
                }
            }
        }
        for(int i=0; i < MAXVOICE;++i){
            if(voices[i].active){
              voices[i].update(clock);
            }
        }
       // cout << "timeTaken (msec): " << timeTaken / 1000.0f << " Blocksize: " << samplesPerBlock <<  " Allowed: " << timeAllowedMsec << endl;
    }
    ++updateCounter;
    
    // Prepare audio uffer
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
    delay.handle(buffer,  totalNumInputChannels,  totalNumOutputChannels);
    
    // Set SCope Buffer for the Ouput UI
    for (int i=0; i<samplesPerBlock; ++i) {
        scopeBuffer[i + scopeCounter * samplesPerBlock] =  (channelDataL[i] + channelDataR[i]) *0.5f;
    }
    
    ++scopeCounter;
    if (scopeCounter >= blocksPerSeccond){
        scopeCounter = 0;
    }
    
    // Move Clock
    clock += samplesPerBlock;
    
    // Measure time taken
    auto end = std::chrono::high_resolution_clock::now();
    int64 nanoSec = std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
    timeTaken = (timeTaken+nanoSec) * 0.5;
}
