//
//  Loader.h
//  Deus
//
//  Created by Mathias Dietrich on 15.07.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef Loader_h
#define Loader_h

class Loader{
    protected:
       static Loader *instance;
       Loader() { }
    
    public:
       static Loader * of() {
           if (instance == 0)
               instance = new Loader();
           return instance;
       }
    
    void init(){
        Preset preset;
        preset.name = "Hello";
        preset.author = "Flipotronics";
        preset.desc = "Inital Preset";
        
        preset.inputModule = mInput;
        preset.osc0Module = mOSCAnalog0;
        preset.osc1Module = mOSCAnalog1;
        preset.filter0Module = mFilter0;
        preset.filter1Module = mFilter1;
        preset.adsr0Module  = mAdsr0;
        preset.adsr1Module = mAdsr1;
        preset.adsr2Module  = mAdsr2;
        preset.lfo0Module  = mLFO0;
        preset.lfo1Module   = mLFO1;
        preset.lfo2Module  = mLFO2;
        
        preset.params[mMacro][16].valF = 440.0f;

        Model::of()->preset = preset;
    }
};
Loader * Loader::instance = 0;

#endif /* Loader_h */
