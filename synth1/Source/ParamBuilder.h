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
#define P_EXP_FILTER1 2
#define P_EXP_FILTER2 3
#define P_EXP_RES1 4
#define P_EXP_LFO1 5
#define P_EXP_PORTAMENTO 6
#define P_VOLUME 7
#define P_PITCHWHEELMIN 8
#define P_PITCHWHEELMAX 9
#define P_PAN 10
#define P_MOD_FILTER 11
#define P_MOD_LFO1 12
#define P_MOD_LFO2 13

// Osc
#define P_NOISE_LEVEL 14
#define P_NOISE_TYPE 15
#define P_OSC1_OCT 16
#define P_OSC1_SEMI 17
#define P_OSC1_FINE 18
#define P_OSC1_VOL 19
#define P_OSC1_WAV 20
#define P_OSC1_PULSE 21
#define P_OSC1_PHASE 22
#define P_OSC1_SUB 23

#define P_OSC2_OCT 24
#define P_OSC2_SEMI 25
#define P_OSC2_FINE 26
#define P_OSC2_VOL 27
#define P_OSC2_WAV 28
#define P_OSC2_PULSE 29
#define P_OSC2_PHASE 30
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
#define P_ADSR1_ATTACK 48
#define P_ADSR1_DECAY 49
#define P_ADSR1_SUSTAIN 50
#define P_ADSR1_RELEASE 51
#define P_ADSR1_PITCH 52
#define P_ADSR1_FILTER 53
#define P_ADSR1_AMP 54
#define P_ADSR1_FX 55

#define P_ADSR1_ATTACK_CURVE 56
#define P_ADSR1_DECAY_CURVE 57
#define P_ADSR1_SUSTAIN_CURVE 58
#define P_ADSR1_RELEASE_CURVE 59
#define P_ADSR1_DELAY 60
#define P_ADSR1_HOLD 61
#define P_ADSR1_TRIGGER 62
#define P_ADSR1_TRESHOLD 63

#define P_ADSR2_ATTACK 176
#define P_ADSR2_DECAY 177
#define P_ADSR2_SUSTAIN 178
#define P_ADSR2_RELEASE 179
#define P_ADSR2_PITCH 180
#define P_ADSR2_FILTER 181
#define P_ADSR2_AMP 182
#define P_ADSR2_FX 183

#define P_ADSR2_ATTACK_CURVE 184
#define P_ADSR2_DECAY_CURVE 185
#define P_ADSR2_SUSTAIN_CURVE 186
#define P_ADSR2_RELEASE_CURVE 187
#define P_ADSR2_DELAY 188
#define P_ADSR2_HOLD 189
#define P_ADSR2_TRIGGER 190
#define P_ADSR2_TRESHOLD 191

#define P_ADSR3_ATTACK 64
#define P_ADSR3_DECAY 65
#define P_ADSR3_SUSTAIN 66
#define P_ADSR3_RELEASE 67
#define P_ADSR3_PITCH 68
#define P_ADSR3_FILTER 69
#define P_ADSR3_AMP 70
#define P_ADSR3_FX 71

#define P_ADSR3_ATTACK_CURVE 72
#define P_ADSR3_DECAY_CURVE 73
#define P_ADSR3_SUSTAIN_CURVE 74
#define P_ADSR3_RELEASE_CURVE 75
#define P_ADSR3_DELAY 76
#define P_ADSR3_HOLD 77
#define P_ADSR3_TRIGGER 78
#define P_ADSR3_TRESHOLD 79

#define P_ADSR4_ATTACK 192
#define P_ADSR4_DECAY 193
#define P_ADSR4_SUSTAIN 194
#define P_ADSR4_RELEASE 195
#define P_ADSR4_PITCH 196
#define P_ADSR4_FILTER 197
#define P_ADSR4_AMP 198
#define P_ADSR4_FX 199

#define P_ADSR4_ATTACK_CURVE 200
#define P_ADSR4_DECAY_CURVE 201
#define P_ADSR4_SUSTAIN_CURVE 202
#define P_ADSR4_RELEASE_CURVE 203
#define P_ADSR4_DELAY 204
#define P_ADSR4_HOLD 205
#define P_ADSR4_TRIGGER 206
#define P_ADSR4_TRESHOLD 207

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

#define P_LFO3_FREQ 208
#define P_LFO3_WAV 209
#define P_LFO3_DELAY 210
#define P_LFO3_SYNC 211
#define P_LFO3_PITCH 212
#define P_LFO3_FILTER 213
#define P_LFO3_VOL 214
#define P_LFO3_ 215

#define P_LFO4_FREQ 216
#define P_LFO4_WAV 217
#define P_LFO4_DELAY 218
#define P_LFO4_SYNC 219
#define P_LFO4_PITCH 220
#define P_LFO4_FILTER 221
#define P_LFO4_VOL 222
#define P_LFO4_ 223


#define P_ARP_BPM 768 // BPM
#define P_ARP_DEVISION 769 //  1/1-Note, 1/2-Note, 1/4-Note, 1/8-Note, 1/16-Note, 1/32-Note, and 1/64-Note
#define P_ARP_LEGATO 770 //  1/1-Note, 1/2-Note, 1/4-Note, 1/8-Note, 1/16-Note, 1/32-Note, and 1/64-Note
#define P_ARP_GATE 771 // +- %
#define P_ARP_VELOCITY 772 // 0-127
#define P_ARP_CHORD 773 // SINGLE QUINT QUART ROOT INV1 INV2
#define P_ARP_SWING 774 // 50 - 71
#define P_ARP_MODE 775  // SEQ - ARP

#define P_ARP_NOTE1 776
#define P_ARP_NOTE2 777
#define P_ARP_NOTE3 778
#define P_ARP_NOTE4 779
#define P_ARP_NOTE5 780
#define P_ARP_NOTE6 781
#define P_ARP_NOTE7 782
#define P_ARP_NOTE8 783

#define P_ARP_NOTECOUNT 896
#define P_ARP_TRANSPOSE 897

#define P_ARP_NOTE9 904
#define P_ARP_NOTE10 905
#define P_ARP_NOTE11 906
#define P_ARP_NOTE12 907
#define P_ARP_NOTE13 908
#define P_ARP_NOTE14 909
#define P_ARP_NOTE15 910
#define P_ARP_NOTE16 911


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
            p0.smoothTime = 0;
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
            
            p.pid = P_EXP_FILTER1;
            p.name = "Exp Filter 1";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 0;
            params[P_EXP_FILTER1] = p;
            
            p.pid = P_EXP_FILTER2;
            p.name = "Exp Filter 2";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 0;
            params[P_EXP_FILTER2] = p;
            
            p.pid = P_EXP_RES1;
            p.name = "Exp Res 1";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 0;
            params[P_EXP_RES1] = p;
            
            p.pid = P_EXP_LFO1;
            p.name = "Exp Lfo 1";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 0;
            params[P_EXP_LFO1] = p;
            
            p.pid = P_EXP_PORTAMENTO;
            p.name = "Portamento";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1000;
            p.stepVal = 1;
            p.type = uTimeMsec;
            p.def = 0;
            params[P_EXP_PORTAMENTO] = p;
            
            p.pid = P_VOLUME;
            p.name = "Volume";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = -96;
            p.maxVal = 0;
            p.stepVal = 0.01;
            p.type = uDb;
            p.def = 0;
           
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
            
            p.pid = P_PITCHWHEELMIN;
            p.name = "PitchWheel Min";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 12;
            p.stepVal = 1;
            p.type = uInt;
            p.def = 5;
            params[P_PITCHWHEELMIN] = p;
            
            p.pid = P_PITCHWHEELMAX;
            p.name = "PitchWheel Max";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 12;
            p.stepVal = 1;
            p.type = uInt;
            p.def = 7;
            params[P_PITCHWHEELMAX] = p;
            
            p.pid = P_MOD_FILTER;
            p.name = "Mod Filter";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 0.1;
            p.type = uFloat;
            p.def = 0;
            params[P_MOD_FILTER] = p;
            
            p.pid = P_MOD_LFO1;
            p.name = "Mod LFO 1";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 0.1;
            p.type = uFloat;
            p.def = 0;
            params[P_MOD_LFO1] = p;
            
            p.pid = P_MOD_LFO2;
            p.name = "Mod LFO 2";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 0.1;
            p.type = uFloat;
            p.def = 0;
            params[P_MOD_LFO2] = p;
            
            p.pid = P_NOISE_LEVEL;
            p.name = "Noise Level";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 0;
            params[P_NOISE_LEVEL] = p;
            
            p.pid = P_NOISE_TYPE;
            p.name = "Noise Type";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 2;
            p.stepVal = 0.01;
            p.type = uInt;
            p.def = 0;
            params[P_NOISE_TYPE] = p;

            // OSC 1
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
            p.stepVal = 0.1;
            p.type = uFloat;
            p.def = 0;
            params[P_OSC1_FINE] = p;
            
            p.pid = P_OSC1_VOL;
            p.name = "Osc1 Vol";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = -96;
            p.maxVal = 0;
            p.stepVal = 0.01;
            p.type = uDb;
            p.def = 0;
            params[P_OSC1_VOL] = p;
            
            p.pid = P_OSC1_WAV;
            p.name = "Osc1 Wav";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 8;
            p.stepVal = 1;
            p.type =  uWaveType;
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
            
            p.pid = P_OSC1_PHASE;
            p.name = "Osc1 Phase";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 358;
            p.stepVal = 0.01;
            p.type = uPhase;
            p.def = 0.0;
            params[P_OSC1_PHASE] = p;
            
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
            p.stepVal = 0.1;
            p.type = uFloat;
            p.def = 0;
            params[P_OSC2_FINE] = p;
            
            p.pid = P_OSC2_VOL;
            p.name = "Osc2 Vol";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = -96;
            p.maxVal = 0;
            p.stepVal = 0.01;
            p.type = uDb;
            p.def = 0;
            params[P_OSC2_VOL] = p;
            
            p.pid = P_OSC2_WAV;
            p.name = "Osc2 Wav";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 8;
            p.stepVal = 1;
            p.type =  uWaveType;
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
            
            p.pid = P_OSC2_PHASE;
            p.name = "Osc2 Phase";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 358;
            p.stepVal = 0.01;
            p.type = uPhase;
            p.def = 0.0;
            params[P_OSC2_PHASE] = p;
            
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
            p.minVal = 40;
            p.maxVal = 7000;
            p.stepVal = 1;
            p.type = uHZ;
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
            p.minVal = 1;
            p.maxVal = 14;
            p.stepVal = 1;
            p.type = uInt;
            p.def = 1;
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
            p.minVal = 40;
            p.maxVal = 7000;
            p.stepVal = 1.0f;
            p.type = uHZ;
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
            p.minVal = 1;
            p.maxVal = 14;
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
            
            // ADSR
            p.pid = P_ADSR1_ATTACK;
            p.name = "ADSR 1 Attack";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 1;
            p.maxVal = 10000;
            p.stepVal = 1;
            p.type = uTimeMsec;
            p.def = 0;
            params[P_ADSR1_ATTACK] = p;
            
            p.pid = P_ADSR1_DECAY;
            p.name = "ADSR 1 Decay";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 1;
            p.maxVal = 10000;
            p.stepVal = 1;
            p.type = uTimeMsec;
            p.def = 0;
            params[P_ADSR1_DECAY] = p;
            
            p.pid = P_ADSR1_SUSTAIN;
            p.name = "ADSR 1 Sustain";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 0;
            params[P_ADSR1_SUSTAIN] = p;
            
            p.pid = P_ADSR1_RELEASE;
            p.name = "ADSR 1 Release";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 1;
            p.maxVal = 10000;
            p.stepVal = 0.1;
            p.type = uTimeMsec;
            p.def = 0;
            params[P_ADSR1_RELEASE] = p;
            
            p.pid = P_ADSR1_PITCH;
            p.name = "ADSR 1 Pitch";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 0;
            params[P_ADSR1_PITCH] = p;
            
            p.pid = P_ADSR1_FILTER;
            p.name = "ADSR 1 Filter";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 0;
            params[P_ADSR1_FILTER] = p;

            p.pid = P_ADSR1_AMP;
            p.name = "ADSR 1 Amp";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 0;
            params[P_ADSR1_AMP] = p;
            
            p.pid = P_ADSR1_FX;
            p.name = "ADSR 1 FX";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 0;
            params[P_ADSR1_FX] = p;

            p.pid = P_ADSR1_ATTACK_CURVE;
            p.name = "ADSR 1 Att C";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = -100;
            p.maxVal = 100;
            p.stepVal = 1;
            p.type = uCurve;
            p.def = 0;
            params[P_ADSR1_ATTACK_CURVE] = p;
            
            p.pid = P_ADSR1_DECAY_CURVE;
            p.name = "ADSR 1 Dec C";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = -100;
            p.maxVal = 100;
            p.stepVal = 1;
            p.type = uCurve;
            p.def = 0;
            params[P_ADSR1_DECAY_CURVE] = p;
            
            p.pid = P_ADSR1_SUSTAIN_CURVE;
            p.name = "ADSR 1 Sus C";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = -100;
            p.maxVal = 100;
            p.stepVal = 1;
            p.type = uCurve;
            p.def = 0;
            params[P_ADSR1_SUSTAIN_CURVE] = p;

            p.pid = P_ADSR1_RELEASE_CURVE;
            p.name = "ADSR 1 Rel C";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = -100;
            p.maxVal = 100;
            p.stepVal = 1;
            p.type = uCurve;
            p.def = 0;
            params[P_ADSR1_RELEASE_CURVE] = p;
            
            p.pid = P_ADSR1_DELAY;
            p.name = "ADSR 1 Delay";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 10000;
            p.stepVal = 1;
            p.type = uTimeMsec;
            p.def = 0;
            params[P_ADSR1_DELAY] = p;
            
            p.pid = P_ADSR1_HOLD;
            p.name = "ADSR 1 Hold";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 10000;
            p.stepVal = 1;
            p.type = uTimeMsec;
            p.def = 0;
            params[P_ADSR1_HOLD] = p;

            p.pid = P_ADSR1_TRIGGER;
            p.name = "ADSR 1 Trigger";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 0;
            params[P_ADSR1_TRIGGER] = p;
            
            p.pid = P_ADSR1_TRESHOLD;
            p.name = "ADSR 1 Tresh";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 0;
            params[ P_ADSR1_TRESHOLD] = p;
            
            // ADSR 2
            p.pid = P_ADSR2_ATTACK;
            p.name = "ADSR 2 Attack";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 1;
            p.maxVal = 10000;
            p.stepVal = 1;
            p.type = uTimeMsec;
            p.def = 0;
            params[P_ADSR2_ATTACK] = p;
            
            p.pid = P_ADSR2_DECAY;
            p.name = "ADSR 2 Decay";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 1;
            p.maxVal = 10000;
            p.stepVal = 1;
            p.type = uTimeMsec;
            p.def = 0;
            params[P_ADSR2_DECAY] = p;
            
            p.pid = P_ADSR2_SUSTAIN;
            p.name = "ADSR 2 Sustain";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 0;
            params[P_ADSR2_SUSTAIN] = p;
            
            p.pid = P_ADSR2_RELEASE;
            p.name = "ADSR 2 Release";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 1;
            p.maxVal = 10000;
            p.stepVal = 0.1;
            p.type = uTimeMsec;
            p.def = 0;
            params[P_ADSR2_RELEASE] = p;
            
            p.pid = P_ADSR2_PITCH;
            p.name = "ADSR 2 Pitch";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 0;
            params[P_ADSR2_PITCH] = p;
            
            p.pid = P_ADSR2_FILTER;
            p.name = "ADSR 2 Filter";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 0;
            params[P_ADSR2_FILTER] = p;

            p.pid = P_ADSR2_AMP;
            p.name = "ADSR 2 Amp";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 0;
            params[P_ADSR2_AMP] = p;
            
            p.pid = P_ADSR2_FX;
            p.name = "ADSR 2 FX";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 0;
            params[P_ADSR2_FX] = p;

            p.pid = P_ADSR2_ATTACK_CURVE;
            p.name = "ADSR 2 Att C";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = -100;
            p.maxVal = 100;
            p.stepVal = 1;
            p.type = uCurve;
            p.def = 0;
            params[P_ADSR2_ATTACK_CURVE] = p;
            
            p.pid = P_ADSR2_DECAY_CURVE;
            p.name = "ADSR 2 Dec C";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = -100;
            p.maxVal = 100;
            p.stepVal = 1;
            p.type = uCurve;
            p.def = 0;
            params[P_ADSR2_DECAY_CURVE] = p;
            
            p.pid = P_ADSR2_SUSTAIN_CURVE;
            p.name = "ADSR 2 Sus C";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = -100;
            p.maxVal = 100;
            p.stepVal = 1;
            p.type = uCurve;
            p.def = 0;
            params[P_ADSR2_SUSTAIN_CURVE] = p;

            p.pid = P_ADSR2_RELEASE_CURVE;
            p.name = "ADSR 2 Rel C";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = -100;
            p.maxVal = 100;
            p.stepVal = 1;
            p.type = uCurve;
            p.def = 0;
            params[P_ADSR2_RELEASE_CURVE] = p;
            
            p.pid = P_ADSR2_DELAY;
            p.name = "ADSR 2 Delay";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 10000;
            p.stepVal = 1;
            p.type = uTimeMsec;
            p.def = 0;
            params[P_ADSR2_DELAY] = p;
            
            p.pid = P_ADSR2_HOLD;
            p.name = "ADSR 2 Hold";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 10000;
            p.stepVal = 1;
            p.type = uTimeMsec;
            p.def = 0;
            params[P_ADSR2_HOLD] = p;

            p.pid = P_ADSR2_TRIGGER;
            p.name = "ADSR 2 Trigger";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 0;
            params[P_ADSR2_TRIGGER] = p;
            
            p.pid = P_ADSR2_TRESHOLD;
            p.name = "ADSR 2 Tresh";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 0;
            params[ P_ADSR2_TRESHOLD] = p;
            
            // ADSR 3
            p.pid = P_ADSR3_ATTACK;
            p.name = "ADSR 3 Attack";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 1;
            p.maxVal = 10000;
            p.stepVal = 1;
            p.type = uTimeMsec;
            p.def = 0;
            params[P_ADSR3_ATTACK] = p;
            
            p.pid = P_ADSR3_DECAY;
            p.name = "ADSR 3 Decay";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 1;
            p.maxVal = 10000;
            p.stepVal = 1;
            p.type = uTimeMsec;
            p.def = 0;
            params[P_ADSR3_DECAY] = p;
            
            p.pid = P_ADSR3_SUSTAIN;
            p.name = "ADSR 3 Sustain";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 0;
            params[P_ADSR3_SUSTAIN] = p;
            
            p.pid = P_ADSR3_RELEASE;
            p.name = "ADSR 3 Release";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 1;
            p.maxVal = 10000;
            p.stepVal = 0.1;
            p.type = uTimeMsec;
            p.def = 0;
            params[P_ADSR3_RELEASE] = p;
            
            p.pid = P_ADSR3_PITCH;
            p.name = "ADSR 3 Pitch";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 0;
            params[P_ADSR3_PITCH] = p;
            
            p.pid = P_ADSR3_FILTER;
            p.name = "ADSR 3 Filter";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 0;
            params[P_ADSR3_FILTER] = p;

            p.pid = P_ADSR3_AMP;
            p.name = "ADSR 3 Amp";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 0;
            params[P_ADSR3_AMP] = p;
            
            p.pid = P_ADSR3_FX;
            p.name = "ADSR 3 FX";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 0;
            params[P_ADSR3_FX] = p;

            p.pid = P_ADSR3_ATTACK_CURVE;
            p.name = "ADSR 3 Att C";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = -100;
            p.maxVal = 100;
            p.stepVal = 1;
            p.type = uCurve;
            p.def = 0;
            params[P_ADSR3_ATTACK_CURVE] = p;
            
            p.pid = P_ADSR3_DECAY_CURVE;
            p.name = "ADSR 3 Dec C";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = -100;
            p.maxVal = 100;
            p.stepVal = 1;
            p.type = uCurve;
            p.def = 0;
            params[P_ADSR3_DECAY_CURVE] = p;
            
            p.pid = P_ADSR3_SUSTAIN_CURVE;
            p.name = "ADSR 3 Sus C";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = -100;
            p.maxVal = 100;
            p.stepVal = 1;
            p.type = uCurve;
            p.def = 0;
            params[P_ADSR3_SUSTAIN_CURVE] = p;

            p.pid = P_ADSR3_RELEASE_CURVE;
            p.name = "ADSR 3 Rel C";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = -100;
            p.maxVal = 100;
            p.stepVal = 1;
            p.type = uCurve;
            p.def = 0;
            params[P_ADSR3_RELEASE_CURVE] = p;
            
            p.pid = P_ADSR3_DELAY;
            p.name = "ADSR 3 Delay";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 10000;
            p.stepVal = 1;
            p.type = uTimeMsec;
            p.def = 0;
            params[P_ADSR3_DELAY] = p;
            
            p.pid = P_ADSR3_HOLD;
            p.name = "ADSR 3 Hold";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 10000;
            p.stepVal = 1;
            p.type = uTimeMsec;
            p.def = 0;
            params[P_ADSR3_HOLD] = p;

            p.pid = P_ADSR3_TRIGGER;
            p.name = "ADSR 3 Trigger";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 0;
            params[P_ADSR3_TRIGGER] = p;
            
            p.pid = P_ADSR3_TRESHOLD;
            p.name = "ADSR 3 Tresh";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 0;
            params[ P_ADSR3_TRESHOLD] = p;
            
            // ADSR 4
            p.pid = P_ADSR4_ATTACK;
            p.name = "ADSR 4 Attack";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 1;
            p.maxVal = 10000;
            p.stepVal = 1;
            p.type = uTimeMsec;
            p.def = 0;
            params[P_ADSR4_ATTACK] = p;
            
            p.pid = P_ADSR2_DECAY;
            p.name = "ADSR 4 Decay";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 1;
            p.maxVal = 10000;
            p.stepVal = 1;
            p.type = uTimeMsec;
            p.def = 0;
            params[P_ADSR4_DECAY] = p;
            
            p.pid = P_ADSR4_SUSTAIN;
            p.name = "ADSR 4 Sustain";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 0;
            params[P_ADSR4_SUSTAIN] = p;
            
            p.pid = P_ADSR4_RELEASE;
            p.name = "ADSR 4 Release";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 1;
            p.maxVal = 10000;
            p.stepVal = 0.1;
            p.type = uTimeMsec;
            p.def = 0;
            params[P_ADSR4_RELEASE] = p;
            
            p.pid = P_ADSR4_PITCH;
            p.name = "ADSR 4 Pitch";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 0;
            params[P_ADSR4_PITCH] = p;
            
            p.pid = P_ADSR4_FILTER;
            p.name = "ADSR 4 Filter";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 0;
            params[P_ADSR4_FILTER] = p;

            p.pid = P_ADSR4_AMP;
            p.name = "ADSR 4 Amp";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 0;
            params[P_ADSR4_AMP] = p;
            
            p.pid = P_ADSR4_FX;
            p.name = "ADSR 4 FX";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 0;
            params[P_ADSR4_FX] = p;

            p.pid = P_ADSR4_ATTACK_CURVE;
            p.name = "ADSR 4 Att C";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = -100;
            p.maxVal = 100;
            p.stepVal = 1;
            p.type = uCurve;
            p.def = 0;
            params[P_ADSR4_ATTACK_CURVE] = p;
            
            p.pid = P_ADSR4_DECAY_CURVE;
            p.name = "ADSR 4 Dec C";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = -100;
            p.maxVal = 100;
            p.stepVal = 1;
            p.type = uCurve;
            p.def = 0;
            params[P_ADSR4_DECAY_CURVE] = p;
            
            p.pid = P_ADSR4_SUSTAIN_CURVE;
            p.name = "ADSR 4 Sus C";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = -100;
            p.maxVal = 100;
            p.stepVal = 1;
            p.type = uCurve;
            p.def = 0;
            params[P_ADSR4_SUSTAIN_CURVE] = p;

            p.pid = P_ADSR4_RELEASE_CURVE;
            p.name = "ADSR 4 Rel C";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = -100;
            p.maxVal = 100;
            p.stepVal = 1;
            p.type = uCurve;
            p.def = 0;
            params[P_ADSR4_RELEASE_CURVE] = p;
            
            p.pid = P_ADSR4_DELAY;
            p.name = "ADSR 4 Delay";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 10000;
            p.stepVal = 1;
            p.type = uTimeMsec;
            p.def = 0;
            params[P_ADSR4_DELAY] = p;
            
            p.pid = P_ADSR4_HOLD;
            p.name = "ADSR 4 Hold";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 10000;
            p.stepVal = 1;
            p.type = uTimeMsec;
            p.def = 0;
            params[P_ADSR4_HOLD] = p;

            p.pid = P_ADSR4_TRIGGER;
            p.name = "ADSR 4 Trigger";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 0;
            params[P_ADSR4_TRIGGER] = p;
            
            p.pid = P_ADSR4_TRESHOLD;
            p.name = "ADSR 4 Tresh";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 0.01;
            p.type = uFloat;
            p.def = 0;
            params[ P_ADSR4_TRESHOLD] = p;
            
            // LFO
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
            p.maxVal = 3;
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
            p.name = "LFO 1 Pitch";
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
            p.maxVal = 3;
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
            p.name = "LFO 2 Pitch";
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
            
            // LFO 3
             p.pid = P_LFO3_FREQ;
             p.name = "LFO 3 Freq";
             p.writeable = 1;
             p.automate = 1;
             p.minVal = 0.1;
             p.maxVal = 20;
             p.stepVal = 0.01;
             p.type = uFloat;
             p.def = 0;
             params[P_LFO3_FREQ] = p;
             
             p.pid = P_LFO3_WAV;
             p.name = "LFO 3 Wave";
             p.writeable = 1;
             p.automate = 1;
             p.minVal = 0;
             p.maxVal = 3;
             p.stepVal = 1;
             p.type = uInt;
             p.def = 0;
             params[P_LFO3_WAV] = p;
    
             p.pid = P_LFO3_DELAY;
             p.name = "LFO 3 Delay";
             p.writeable = 1;
             p.automate = 1;
             p.minVal = 0;
             p.maxVal = 2000;
             p.stepVal = 0.1;
             p.type = uInt;
             p.def = 0;
             params[P_LFO3_DELAY] = p;

             p.pid = P_LFO3_SYNC;
             p.name = "LFO 3 Sync";
             p.writeable = 1;
             p.automate = 1;
             p.minVal = 0;
             p.maxVal = 1;
             p.stepVal = 1;
             p.type = uInt;
             p.def = 0;
             params[P_LFO3_SYNC] = p;

             p.pid = P_LFO3_PITCH;
             p.name = "LFO 3 Pitch";
             p.writeable = 1;
             p.automate = 1;
             p.minVal = 0;
             p.maxVal = 1;
             p.stepVal = 0.01;
             p.type = uFloat;
             p.def = 0;
             params[P_LFO3_PITCH] = p;
             
             p.pid = P_LFO3_FILTER;
             p.name = "LFO 3 Filter";
             p.writeable = 1;
             p.automate = 1;
             p.minVal = 0;
             p.maxVal = 1;
             p.stepVal = 0.01;
             p.type = uFloat;
             p.def = 0;
             params[P_LFO3_FILTER] = p;
             
             p.pid = P_LFO3_VOL;
             p.name = "LFO 3 Vol";
             p.writeable = 1;
             p.automate = 1;
             p.minVal = 0;
             p.maxVal = 1;
             p.stepVal = 0.01;
             p.type = uFloat;
             p.def = 0;
             params[P_LFO3_VOL] = p;
             
             // LFO4
             p.pid = P_LFO4_FREQ;
             p.name = "LFO 4 Freq";
             p.writeable = 1;
             p.automate = 1;
             p.minVal = 0.1;
             p.maxVal = 20;
             p.stepVal = 0.01;
             p.type = uFloat;
             p.def = 0;
             params[P_LFO4_FREQ] = p;

             p.pid = P_LFO4_WAV;
             p.name = "LFO 4 Wave";
             p.writeable = 1;
             p.automate = 1;
             p.minVal = 0;
             p.maxVal = 3;
             p.stepVal = 1;
             p.type = uInt;
             p.def = 0;
             params[P_LFO4_WAV] = p;

             p.pid = P_LFO4_DELAY;
             p.name = "LFO 4 Delay";
             p.writeable = 1;
             p.automate = 1;
             p.minVal = 0;
             p.maxVal = 2000;
             p.stepVal = 0.1;
             p.type = uInt;
             p.def = 0;
             params[P_LFO4_DELAY] = p;

             p.pid = P_LFO4_SYNC;
             p.name = "LFO 4 Sync";
             p.writeable = 1;
             p.automate = 1;
             p.minVal = 0;
             p.maxVal = 1;
             p.stepVal = 1;
             p.type = uInt;
             p.def = 0;
             params[P_LFO4_SYNC] = p;

             p.pid = P_LFO4_PITCH;
             p.name = "LFO 4 Pitch";
             p.writeable = 1;
             p.automate = 1;
             p.minVal = 0;
             p.maxVal = 1;
             p.stepVal = 0.01;
             p.type = uFloat;
             p.def = 0;
             params[P_LFO4_PITCH] = p;

             p.pid = P_LFO4_FILTER;
             p.name = "LFO 4 Filter";
             p.writeable = 1;
             p.automate = 1;
             p.minVal = 0;
             p.maxVal = 1;
             p.stepVal = 0.01;
             p.type = uFloat;
             p.def = 0;
             params[P_LFO4_FILTER] = p;

             p.pid = P_LFO4_VOL;
             p.name = "LFO 4 Vol";
             p.writeable = 1;
             p.automate = 1;
             p.minVal = 0;
             p.maxVal = 1;
             p.stepVal = 0.01;
             p.type = uFloat;
             p.def = 0;
             params[P_LFO4_VOL] = p;

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
            
            p.pid = P_ARP_BPM;
            p.name = "Arp BPM";
            p.writeable = 1;
            p.automate = 0;
            p.minVal = 40;
            p.maxVal = 240;
            p.stepVal = 0.1;
            p.type = uFloat;
            p.def = 120;
            params[P_ARP_BPM] = p;
            
          p.pid = P_ARP_DEVISION;
           p.name = "Arp Devision";
           p.writeable = 1;
           p.automate = 0;
           p.minVal = 0;
           p.maxVal = 12;
           p.stepVal = 1;
           p.type = uDevision;
           p.def = 0;
           params[P_ARP_DEVISION] = p;
            
            p.pid = P_ARP_LEGATO;
            p.name = "Arp Legato";
            p.writeable = 1;
            p.automate = 0;
            p.minVal = 0;
            p.maxVal = 1;
            p.stepVal = 1;
            p.type = uInt;
            p.def = 0;
            params[P_ARP_LEGATO] = p;
            
            p.pid = P_ARP_GATE;
            p.name = "Arp Gate";
            p.writeable = 1;
            p.automate = 0;
            p.minVal = 1;
            p.maxVal = 100;
            p.stepVal = 1;
            p.type = uProcent;
            p.def = 100;
            params[P_ARP_GATE] = p;
            
            p.pid = P_ARP_VELOCITY;
            p.name = "Arp Velocity";
            p.writeable = 1;
            p.automate = 0;
            p.minVal = 0;
            p.maxVal = 127;
            p.stepVal = 1;
            p.type = uInt;
            p.def = 0;
            params[P_ARP_VELOCITY] = p;
            
            p.pid = P_ARP_CHORD;
            p.name = "Arp Chord";
            p.writeable = 1;
            p.automate = 0;
            p.minVal = 0;
            p.maxVal = 5;
            p.stepVal = 1;
            p.type = uChordMode;
            p.def = 0;
            params[P_ARP_CHORD] = p;
            
            p.pid = P_ARP_SWING;
            p.name = "Arp Swing";
            p.writeable = 1;
            p.automate = 0;
            p.minVal = -28;
            p.maxVal = 71;
            p.stepVal = 1;
            p.type = uFloat;
            p.def = 50;
            params[P_ARP_SWING] = p;
            
            p.pid = P_ARP_MODE;
            p.name = "Arp Mode";
            p.writeable = 1;
            p.automate = 0;
            p.minVal = 0;
            p.maxVal = 2;
            p.stepVal = 1;
            p.type = uArpMode;
            p.def = 0;
            params[P_ARP_MODE] = p;
            
            p.pid = P_ARP_TRANSPOSE;
            p.name = "Arp Transpose";
            p.writeable = 1;
            p.automate = 0;
            p.minVal = -36;
            p.maxVal = 36;
            p.stepVal = 1;
            p.type = uInt;
            p.def = 0;
            params[P_ARP_TRANSPOSE] = p;
            
            p.pid = P_ARP_NOTE1;
            p.name = "Arp Note 1";
            p.writeable = 1;
            p.automate = 0;
            p.minVal = 0;
            p.maxVal = 127;
            p.stepVal = 1;
            p.type = uMidiNote;
            p.def = 0;
            params[P_ARP_NOTE1] = p;
            
            p.pid = P_ARP_NOTE2;
            p.name = "Arp Note 2";
            p.writeable = 1;
            p.automate = 0;
            p.minVal = 0;
            p.maxVal = 127;
            p.stepVal = 1;
            p.type = uMidiNote;
            p.def = 0;
            params[P_ARP_NOTE2] = p;
            
            p.pid = P_ARP_NOTE3;
            p.name = "Arp Note 3";
            p.writeable = 1;
            p.automate = 0;
            p.minVal = 0;
            p.maxVal = 127;
            p.stepVal = 1;
            p.type = uMidiNote;
            p.def = 0;
            params[P_ARP_NOTE3] = p;
            
            p.pid = P_ARP_NOTE4;
            p.name = "Arp Note 4";
            p.writeable = 1;
            p.automate = 0;
            p.minVal = 0;
            p.maxVal = 127;
            p.stepVal = 1;
            p.type = uMidiNote;
            p.def = 0;
            params[P_ARP_NOTE4] = p;
            
            p.pid = P_ARP_NOTE5;
            p.name = "Arp Note 5";
            p.writeable = 1;
            p.automate = 0;
            p.minVal = 0;
            p.maxVal = 127;
            p.stepVal = 1;
            p.type = uMidiNote;
            p.def = 0;
            params[P_ARP_NOTE5] = p;
            
            p.pid = P_ARP_NOTE6;
            p.name = "Arp Note 6";
            p.writeable = 1;
            p.automate = 0;
            p.minVal = 0;
            p.maxVal = 127;
            p.stepVal = 1;
            p.type = uMidiNote;
            p.def = 0;
            params[P_ARP_NOTE6] = p;
            
            p.pid = P_ARP_NOTE7;
            p.name = "Arp Note 7";
            p.writeable = 1;
            p.automate = 0;
            p.minVal = 0;
            p.maxVal = 127;
            p.stepVal = 1;
            p.type =  uMidiNote;
            p.def = 0;
            params[P_ARP_NOTE7] = p;
            
            p.pid = P_ARP_NOTE8;
            p.name = "Arp Note 8";
            p.writeable = 1;
            p.automate = 0;
            p.minVal = 0;
            p.maxVal = 127;
            p.stepVal = 1;
            p.type = uMidiNote;
            p.def = 0;
            params[P_ARP_NOTE8] = p;
            
            p.pid = P_ARP_NOTECOUNT;
            p.name = "Arp Note Count";
            p.writeable = 1;
            p.automate = 0;
            p.minVal = 0;
            p.maxVal = 16;
            p.stepVal = 1;
            p.type = uInt;
            p.def = 0;
            params[P_ARP_NOTECOUNT] = p;
            
            p.pid = P_ARP_NOTE9;
            p.name = "Arp Note 9";
            p.writeable = 1;
            p.automate = 0;
            p.minVal = 0;
            p.maxVal = 127;
            p.stepVal = 1;
            p.type = uMidiNote;
            p.def = 0;
            params[P_ARP_NOTE9] = p;
            
            p.pid = P_ARP_NOTE10;
            p.name = "Arp Note 10";
            p.writeable = 1;
            p.automate = 0;
            p.minVal = 0;
            p.maxVal = 127;
            p.stepVal = 1;
            p.type = uMidiNote;
            p.def = 0;
            params[P_ARP_NOTE10] = p;
            
            p.pid = P_ARP_NOTE11;
            p.name = "Arp Note 11";
            p.writeable = 1;
            p.automate = 0;
            p.minVal = 0;
            p.maxVal = 127;
            p.stepVal = 1;
            p.type = uMidiNote;
            p.def = 0;
            params[P_ARP_NOTE11] = p;
            
            p.pid = P_ARP_NOTE12;
            p.name = "Arp Note 12";
            p.writeable = 1;
            p.automate = 0;
            p.minVal = 0;
            p.maxVal = 127;
            p.stepVal = 1;
            p.type = uMidiNote;
            p.def = 0;
            params[P_ARP_NOTE12] = p;
            
            p.pid = P_ARP_NOTE13;
            p.name = "Arp Note 13";
            p.writeable = 1;
            p.automate = 0;
            p.minVal = 0;
            p.maxVal = 127;
            p.stepVal = 1;
            p.type = uMidiNote;
            p.def = 0;
            params[P_ARP_NOTE13] = p;
            
            p.pid = P_ARP_NOTE14;
            p.name = "Arp Note 14";
            p.writeable = 1;
            p.automate = 0;
            p.minVal = 0;
            p.maxVal = 127;
            p.stepVal = 1;
            p.type = uMidiNote;
            p.def = 0;
            params[P_ARP_NOTE14] = p;
            
            p.pid = P_ARP_NOTE15;
            p.name = "Arp Note 15";
            p.writeable = 1;
            p.automate = 0;
            p.minVal = 0;
            p.maxVal = 127;
            p.stepVal = 1;
            p.type =  uMidiNote;
            p.def = 0;
            params[P_ARP_NOTE15] = p;
            
            p.pid = P_ARP_NOTE16;
            p.name = "Arp Note 16";
            p.writeable = 1;
            p.automate = 0;
            p.minVal = 0;
            p.maxVal = 127;
            p.stepVal = 1;
            p.type = uMidiNote;
            p.def = 0;
            params[P_ARP_NOTE16] = p;
            
            // Curvetest
            p.pid = 1022;
            p.name = "curve";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = -100;
            p.maxVal = 100;
            p.stepVal = 1;
            p.type = uMidiNote;
            p.def = 0;
            params[1022] = p;
        }
};

#endif /* ParamBuilder_h */





