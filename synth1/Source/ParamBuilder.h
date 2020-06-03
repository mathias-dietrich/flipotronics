//
//  ParamBuilder.h
//  synth1
//
//  Created by Mathias Dietrich on 03.06.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef ParamBuilder_h
#define ParamBuilder_h

#include <stdio.h>
#include <JuceHeader.h>
#include "WaveTable.h"
#include "Model.h"
#include "Func.h"
#include "Param.h"

/*    E_UnitType type;
String name;
int pid;
int writeable;
int automate;
int valI;
float valF;
double valD;
String valS;
float stepValue;
 */

class ParamBuilder {       // The class
    public:
        void build(){
            for(int i=0; i < 1024; ++i){
                Param p;
                p.pid = 0;
                p.name = toString(i);
                params[i] = p;
                p.minVal = 0;
                p.maxVal = 1;
                p.stepVal = 0.01;
                p.type = uFloat;
                p.def = 0;
            }
            
            Param p0;
            p0.pid = 0;
            p0.name = "Tuning";
            p0.writeable = 1;
            p0.automate = 1;
            p0.valD = 440.0;
            p0.minVal = 435.0;
            p0.maxVal = 445.0;
            p0.stepVal = 0.1;
            p0.def = 440.0;
            params[0] = p0;
        }
};

#endif /* ParamBuilder_h */





