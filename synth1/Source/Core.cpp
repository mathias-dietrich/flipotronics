//
//  Core.cpp
//  synth1
//
//  Created by Mathias Dietrich on 30.05.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#include "Core.h"
void Core::init (double sampleRate, int samplesPerBlock){
    this->sampleRate = sampleRate;
    this->samplesPerBlock = samplesPerBlock;
    arp->init(sampleRate, samplesPerBlock);
    
    for (int i=0; i<voiceCount; ++i) {
        voices[i].init( sampleRate,  samplesPerBlock);
        voices[i].active = true;
    }
}

void Core::handle(AudioBuffer<float>& buffer, MidiBuffer& midiMessages, int totalNumInputChannels, int totalNumOutputChannels) {

    ScopedNoDenormals noDenormals;
 
    auto* channelDataL = buffer.getWritePointer (0);
    auto* channelDataR = buffer.getWritePointer (1);
    
    
    // clear buffer
    for (int i=0; i<samplesPerBlock; ++i) {
        channelDataL[i] =  0;
        channelDataR[i] =  0;
    }
    
    for( int i =0; i < voiceCount;++i){
           if(voices[i].active){
               voices[i].render(clock, buffer );
           }
     }
    clock += samplesPerBlock;
}
