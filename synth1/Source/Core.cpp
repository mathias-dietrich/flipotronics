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
    
    for (int i=0; i<voiceCount; ++i) {
        voices[i].init( sampleRate,  samplesPerBlock);
        voices[i].active = false;
    }
    voices[0].active = true;
    voices[0].freq = 440;
    voices[0].volume = 1.0;
    voices[0].volOscSin = 1.0;
    
    voices[1].active = true;
    voices[1].freq = 440 * 3;
    voices[1].volume = 1.0;
    voices[1].volOscSaw = 1.0;
    
    std::cout << "==========================" << std::endl;
    float t = LinearToDecibel(0.0);
    std::cout << t << std::endl;
    std::cout << MidiToFreq(69, 440) << std::endl;
    std::cout << FreqToMidi(MidiToFreq(69, 440),440) << std::endl;
    
    std::cout << "==========================" << std::endl;
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
               voices[i].render(clock, buffer,voiceCount  );
           }
     }
    clock += samplesPerBlock;
}
