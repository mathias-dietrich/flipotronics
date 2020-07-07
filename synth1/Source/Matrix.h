//
//  Matrix.h
//  synth1
//
//  Created by Mathias Dietrich on 06.07.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef Matrix_h
#define Matrix_h

enum MatrixTransform{
    t_NONE = 0,
    t_UNIPOLAR_TO_BIPOLAR,
    t_BIPOLAR_TO_UNIPOLAR,
    t_MIDI_NORMALIZE,
    t_INVERT_MIDI_NORMALIZE,
    t_MIDI_TO_BIPOLAR,
    t_MIDI_TO_PAN,
    t_MIDI_SWITCH,
    t_MIDI_TO_ATTENUATION,
    t_NOTE_NUMBER_TO_FREQUENCY,
    t_MAX_TRANSFORM
};

enum MatrixSource{
    s_NONE = 0,
    s_LFO1,
    s_LFO2,
    s_LFO3,
    s_LFO4,
    s_SOURCES
};

enum MatrixDest{
    d_NONE = 0,
    d_OSC1_FREQ,
    d_OSC1_VOL,
    d_FILTER1_CUTOFF,
    d_TARGETS
};

struct MatrixEntry{
    // --- index of source
    MatrixSource source;

    // --- index of destination
    MatrixDest dest;

    int paramMulti;
    int paramAdd;

    // --- transform on Source
    MatrixTransform transform;

    // --- to easily turn on/off a modulation routing
    bool isEnabled;
};

class Matrix{
public:
    
    MatrixEntry entries[s_SOURCES][d_TARGETS];
    
    // sources: where each source (LFO, EG, ETC) writes its output value
    float sources[s_SOURCES];

    // destinations: where the newly calculated mod values are read from
    float targets[d_TARGETS];
    
    inline MatrixEntry createEntry(MatrixSource source, MatrixDest dest, int paramMulti, int  paramAdd, MatrixTransform transform, bool isEnabled = true)
       {
           MatrixEntry entry;
           entry.source = source;
           entry.dest = dest;
           entry.paramMulti = paramMulti;
           entry.paramAdd = paramAdd;
           entry.transform = transform;
           entry.isEnabled = isEnabled;
           return entry;
       }
    
    inline void addEntry(MatrixEntry entry){
        entries[entry.source][entry.dest] = entry;
    }
    
    inline void clear(){
        for( int i =0; i < s_SOURCES;i++){
            for( int y =0; y < d_TARGETS;y++){
                entries[i][y].isEnabled = false;
            }
        }
    }
    
    inline void calc(float (&p)[MAXPARAM]){
           for( int i = 0; i < d_TARGETS;i++){
               float t = 1.0f;
               for( int y = 0; y < s_SOURCES;y++){
                   MatrixEntry entry = entries[y][i];
                   if(entry.isEnabled){
                       float input = sources[y];
                       switch(entry.transform){
                           case t_NONE:
                               break;
                               
                           case t_UNIPOLAR_TO_BIPOLAR:
                               input = 2.0f * input - 1.0f;
                               break;
                               
                           case t_BIPOLAR_TO_UNIPOLAR:
                               input =  0.5f * input + 0.5f;
                               break;
                               
                           case t_MIDI_NORMALIZE:
                               
                               break;
                           case t_INVERT_MIDI_NORMALIZE:
                               
                               break;
                           case t_MIDI_TO_BIPOLAR:
                               
                               break;
                           case t_MIDI_TO_PAN:
                               
                               break;
                           case t_MIDI_SWITCH:
                               
                               break;
                           case t_MIDI_TO_ATTENUATION:
                               
                               break;
                           case t_NOTE_NUMBER_TO_FREQUENCY:
                               
                               break;
                               
                           case t_MAX_TRANSFORM:
                               break;
                       }
                       float multi = 1.0;
                       if(entry.paramMulti > -1){
                           multi = p[entry.paramMulti];
                       }
                       if(entry.paramAdd == P_FIXTURN){
                          t *=  1.0f - input *  multi;
                           continue;
                       }
                       float add = 0;
                       if(entry.paramAdd > -1){
                           add = p[entry.paramAdd];
                       }
                       t *= input * multi;
                       t += add;
                   }
               }
               
               // bounds check
               if(t < -1){
                   t = -1;
               }
               if(t > 1){
                   t = 1;
               }
               targets[i] = t;
           }
       }
};

#endif /* Matrix_h */
