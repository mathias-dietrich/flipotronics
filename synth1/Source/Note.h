//
//  Note.h
//  synth1
//
//  Created by Mathias Dietrich on 31.05.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef Note_h
#define Note_h

struct Note{
    int midiNote;
    int midiVelocity;
    int tickLength;
    double freq;
    int sampleLength;
    int startClock;
    int endClock;
    
};

#endif /* Note_h */
