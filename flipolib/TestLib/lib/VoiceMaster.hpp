//
//  VoiceMaster.hpp
//  TestLib
//
//  Created by Mathias Dietrich on 02.03.21.
//

#ifndef VoiceMaster_hpp
#define VoiceMaster_hpp

#include <stdio.h>
#include <ostream>
#include  <iostream>
#include "SimpleOsc.hpp"

using namespace std;

enum VoiceMode{
    POLY,
    MONO,
    UNISONO,
    TWOVOICES
};

enum PlayMode{
    RETRIGGER,
    LEGSTO,
    GLISSANDO
};

enum Algo{
    OLDEST,
    YOUNGEST,
    LOWEST,
    HIGHEST,
    IGNORE
};

class VoiceMaster{
    
public:
    
    VoiceMaster(){
        
        simpleOsc = new SimpleOsc();
        simpleOsc->setup();
    }
    void noteOn(int channel, int note, int velocity);
    void noteOff(int channel, int note, int velocity);
    void aftertouch(int channel, int pressure);
    
    void allNotesOff(int channel);
    void clearVoice(int id);
    void clearAllVoices();
    void pitchBend(int channel, int val);
    void modWheel(int channel, int val);
    void controller(int channel, int cc, int val);
    
    void configure(int zone, int channel, int noOfVoices);

    //77Settings (per Channel or all)
    int noOfVoicesTotal;
    int noOfZones;
    enum VoiceMode voiceMode; //
    enum Algo algo;
    int PitchWheelMin;
    int PitchWheelMax;
    enum PlayMode playMode; //
    
    SimpleOsc *simpleOsc = 0;
};

#endif /* VoiceMaster_hpp */
