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
#include <chrono>
#include <JuceHeader.h>
#include <time.h>
#include <unistd.h>

#include "Note.h"
#include "Player.h"
#include "Enum.h"
#include "ParamBuilder.h"
// https://github.com/juce-framework/JUCE/blob/master/examples/Utilities/MultithreadingDemo.h

using Clock = std::chrono::high_resolution_clock;
using TimePoint = std::chrono::time_point<Clock>;

//
//
class Arp : public Thread {
    
  public:

    typedef std::chrono::high_resolution_clock Clock;
    TimePoint last = TimePoint();
    
    Arp() :Thread ("ARP Thread"){

    }

    ~Arp() {
        
    }
    
    void setPlayer(Player * player){
        this->player = player;
    }
    
    void run() {
        while(isRunning){
            usleep(250);
            if(!isRunning)return;
            
            float bps = Model::of().par[P_ARP_BPM] / 60.0f;
            float tempoMsBeat =  1000.0f / bps;
            
            // WHOLE, nHALF, nHALFD, qQuarter, qQuarterD, nEIGHT, nEIGHTD, nSIXTEEN, nSIXTEEND, nThirtyTwo, nThirtyTwoD, nSixtyFour}
            switch(int( Model::of().par[P_ARP_DEVISION])){
                case nWHOLE:
                    tempoMs = 4.0 * tempoMsBeat;
                    break;
                    
                case nHALF:
                    tempoMs = 2.0 * tempoMsBeat;
                    break;
                    
                case nHALFD:
                    tempoMs = 3.0 * tempoMsBeat;
                    break;
                    
                case qQuarter:
                    tempoMs = 1.0 * tempoMsBeat;
                    break;
                    
                case qQuarterD:
                    tempoMs = 2.0/3.0 * tempoMsBeat;
                    break;
                    
                case nEIGHT:
                    tempoMs = 0.5 * tempoMsBeat;
                    break;
                    
                case nEIGHTD:
                    tempoMs = 0.5 * 2.0 / 3.0 * tempoMsBeat;
                    break;
                    
                case nSIXTEEN:
                    tempoMs = 0.25 * tempoMsBeat;
                    break;
                    
                case nSIXTEEND:
                    tempoMs = 0.25 * 2.0 / 3.0 * tempoMsBeat;
                    break;
                    
                case nThirtyTwo:
                    tempoMs = 0.125 * tempoMsBeat;
                    break;
                    
                case nThirtyTwoD:
                    tempoMs = 0.125 *  2.0 / 3.0 *tempoMsBeat;
                    break;
                    
                case nSixtyFour:
                    tempoMs = 0.125 /  2.0  * tempoMsBeat;
                    break;
            }
            
            auto newTime = std::chrono::high_resolution_clock::now();
            int64 nano = std::chrono::duration_cast<std::chrono::nanoseconds>(newTime-last).count();

             if(newStart){
               newStart = false;
               last = newTime;
               isNoteOn = true;
               currentNote = 0;
               runningNote =  Model::of().par[P_ARP_NOTE1] +  Model::of().par[P_ARP_TRANSPOSE];
               player->startVoice(1,runningNote, 0.9);
               continue;
           }
           
            float timePassed = nano / 1000000.0f;
            
          if (!isNoteOn && timePassed >= tempoMs){
              last = newTime;
              isNoteOn = true;
              int noteIndex = currentNote + P_ARP_NOTE1;
              if(currentNote > 7){
                  noteIndex  = (currentNote-8) + P_ARP_NOTE9;
              }
              if( Model::of().par[P_ARP_LEGATO] == 0){ // not Legato
                  player->endVoice(1,runningNote);;
              }
              runningNote =  Model::of().par[noteIndex];
              runningNote +=  Model::of().par[P_ARP_TRANSPOSE];
              
              player->startVoice(1,runningNote,   Model::of().par[P_ARP_VELOCITY] / 127.0f);
              ++currentNote;
              if(currentNote >=  Model::of().par[P_ARP_NOTECOUNT]){
                  currentNote = 0;
              }
              continue;
          }
            
            float gate = tempoMs - 1.0f;
            float gatePercent =  Model::of().par[P_ARP_GATE];
            gate =  gatePercent / 100.0f * gateTimeMsec * 2.0f;
            if( Model::of().par[P_ARP_LEGATO] == 1){
                continue;
            }
          if (timePassed >= gate){
              isNoteOn = false;
              player->endVoice(1,runningNote);
          }
        }
    }
        
    void init (double sampleRate, int samplesPerBlock){
        this->sampleRate = sampleRate;
        this->samplesPerBlock = samplesPerBlock;
        last = TimePoint();
    }
    
    void start(){
        if(isRunning)return;
        isRunning = true;
        newStart = true;
        last = TimePoint();
         startThread (3);
    }
    void stop(){
        isRunning = false;
        signalThreadShouldExit ();
    }
    
    E_NoteType noteType = nEIGHT;
    bool isRunning;
    float tempoMs = 0.0f;
    bool newStart = false;
    
private:
    Note steps[32];
    int sampleRate;
    int samplesPerBlock;
    bool isNoteOn;
    int gateTimeMsec = 100;
     Player * player;
    int currentNote;
    int runningNote;
};

#endif /* Arp_hpp */
