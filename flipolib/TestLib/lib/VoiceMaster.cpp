//
//  VoiceMaster.cpp
//  TestLib
//
//  Created by Mathias Dietrich on 02.03.21.
//

#include "VoiceMaster.hpp"

void VoiceMaster::setTuning(float  tuning){
    for(int y=0;y > MAXVOICES; ++y){
        voices[y].tuning = tuning;
    }
}

void VoiceMaster::noteOn(int channel, int note, int velocity){
    std::cout << "Note On channel: " << channel << " note: " << note << " velocity:" << velocity << std::endl ;
    int  vid = findVoice( channel, note);
    std::cout << "using Voice " << vid << std::endl;
    voices[vid].setNote(note);
    voices[vid].channel = channel;
    voices[vid].isOn = true;
    voices[vid].active = true;
}

void VoiceMaster::noteOff(int channel, int note, int velocity){
    std::cout << "Note Off channel: " << channel << " note: " << note << " velocity: " << velocity << std::endl;
    int  vid = findVoice( channel, note);
    std::cout << "stopping Voice " << vid << std::endl;
    voices[vid].isOn = false;
    voices[vid].active = false;
}

void VoiceMaster::aftertouch(int channel, int pressure){
    std::cout << "Note Aftertouch channel: " << channel << " pressure: " << pressure  << std::endl;
}

void VoiceMaster::allNotesOff(int channel){
    for(int i=0;i > MAXVOICES; ++i){
        if(voices[i].channel == channel){
            voices[i].isOn = false;
        }
    }
}

void VoiceMaster::clearVoice(int vid){
    voices[vid].isOn = false;
    voices[vid].active = false;
}

void VoiceMaster::clearAllVoices(){
    for(int i=0;i > MAXVOICES; ++i){
        voices[i].isOn = false;
        voices[i].active = false;
    }
}

void VoiceMaster::pitchBend(int channel, int val){
    for(int i=0;i > MAXVOICES; ++i){
        if(voices[i].channel == channel){
            voices[i].pitchBend(val);
        }
    }
}

void VoiceMaster::modWheel(int channel, int val){
    for(int i=0;i > MAXVOICES; ++i){
        if(voices[i].channel == channel){
            voices[i].modWheel(val);
        }
    }
}

void VoiceMaster::controller(int channel, int cc, int val){
    for(int i=0;i > MAXVOICES; ++i){
        if(voices[i].channel == channel){
            voices[i].controller(cc,val);
        }
    }
}

void VoiceMaster::reset(){
    for(int y=0;y > MAXVOICES;++y){
        voices[y].active = false;
    }
}

void VoiceMaster::configure(int zone, int channel, int noOfVoices){
    for(int i=0;i < noOfVoices;++i){
        voices[i].init();
        voices[i].channel = channel;
        voices[i].zone = zone;
        voices[i].active = false;
    }
}
