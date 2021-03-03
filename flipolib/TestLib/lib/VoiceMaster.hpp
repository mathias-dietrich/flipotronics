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

#include "Def.h"
#include "Hal.hpp"
#include "Renderer.h"
#include "Voice.hpp"

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

class VoiceMaster : Renderer{
   
public:
    Voice  voices[MAXVOICES];
    
    VoiceMaster(int noOfVoicesTotal, int noOfZones){
        this->noOfVoicesTotal = noOfVoicesTotal;
        this->noOfZones = noOfZones;
        
        int nextId = 0;
        for(int y=0;y < MAXVOICES;++y){
            voices[y].id = nextId;
            ++nextId;
        }
        
        renderer = this;
        hal.setup();
    }
    
    void printTime(){
        cout << "Render Time " << ms_renderTime << endl;
    }
    
    void render(SAMPLE * l, SAMPLE * r, int noOfSamples){
        
        // Clear
        memset(l, 0.0, noOfSamples * 4);
        memset(r, 0.0, noOfSamples * 4);

        // Render Voices
        voices[0].render(l,r,  noOfSamples);
        voices[1].render(l,r,   noOfSamples);
        voices[2].render(l,r,   noOfSamples);
        voices[3].render(l,r,    noOfSamples);
        voices[4].render(l,r,    noOfSamples);
        voices[5].render(l,r,    noOfSamples);
        voices[6].render(l,r,    noOfSamples);
        voices[7].render(l,r,    noOfSamples);
        voices[8].render(l,r,   noOfSamples);
        voices[9].render(l,r,    noOfSamples);
        voices[10].render(l,r,    noOfSamples);
        voices[11].render(l,r,    noOfSamples);
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
    void reset();
    void setTuning(float  tuning);
    
    enum VoiceMode voiceMode; //
    enum Algo algo;
    
    int noOfVoicesTotal;
    int noOfZones;
    int PitchWheelMin;
    int PitchWheelMax;
    enum PlayMode playMode; //
    
    Hal hal;
    
    void close(){
        hal.close();
    }
    
private:
    
    int  findVoice(int channel, int midiNote){
            for(int y=0;y < MAXVOICES;y++){
                if(voices[y].channel == channel && voices[y].midiNote ==  midiNote && voices[y].active){
                    std::cout << "reuse" << std::endl;
                    return y;
                }
            }

            for(int y=0;y < MAXVOICES;y++){
                if(!voices[y].active){
                    cout << "next voice" << endl;
                    return y;
                }
            }
        std:cout << "default 0" << endl;
        return 0;// make better
    }
};

#endif /* VoiceMaster_hpp */
