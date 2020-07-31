//
//  Matrix.h
//  synth1
//
//  Created by Mathias Dietrich on 06.07.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef Matrix_h
#define Matrix_h
#define  P_FIXTURN 1025

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
    s_LFO0,
    s_LFO1,
    s_LFO2,
    s_LFO3,
    s_SOURCESCOUNT
};

enum MatrixDest{
    d_NONE = 0,
    d_OSC0_PITCH,
    d_OSC0_VOL,
    d_FILTER0_CUTOFF,
    d_TARGETSCOUNT
};

struct MatrixEntry{
    // --- index of source
    MatrixSource source;

    // --- index of destination
    MatrixDest dest;

    E_Module modMulti;
    int paramMulti;
    E_Module modAdd;
    int paramAdd;

    // --- transform on Source
    MatrixTransform transform;

    // --- to easily turn on/off a modulation routing
    bool isEnabled;
    
    bool isUseOneMinus;
    
    
    
    // Curve
    float curve;
};

class Matrix{
public:
    
    MatrixEntry entries[s_SOURCESCOUNT][d_TARGETSCOUNT];
    
    // sources: where each source (LFO, EG, ETC) writes its output value
    float sources[s_SOURCESCOUNT];

    // destinations: where the newly calculated mod values are read from
    float targets[d_TARGETSCOUNT];
    
    inline MatrixEntry createEntry(MatrixSource source, MatrixDest dest, E_Module modMulti, int paramMulti,  E_Module modAdd, int  paramAdd, MatrixTransform transform, bool useOneMinus, bool isEnabled)
       {
           MatrixEntry entry;
           entry.source = source;
           entry.dest = dest;
           entry.modMulti = modMulti;
           entry.paramMulti = paramMulti;
           entry.modAdd = modAdd;
           entry.paramAdd = paramAdd;
           entry.transform = transform;
           entry.isUseOneMinus = useOneMinus;
           entry.isEnabled = isEnabled;
           return entry;
       }
    
    inline void addEntry(MatrixEntry entry){
        entries[entry.source][entry.dest] = entry;
    }
    
    inline void clear(){
        for( int i =0; i < s_SOURCESCOUNT;i++){
            for( int y =0; y < d_TARGETSCOUNT;y++){
                entries[i][y].isEnabled = false;
            }
        }
    }
    
    inline void calc(){
           for( int i = 0; i < d_TARGETSCOUNT;i++){
               float t = 1.0f;
               for( int y = 0; y < s_SOURCESCOUNT;y++){
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
                           multi = Model::of()->preset.params[entry.modMulti][entry.paramMulti].valF;
                       }
                       if(entry.paramAdd == P_FIXTURN){
                          t *=  1.0f - input *  multi;
                           continue;
                       }
                       float add = 0;
                       if(entry.paramAdd > -1){
                           add = Model::of()->preset.params[entry.modAdd][entry.paramAdd].valF;
                       }
                       t *= input * multi;
                       t += add;
                       if(entry.isUseOneMinus){
                           t = 1.0f - t;
                       }
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
