//
//  Core.cpp
//  synth1
//
//  Created by Mathias Dietrich on 30.05.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#include "Core.h"
#include "Func.h"

void Core::init (double sampleRate, int samplesPerBlock){
    this->sampleRate = sampleRate;
    this->samplesPerBlock = samplesPerBlock;
    
    patchCurrent = 1;
    
    // ARP
    arp->init(sampleRate, samplesPerBlock);

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
}

void Core::handle(AudioBuffer<float>& buffer, MidiBuffer& midiMessages, int totalNumInputChannels, int totalNumOutputChannels) {

    ScopedNoDenormals noDenormals;
    
    // Handle Midi Messages
    MidiMessage result;
    int samplePosition;
    MidiBuffer::Iterator n(midiMessages);
    while(n.getNextEvent (result, samplePosition)){
        if(result.isNoteOn()){
            int note = result.getNoteNumber();
            float velocity = result.getVelocity() / 127.0;
            int channel = result.getChannel();
            startVoice(channel,note, velocity);
        }
        if(result.isNoteOff()){
            int note = result.getNoteNumber();
            int channel = result.getChannel();
            endVoice(channel,note);
        }
    }
    
    // Update
    if(updateCounter % UPDATEDEVIDER == 0){
        for(int i=0; i < MAXVOICE;++i){
            if(voices[i].active){
              voices[i].update(clock);
            }
        }
    }
    ++updateCounter;
    
    // Clear buffer
    auto* channelDataL = buffer.getWritePointer (0);
    auto* channelDataR = buffer.getWritePointer (1);
    for (int i=0; i<samplesPerBlock; ++i) {
        channelDataL[i] =  0;
        channelDataR[i] =  0;
    }
    
    // Render Voices
    for(int i=0; i < MAXVOICE;++i){
           if(voices[i].active){
               voices[i].render(clock, buffer);
           }
     }
    
    // Move Clock
    clock += samplesPerBlock;
}