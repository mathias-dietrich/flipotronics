//
//  Arp.hpp
//  synth1
//
//  Created by Mathias Dietrich on 31.05.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef Arp_hpp
#define Arp_hpp

#include <stdio.h>
#include <JuceHeader.h>
#include "Note.h"

class Arp {       // The class
  public:             // Access specifier
    Arp(){
        steps[0].freq = 440;
    }
    
    ~Arp(){

    }
    
    void init (double sampleRate, int samplesPerBlock){
        this->sampleRate = sampleRate;
        this->samplesPerBlock = samplesPerBlock;
    }
    
   int getNotes(int clock, Note * notes[]){
       notes[0] = new Note();
       notes[0]->freq = 220;
       notes[0]->startClock = clock;
       notes[0]->endClock = notes[0]->startClock  + sampleRate / 16;
       notes[1] = new Note();
       notes[1]->freq = 440;
       notes[1]->startClock = clock + sampleRate / 2;
       notes[1]->endClock = notes[1]->startClock  + sampleRate / 16;
       return 2;
   }
    
private:
    Note steps[32];
    int sampleRate;
    int samplesPerBlock;
};


#endif /* Arp_hpp */
