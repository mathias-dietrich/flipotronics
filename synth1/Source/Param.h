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
    String name;
    int pid;
    int writeable;
    int automate;
    int valI;
    float valF;
    double valD;
    float def;
    String valS;
    float stepVal;
    float minVal;
    float maxVal;
    
    Param copy(){
        Param p;
        p.type = type;
        p.name = String(name);
        p.pid = pid;
        p.writeable = writeable;
        p.automate = automate;
        p.valI = valI;
        p.valF = valF;
        p.valD = valD;
        p.def = def;
        p.valS = String(valS);
        p.stepVal = stepVal;
        p.minVal = minVal;
        p.maxVal = maxVal;
        return p;
    }
};
#endif /* Param_h */
