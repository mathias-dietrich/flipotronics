//
//  PatchLoader.h
//  synth1
//
//  Created by Mathias Dietrich on 04.06.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef PatchLoader_h
#define PatchLoader_h
#include <JuceHeader.h>
#include "WaveTable.h"
#include "Model.h"
#include "Func.h"

class PatchLoader {       // The class

public:
    void load(int pNo){
        PatchData p = Model::of().bankData.patchData[pNo];
        Model::of().patchNameCurrent = p.name;
        for(int i=0; i < p.floatCount;++i){
            Model::of().par[i] = p.floatNumbers[i];
        }
        Model::of().patchCurrent = pNo;
    }
};

#endif /* PatchLoader_h */
