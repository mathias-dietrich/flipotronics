//
//  Model.h
//  synth1
//
//  Created by Mathias Dietrich on 02.06.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef Model_h
#define Model_h

#include "Param.h"
#include "Const.h"

extern int samplesperblock;
extern int samplerate;
extern double par[MAXPARAM];
extern Param params[MAXPARAM];
extern double tuneTable[256];
extern double tuneMulti[12];

extern int viewModeSetting;
extern int patchCurrent;
#endif /* Model_h */
