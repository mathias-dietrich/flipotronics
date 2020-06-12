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
#include <string>

inline String toString(int i) {
    return std::to_string(i);
}

inline String toString(float f) {
    return std::to_string(f);
}

inline String toString(double d) {
    return std::to_string(d);
}

inline int intFromString(String s) {
    return s.getIntValue();
}

// 0.0 - 1.0
inline float LinearToDecibel(float linear)
{
    return Decibels::gainToDecibels(linear, -96.0f);
    /*
   float db;
   if (linear != 0.0f)
     db = 20.0f * log10(linear);
   else
     db = -144.0f;  // effectively minus infinity
   return db;
     */
}

inline float degToRad(float degrees){
    return degrees * M_PI / 180.0f;
}

inline float radToDeg(float radians){
   return radians * 180.0f / M_PI;
}

inline float DecibelToLinear(float db)
{
    return Decibels::decibelsToGain(db, -96.0f);
  // return  exp(db/20.0f);
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

inline String getWaveType(E_WaveType type){
    switch(type){
        case wSin:
            return "Sin";
            
        case wSaw:
            return "Saw";
        
        case wTriangle:
            return "Triangle";
        
        case wSquare:
            return "Square";
        
        case wShark:
            return "Shark";
        
        case wWhite:
            return "White";
        
        case wBrown:
            return "Brown";
            
        case wPink:
            return "Pink";
            
        case wTable:
            return "Table";
    }
}
   
#endif /* Func_h */
