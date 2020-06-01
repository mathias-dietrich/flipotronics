//
//  Func.h
//  synth1
//
//  Created by Mathias Dietrich on 01.06.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef Func_h
#define Func_h

#include <math.h>

// 0.0 - 1.0
inline float LinearToDecibel(float linear)
{
   float db;
   if (linear != 0.0f)
     db = 20.0f * log10(linear);
   else
     db = -144.0f;  // effectively minus infinity
   return db;
}

inline float MidiToLinear(int midi)
{
    return midi / 127.0;
}

inline int LinearToMidi(float linear)
{
    return linear * 127.0;
}

inline float MidiToFreq(int note, float tuning)
{
    return tuning * pow(2.0, ((note - 69) / 12.0));
}

inline int FreqToMidi(float freq, float tuning)
{
    return log(freq/tuning)/log(2) * 12.0 + 69;
}
   
#endif /* Func_h */
