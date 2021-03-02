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

#include "Hal.hpp"
#include "Renderer.h"

#define SAMPLE_RATE 44100
#define M_TAU 2.0 * M_PI

#define MAXVOICES 12
#define MAXZONES 1

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
    
    Voice  voices[MAXVOICES];
    
public:

    
    VoiceMaster(int noOfVoicesTotal, int noOfZones){
        this->noOfVoicesTotal = noOfVoicesTotal;
        this->noOfZones = noOfZones;
        
        int nextId = 0;
        for(int y=0;y < MAXVOICES;++y){
            voices[y].id = nextId;
            ++nextId;
        }
        
        hal = new Hal();
        renderer = this;
        hal->setup();
    }
    
    void render( AudioBufferList *ioData, int inNumberFrames){
        
        // Clear
        memset(ioData->mBuffers[0].mData, 0, ioData->mBuffers[1].mDataByteSize);
        
        voices[0].render(ioData,  inNumberFrames);
        voices[1].render(ioData,  inNumberFrames);
        voices[2].render(ioData,  inNumberFrames);
        voices[3].render(ioData,  inNumberFrames);
        voices[4].render(ioData,  inNumberFrames);
        voices[5].render(ioData,  inNumberFrames);
        voices[6].render(ioData,  inNumberFrames);
        voices[7].render(ioData,  inNumberFrames);
        voices[8].render(ioData,  inNumberFrames);
        voices[9].render(ioData,  inNumberFrames);
        voices[10].render(ioData,  inNumberFrames);
        voices[11].render(ioData,  inNumberFrames);
        
        SInt16 *left = (SInt16 *)ioData->mBuffers[0].mData;
        memcpy(ioData->mBuffers[1].mData, left, ioData->mBuffers[1].mDataByteSize);
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

    //77Settings (per Channel or all)
    int noOfVoicesTotal;
    int noOfZones;
    enum VoiceMode voiceMode; //
    enum Algo algo;
    int PitchWheelMin;
    int PitchWheelMax;
    enum PlayMode playMode; //
    
    Hal *hal = 0;
    
    void close(){
        hal->close();
        delete hal;
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
