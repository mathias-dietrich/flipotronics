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

// https://docs.juce.com/master/tutorial_synth_using_midi_input.html

class Core {       // The class
  public:             // Access specifier
    Core(){
        arp = new Arp();
    }
    
    ~Core(){
        delete arp;
    }
    
    int voiceCount = 16;
    Voice voices[32] ;
    
    void handle(AudioBuffer<float>& buffer, MidiBuffer& midiMessages,int totalNumInputChannels, int totalNumOutputChannels);
    void init (double sampleRate, int samplesPerBlock);
    
     Arp *arp;
    
private:

    double clock = 0;
    int sampleRate;
    int samplesPerBlock;
    double m_frequency = 440;
};

#endif /* Core_hpp */
