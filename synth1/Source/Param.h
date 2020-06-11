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
    E_UnitType type = uUnknown;
    String name = "";
    int pid = -1;
    
    int writeable = 0;
    int automate = 0;
    int controllerId = -1;
    
    int valI = 0;
    float valF = 0.0f;
    double valD = 0.0;
    double desiredValue = 0.0;
    
    String valS = "";
    
    float def = 0.0f;
    float stepVal = 0.01f;
    float minVal = 0.0f;
    float maxVal = 1.0f;
    float smoothTime = 0.0f; // msec
    
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
        p.smoothTime = smoothTime;
        p.controllerId = controllerId;
        return p;
    }
};
#endif /* Param_h */
