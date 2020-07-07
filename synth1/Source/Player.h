//
//  Player.h
//  synth1
//
//  Created by Mathias Dietrich on 15.06.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef Player_h
#define Player_h

#include <stdio.h>
#include <JuceHeader.h>

class Player{
    
    public:
    
    Player(){}
    virtual ~Player(){}

    virtual void startVoice(int midiChannel, int midiNoteNumber, float velocity, int group) = 0;
    virtual void endVoice(int midiChannel, int midiNoteNumber) = 0;
};

#endif /* Player_h */
