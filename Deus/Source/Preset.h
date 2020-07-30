//
//  Patch.h
//  Deus
//
//  Created by Mathias Dietrich on 15.07.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef Preset_h
#define Preset_h
#include <JuceHeader.h>

#include "Param.h"
#include "Enums.h"

class Preset{
public:
    
    String name;
    String author;
    String desc;
    
    float tuning = 440.0f;
    
    std::map<E_Module,std::map<int, Param> > params;
    
    E_Module inputModule = mInput;
    E_Module osc0Module = mOSCAnalog0;
    E_Module osc1Module = mOSCAnalog1;
    E_Module filter0Module = mFilter0;
    E_Module filter1Module = mFilter1;
    E_Module adsr0Module  = mAdsr0;
    E_Module adsr1Module = mAdsr1;
    E_Module adsr2Module  = mAdsr2;
    E_Module lfo0Module  = mLFO0;
    E_Module lfo1Module   = mLFO1;
    E_Module lfo2Module  = mLFO2;
    
    bool isFilterParallel;
    
    
};
#endif /* Preset_h */
