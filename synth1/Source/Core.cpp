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
    arp->init(sampleRate, samplesPerBlock);
    
    noOfVoices = 2;
    
    for (int i=0; i<noOfVoices; ++i) {
        voices[i].init( sampleRate,  samplesPerBlock);
        voices[i].active = false;
    }
    
    std::cout << "==========================" << std::endl;
    float t = LinearToDecibel(0.0);
    std::cout << t << std::endl;
    std::cout << MidiToFreq(69, 440) << std::endl;
    std::cout << FreqToMidi(MidiToFreq(69, 440),440) << std::endl;
    
    std::cout << "==========================" << std::endl;
}

void Core::handle(AudioBuffer<float>& buffer, MidiBuffer& midiMessages, int totalNumInputChannels, int totalNumOutputChannels) {

    ScopedNoDenormals noDenormals;
 
    // Clear buffer
    auto* channelDataL = buffer.getWritePointer (0);
    auto* channelDataR = buffer.getWritePointer (1);
    for (int i=0; i<samplesPerBlock; ++i) {
        channelDataL[i] =  0;
        channelDataR[i] =  0;
    }
    
    // Render Voices
    for( int i =0; i < noOfVoices;++i){
           if(voices[i].active){
               voices[i].render(clock, buffer  );
           }
     }
    
    // Move Clock
    clock += samplesPerBlock;
}
