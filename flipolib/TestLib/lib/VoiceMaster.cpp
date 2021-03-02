//
//  VoiceMaster.cpp
//  TestLib
//
//  Created by Mathias Dietrich on 02.03.21.
//

#include "VoiceMaster.hpp"


void VoiceMaster::noteOn(int channel, int note, int velocity){
    std::cout << "Note On channel: " << channel << " note: " << note << " velocity:" << velocity << endl ;
    

}

void VoiceMaster::noteOff(int channel, int note, int velocity){
    std::cout << "Note Off channel: " << channel << " note: " << note << " velocity: " << velocity << endl;
    
}

void VoiceMaster::aftertouch(int channel, int pressure){
    std::cout << "Note Aftertouch channel: " << channel << " pressure: " << pressure  << endl;
    
}

void VoiceMaster::allNotesOff(int channel){
    
}
void VoiceMaster::clearVoice(int id){
    
}
void VoiceMaster::clearAllVoices(){
    
}
void VoiceMaster::pitchBend(int channel, int val){
    
}
void VoiceMaster::modWheel(int channel, int val){
    
}
void VoiceMaster::controller(int channel, int cc, int val){
    
}

void VoiceMaster::configure(int zone, int channel, int noOfVoices){
    
}
