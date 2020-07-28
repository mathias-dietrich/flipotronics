//
//  Func.h
//  Deus
//
//  Created by Mathias Dietrich on 15.07.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef Func_h
#define Func_h

#include <math.h>
#include <string>

#include "Enums.h"


inline String format(float val, int prec){
    std::stringstream stream;
    stream << std::fixed << std::setprecision(prec) << val;
    std::string s = stream.str();
    return s;
}

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

inline Rectangle<float> convertRect(Rectangle<int> r){
    Rectangle<float> rf{static_cast<float>(r.getX()), static_cast<float>(r.getY()), static_cast<float>(r.getWidth()), static_cast<float>(r.getHeight())};
    return rf;
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


inline String midiNote(int midiNote){
    String notes[] = {"C","C#","D","D#","E","F","F#","G","G#","A","Bb","B"};
    int oct = midiNote / 12;
    int n = midiNote - oct * 12;
    return notes[n] + String(oct);
}

inline String devision(int devision){
    switch(devision){
        case 0:
            return "0";
        case 1:
            return "1/2";
        case 2:
            return "1/2.";
        case 3:
            return "1/4";
        case 4:
            return "1/4.";
        case 5:
            return "1/8";
        case 6:
            return "1/8.";
        case 7:
            return "1/16";
        case 8:
            return "1/16.";
        case 9:
            return "1/32";
        case 10:
            return "1/32.";
        case 11:
            return "1/64";
    }
    return "";
}

inline String getFilterTypeString(MultiModeLadderFilterTypes type){
      switch (type) {
           case LPF1:
              return "LPF1";
              
           case LPF2:
              return "LPF2";

           case LPF3:
                return "LPF3";
              
           case LPF4:
                return "LPF4";
              
           case HPF1:
                return "HPF1";
              
           case HPF2:
                return "HPF2";
              
           case HPF3:
                return "HPF3";
              
           case HPF4:
               return "HPF4";
              
           case BPF2:
               return "BPF2";
              
           case BPF4:
               return "BPF4";
              
           case NF2:
               return "NF2";
              
           case NF4:
               return "NF4";
              
           case PF2:
              return "PF2";
              
           case PF4:
               return "PF4";
              
           default:
              return "Off";
       }
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
}

inline float linearToDecibles(float lin)
{
    return Decibels::gainToDecibels(lin, -96.0f);
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
