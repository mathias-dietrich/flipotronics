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

// https://github.com/juce-framework/JUCE/blob/master/examples/Utilities/MultithreadingDemo.h

using Clock = std::chrono::high_resolution_clock;
using TimePoint = std::chrono::time_point<Clock>;

class Arp :  public Thread {
    
  public:

    typedef std::chrono::high_resolution_clock Clock;
    TimePoint last = TimePoint();
    
    Arp():Thread ("ARP Thread"){

    }

    ~Arp() {
        isRunning = false;
        sleep(1);
        if(player != nullptr){
            delete player;
        }
    }
    
    void setPlayer(Player * player){
        this->player = player;
    }
    
    void run() override{
        while(isRunning){
            usleep(250);
            if(!isRunning)return;
            
            auto newTime = std::chrono::high_resolution_clock::now();
            int64 nano = std::chrono::duration_cast<std::chrono::nanoseconds>(newTime-last).count();

             if(newStart){
                newStart = false;
               last = newTime;
               isNoteOn = true;
               player->startVoice(1,60, 0.9);
               continue;
           }
           
          int64 timePassed = nano / 1000000;
            
          if (!isNoteOn && timePassed >= tempoMs){
              last = newTime;
              isNoteOn = true;
              player->startVoice(1,60, 0.9);
              continue;
          }
           
          if (timePassed >= gateTimeMsec){
              isNoteOn = false;
              player->endVoice(1,60);
          }
        }
    }
        
    void init (double sampleRate, int samplesPerBlock){
        this->sampleRate = sampleRate;
        this->samplesPerBlock = samplesPerBlock;
        last = TimePoint();
    }
    
    void start(){
        isRunning = true;
        newStart = true;
        last = TimePoint();
        startThread (3);
    }
    void stop(){
         isRunning = false;
    }
    
    float bpm = 123;
    E_NoteType noteType = nEIGHT;
    bool isRunning;
    float tempoMs = 250;
    bool newStart = false;
    
private:
    Note steps[32];
    int sampleRate;
    int samplesPerBlock;
    bool isNoteOn;
    int gateTimeMsec = 100;
     Player * player;
};

#endif /* Arp_hpp */
