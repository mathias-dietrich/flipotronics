//
//  ParamBuilder.h
//  synth1
//
//  Created by Mathias Dietrich on 03.06.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef ParamBuilder_h
#define ParamBuilder_h

#include <stdio.h>
#include <JuceHeader.h>
#include "WaveTable.h"
#include "Model.h"
#include "Func.h"
#include "Param.h"

#define P_TUNING 0
#define P_NOVOICES 1
#define P_VOLUME 7
#define P_PAN 10

// Osc
#define P_OSC1_OCT 16
#define P_OSC1_SEMI 17
#define P_OSC1_FINE 18
#define P_OSC1_VOL 19
#define P_OSC1_WAV 20
#define P_OSC1_PULSE 21
#define P_OSC1_KEYFOLLOW 22
#define P_OSC1_SUB 23

#define P_OSC2_OCT 24
#define P_OSC2_SEMI 25
#define P_OSC2_FINE 26
#define P_OSC2_VOL 27
#define P_OSC2_WAV 28
#define P_OSC2_PULSE 29
#define P_OSC2_KEYFOLLOW 30
#define P_OSC2_SYNC 31

// Filter
#define P_FILTER1_FREQ 32
#define P_FILTER1_RES 33
#define P_FILTER1_TYPE 34
#define P_FILTER1_DRIVE 35
#define P_FILTER_ARCHITECTURE 36

#define P_FILTER2_FREQ 40
#define P_FILTER2_RES 41
#define P_FILTER2_TYPE 42
#define P_FILTER2_DRIVE 43

// ADSR 1
#define P_ADSR1_DELAY 48
#define P_ADSR1_ATTACK 49
#define P_ADSR1_DECAY 50
#define P_ADSR1_SUSTAIN 51
#define P_ADSR1_RELEASE 52
#define P_ADSR1_FREQ 53
#define P_ADSR1_FILT 54
#define P_ADSR1_VOL 55

#define P_ADSR2_DELAY 56
#define P_ADSR2_ATTACK 57
#define P_ADSR2_DECAY 58
#define P_ADSR2_SUSTAIN 59
#define P_ADSR2_RELEASE 60
#define P_ADSR2_FREQ 61
#define P_ADSR2_FILT 62
#define P_ADSR2_VOL 63

#define P_ADSR3_DELAY 64
#define P_ADSR3_ATTACK 65
#define P_ADSR3_DECAY 66
#define P_ADSR3_SUSTAIN 67
#define P_ADSR3_RELEASE 68
#define P_ADSR3_FREQ 69
#define P_ADSR3_FILT 70
#define P_ADSR3_VOL 71

#define P_ADSR4_DELAY 72
#define P_ADSR4_ATTACK 73
#define P_ADSR4_DECAY 74
#define P_ADSR4_SUSTAIN 75
#define P_ADSR4_RELEASE 76
#define P_ADSR4_FREQ 77
#define P_ADSR4_FILT 78
#define P_ADSR4_VOL 79

#define P_LFO1_FREQ 80
#define P_LFO1_WAV 81
#define P_LFO1_DELAY 82
#define P_LFO1_SYNC 83
#define P_LFO1_PITCH 84
#define P_LFO1_FILTER 85
#define P_LFO1_VOL 86
#define P_LFO1_ 87

#define P_LFO2_FREQ 88
#define P_LFO2_WAV 89
#define P_LFO2_DELAY 90
#define P_LFO2_SYNC 91
#define P_LFO2_PITCH 92
#define P_LFO2_FILTER 93
#define P_LFO2_VOL 94
#define P_LFO2_ 95


#define P_PLAYMODE 1023

class ParamBuilder {       // The class
    public:
        void build(){
            for(int i=0; i < 1024; ++i){
                Param p;
                p.pid = i;
                p.name = toString(i);
                params[i] = p;
                p.minVal = 0;
                p.maxVal = 1;
                p.stepVal = 0.01;
                p.type = uFloat;
                p.def = 0;
            }
            
            Param p0;
            p0.pid = P_TUNING;
            p0.name = "Tuning";
            p0.writeable = 1;
            p0.automate = 1;
            p0.valD = 440.0;
            p0.minVal = 435.0;
            p0.maxVal = 445.0;
            p0.stepVal = 0.1;
            p0.def = 440.0;
            params[P_TUNING] = p0;
            
            Param p;
            p.pid = P_NOVOICES;
            p.name = "NoVoices";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 1;
            p.maxVal = 32;
            p.stepVal = 1;
            p.type = uInt;
            p.def = 8;
            params[P_NOVOICES] = p;
            
            p.pid = P_VOLUME;
            p.name = "Volume";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 8;
            params[P_VOLUME] = p;
            
            p.pid = P_PAN;
            p.name = "Pan";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 0.5;
            params[P_PAN] = p;

            p.pid = P_OSC1_OCT;
            p.name = "Osc1 Octave";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = -3;
            p.maxVal = 3;
            p.stepVal = 1;
            p.type = uFloat;
            p.def = 0;
            params[P_OSC1_OCT] = p;
            
            p.pid = P_OSC1_SEMI;
            p.name = "Osc1 Semi";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = -6;
            p.maxVal = 6;
            p.stepVal = 1;
            p.type = uFloat;
            p.def = 0;
            params[P_OSC1_SEMI] = p;
            
            p.pid = P_OSC1_FINE;
            p.name = "Osc1 Fine";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = -6;
            p.maxVal = 6;
            p.stepVal = 1;
            p.type = uFloat;
            p.def = 0;
            params[P_OSC1_FINE] = p;
            
            p.pid = P_OSC1_VOL;
            p.name = "Osc1 Vol";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 0;
            params[P_OSC1_VOL] = p;
            
            p.pid = P_OSC1_WAV;
            p.name = "Osc1 Wav";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 6;
            p.stepVal = 1;
            p.type = uInt;
            p.def = 0;
            params[P_OSC1_WAV] = p;
            
            p.pid = P_OSC1_PULSE;
            p.name = "Osc1 Pulse W";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 100;
            p.stepVal = 0.1;
            p.type = uFloat;
            p.def = 0;
            params[P_OSC1_PULSE] = p;
            
            p.pid = P_OSC1_KEYFOLLOW;
            p.name = "Osc1 Key Follow";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 0.5;
            params[P_OSC1_KEYFOLLOW] = p;
            
            p.pid = P_OSC1_SUB;
            p.name = "Osc1 Sub";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 0;
            params[P_OSC1_SUB] = p;
            
            p.pid = P_OSC2_OCT;
            p.name = "Osc2 Octave";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = -3;
            p.maxVal = 3;
            p.stepVal = 1;
            p.type = uFloat;
            p.def = 0;
            params[P_OSC2_OCT] = p;
            
            p.pid = P_OSC2_SEMI;
            p.name = "Osc2 Semi";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = -6;
            p.maxVal = 6;
            p.stepVal = 1;
            p.type = uFloat;
            p.def = 0;
            params[P_OSC2_SEMI] = p;
            
            p.pid = P_OSC2_FINE;
            p.name = "Osc2 Fine";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = -6;
            p.maxVal = 6;
            p.stepVal = 1;
            p.type = uFloat;
            p.def = 0;
            params[P_OSC2_FINE] = p;
            
            p.pid = P_OSC2_VOL;
            p.name = "Osc2 Vol";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 0;
            params[P_OSC2_VOL] = p;
            
            p.pid = P_OSC2_WAV;
            p.name = "Osc2 Wav";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 6;
            p.stepVal = 1;
            p.type = uInt;
            p.def = 0;
            params[P_OSC2_WAV] = p;
            
            p.pid = P_OSC2_PULSE;
            p.name = "Osc2 Pulse W";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 100;
            p.stepVal = 0.1;
            p.type = uFloat;
            p.def = 0;
            params[P_OSC2_PULSE] = p;
            
            p.pid = P_OSC2_KEYFOLLOW;
            p.name = "Osc2 Key Follow";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 0.5;
            params[P_OSC2_KEYFOLLOW] = p;
            
            p.pid = P_OSC2_SYNC;
            p.name = "Osc2 Sync";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 1;
            p.type = uBool;
            p.def = 0;
            params[P_OSC2_SYNC] = p;
            
            // Filter
            p.pid = P_FILTER1_FREQ;
            p.name = "Filter 1 Freq";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 20;
            p.maxVal = 7000;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 0;
            params[P_FILTER1_FREQ] = p;
            
            p.pid = P_FILTER1_RES;
            p.name = "Filter 1 Res";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 100;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 0;
            params[P_FILTER1_RES] = p;
            
            p.pid = P_FILTER1_TYPE;
            p.name = "Filter 1 Type";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 5;
            p.stepVal = 1;
            p.type = uInt;
            p.def = 0;
            params[P_FILTER1_TYPE] = p;
            
            p.pid = P_FILTER1_DRIVE;
            p.name = "Filter 1 Drive";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 0;
            params[P_FILTER1_DRIVE] = p;
            
            p.pid = P_FILTER_ARCHITECTURE;
            p.name = "F Architecture";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 1;
            p.type = uInt;
            p.def = 0;
            params[P_FILTER_ARCHITECTURE] = p;
             
            p.pid = P_FILTER2_FREQ;
            p.name = "Filter 2 Freq";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 20;
            p.maxVal = 7000;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 0;
            params[P_FILTER2_FREQ] = p;
            
            p.pid = P_FILTER2_RES;
            p.name = "Filter 2 Res";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1000;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 7000;
            params[P_FILTER2_RES] = p;
            
            p.pid = P_FILTER2_TYPE;
            p.name = "Filter 2 Type";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 5;
            p.stepVal = 1;
            p.type = uInt;
            p.def = 0;
            params[P_FILTER2_TYPE] = p;
            
            p.pid = P_FILTER2_DRIVE;
            p.name = "Filter 2 Drive";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 0;
            params[P_FILTER2_DRIVE] = p;
            
            p.pid = P_ADSR1_DELAY;
            p.name = "ADSR 1 Delay";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 500;
            p.stepVal = 1;
            p.type = uInt;
            p.def = 0;
            params[P_ADSR1_DELAY] = p;
            
            p.pid = P_ADSR1_ATTACK;
            p.name = "ADSR 1 Attack";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 90;
            p.stepVal = 0.1;
            p.type = uFloat;
            p.def = 0;
            params[P_ADSR1_ATTACK] = p;
            
            p.pid = P_ADSR1_DECAY;
            p.name = "ADSR 1 Decay";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 2000;
            p.stepVal = 0.1;
            p.type = uFloat;
            p.def = 0;
            params[P_ADSR1_DECAY] = p;
            
            p.pid = P_ADSR1_SUSTAIN;
            p.name = "ADSR 1 Sustain";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 2000;
            p.stepVal = 0.1;
            p.type = uFloat;
            p.def = 0;
            params[P_ADSR1_SUSTAIN] = p;

            p.pid = P_ADSR1_RELEASE;
            p.name = "ADSR 1 Release";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 2000;
            p.stepVal = 0.1;
            p.type = uFloat;
            p.def = 0;
            params[P_ADSR1_RELEASE] = p;
            
            p.pid = P_ADSR1_FREQ;
            p.name = "ADSR 1 Freq";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 0;
            params[P_ADSR1_FREQ] = p;
            
            p.pid = P_ADSR1_FILT;
            p.name = "ADSR 1 Filter";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 0;
            params[P_ADSR1_FILT] = p;

            p.pid = P_ADSR1_VOL;
            p.name = "ADSR 1 Vol";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 0;
            params[P_ADSR1_VOL] = p;
            
            p.pid = P_ADSR2_DELAY;
            p.name = "ADSR 2 Delay";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 2000;
            p.stepVal = 0.1;
            p.type = uFloat;
            p.def = 0;
            params[P_ADSR2_DELAY] = p;
            
            p.pid = P_ADSR2_ATTACK;
            p.name = "ADSR 2 Attack";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 90;
            p.stepVal = 0.1;
            p.type = uFloat;
            p.def = 0;
            params[P_ADSR2_ATTACK] = p;
            
            p.pid = P_ADSR2_DECAY;
            p.name = "ADSR 2 Decay";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 2000;
            p.stepVal = 0.1;
            p.type = uFloat;
            p.def = 0;
            params[P_ADSR2_DECAY] = p;
            
            p.pid = P_ADSR2_SUSTAIN;
            p.name = "ADSR 2 Sustain";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 2000;
            p.stepVal = 0.1;
            p.type = uFloat;
            p.def = 0;
            params[P_ADSR2_SUSTAIN] = p;

            p.pid = P_ADSR2_RELEASE;
            p.name = "ADSR 2 Release";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 2000;
            p.stepVal = 0.1;
            p.type = uFloat;
            p.def = 0;
            params[P_ADSR2_RELEASE] = p;
            
            p.pid = P_ADSR2_FREQ;
            p.name = "ADSR 2 Freq";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 0;
            params[P_ADSR2_FREQ] = p;
            
            p.pid = P_ADSR2_FILT;
            p.name = "ADSR 2 Filter";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 0;
            params[P_ADSR2_FILT] = p;

            p.pid = P_ADSR2_VOL;
            p.name = "ADSR 2 Vol";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 0;
            params[P_ADSR2_VOL] = p;

            p.pid = P_ADSR3_DELAY;
            p.name = "ADSR 3 Delay";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 2000;
            p.stepVal = 0.1;
            p.type = uFloat;
            p.def = 0;
            params[P_ADSR3_DELAY] = p;
            
            p.pid = P_ADSR3_ATTACK;
            p.name = "ADSR 3 Attack";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 90;
            p.stepVal = 0.1;
            p.type = uFloat;
            p.def = 0;
            params[P_ADSR3_ATTACK] = p;
            
            p.pid = P_ADSR3_DECAY;
            p.name = "ADSR 3 Decay";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 2000;
            p.stepVal = 0.1;
            p.type = uFloat;
            p.def = 0;
            params[P_ADSR3_DECAY] = p;
            
            p.pid = P_ADSR3_SUSTAIN;
            p.name = "ADSR 3 Sustain";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 2000;
            p.stepVal = 0.1;
            p.type = uFloat;
            p.def = 0;
            params[P_ADSR3_SUSTAIN] = p;

            p.pid = P_ADSR3_RELEASE;
            p.name = "ADSR 3 Release";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 2000;
            p.stepVal = 0.1;
            p.type = uFloat;
            p.def = 0;
            params[P_ADSR3_RELEASE] = p;
            
            p.pid = P_ADSR3_FREQ;
            p.name = "ADSR 3 Freq";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 0;
            params[P_ADSR3_FREQ] = p;
            
            p.pid = P_ADSR3_FILT;
            p.name = "ADSR 3 Filter";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 0;
            params[P_ADSR3_FILT] = p;

            p.pid = P_ADSR3_VOL;
            p.name = "ADSR 3 Vol";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 0;
            params[P_ADSR3_VOL] = p;

            p.pid = P_ADSR4_DELAY;
            p.name = "ADSR 4 Delay";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 2000;
            p.stepVal = 0.1;
            p.type = uFloat;
            p.def = 0;
            params[P_ADSR4_DELAY] = p;
            
            p.pid = P_ADSR4_ATTACK;
            p.name = "ADSR 4 Attack";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 90;
            p.stepVal = 0.1;
            p.type = uFloat;
            p.def = 0;
            params[P_ADSR4_ATTACK] = p;
             
            p.pid = P_ADSR4_DECAY;
            p.name = "ADSR 4 Decay";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 2000;
            p.stepVal = 0.1;
            p.type = uFloat;
            p.def = 0;
            params[P_ADSR4_DECAY] = p;

            p.pid = P_ADSR4_SUSTAIN;
            p.name = "ADSR 4 Sustain";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 2000;
            p.stepVal = 0.1;
            p.type = uFloat;
            p.def = 0;
            params[P_ADSR4_SUSTAIN] = p;

            p.pid = P_ADSR4_RELEASE;
            p.name = "ADSR 4 Release";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 2000;
            p.stepVal = 0.1;
            p.type = uFloat;
            p.def = 0;
            params[P_ADSR4_RELEASE] = p;

            p.pid = P_ADSR4_FREQ;
            p.name = "ADSR 4 Freq";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 0;
            params[P_ADSR4_FREQ] = p;

            p.pid = P_ADSR4_FILT;
            p.name = "ADSR 4 Filter";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 0;
            params[P_ADSR4_FILT] = p;

            p.pid = P_ADSR4_VOL;
            p.name = "ADSR 4 Vol";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 0;
            params[P_ADSR4_VOL] = p;
            
            p.pid = P_LFO1_FREQ;
            p.name = "LFO 1 Freq";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0.1;
            p.maxVal = 20;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 0;
            params[P_LFO1_FREQ] = p;
            
            p.pid = P_LFO1_WAV;
            p.name = "LFO 1 Wave";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 5;
            p.stepVal = 1;
            p.type = uInt;
            p.def = 0;
            params[P_LFO1_WAV] = p;
   
            p.pid = P_LFO1_DELAY;
            p.name = "LFO 1 Delay";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 2000;
            p.stepVal = 0.1;
            p.type = uInt;
            p.def = 0;
            params[P_LFO1_DELAY] = p;

            p.pid = P_LFO1_SYNC;
            p.name = "LFO 1 Sync";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 1;
            p.type = uInt;
            p.def = 0;
            params[P_LFO1_SYNC] = p;

            p.pid = P_LFO1_PITCH;
            p.name = "LFO 1 Sync";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 0;
            params[P_LFO1_PITCH] = p;
            
            p.pid = P_LFO1_FILTER;
            p.name = "LFO 1 Filter";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 0;
            params[P_LFO1_FILTER] = p;
            
            p.pid = P_LFO1_VOL;
            p.name = "LFO 1 Vol";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 0;
            params[P_LFO1_VOL] = p;
            
            // LFO2
            p.pid = P_LFO2_FREQ;
            p.name = "LFO 2 Freq";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0.1;
            p.maxVal = 20;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 0;
            params[P_LFO2_FREQ] = p;

            p.pid = P_LFO1_WAV;
            p.name = "LFO 2 Wave";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 5;
            p.stepVal = 1;
            p.type = uInt;
            p.def = 0;
            params[P_LFO2_WAV] = p;

            p.pid = P_LFO1_DELAY;
            p.name = "LFO 2 Delay";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 2000;
            p.stepVal = 0.1;
            p.type = uInt;
            p.def = 0;
            params[P_LFO2_DELAY] = p;

            p.pid = P_LFO2_SYNC;
            p.name = "LFO 2 Sync";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 1;
            p.type = uInt;
            p.def = 0;
            params[P_LFO2_SYNC] = p;

            p.pid = P_LFO2_PITCH;
            p.name = "LFO 2 Sync";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 0;
            params[P_LFO2_PITCH] = p;

            p.pid = P_LFO2_FILTER;
            p.name = "LFO 2 Filter";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 0;
            params[P_LFO2_FILTER] = p;

            p.pid = P_LFO2_VOL;
            p.name = "LFO 2 Vol";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 0;
            params[P_LFO2_VOL] = p;


            
            p.pid = P_PLAYMODE;
            p.name = "PlayMode";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 1;
            p.maxVal = 4;
            p.stepVal = 1;
            p.type = uInt;
            p.def = 1;
            params[P_PLAYMODE] = p;
        }
};

#endif /* ParamBuilder_h */





