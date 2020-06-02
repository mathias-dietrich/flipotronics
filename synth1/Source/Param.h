//
//  Param.h
//  synth1
//
//  Created by Mathias Dietrich on 02.06.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef Param_h
#define Param_h

#include "Enum.h"

struct Param{
    E_UnitType type;
    string name;
    int pid;
    int writeable;
    int automate;
    
    int valI;
    float valF;
    double valD;
    string valS;
    float stepValue;
};
#endif /* Param_h */
