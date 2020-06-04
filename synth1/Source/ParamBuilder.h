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
            
            Param p;
            p.pid = 0;
            p.name = "NoVoices";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 1;
            p.maxVal = 32;
            p.stepVal = 1;
            p.type = uInt;
            p.def = 8;
            params[1] = p;
            

           p.pid = 0;
           p.name = "Volume";
           p.writeable = 1;
           p.automate = 1;
           p.minVal = 0;
           p.maxVal = 1;
           p.stepVal = 0.011;
           p.type = uFloat;
           p.def = 8;
           params[7] = p;
            
            p.pid = 1023;
            p.name = "PlayMode";
            p.writeable = 1;
            p.automate = 1;
            p.minVal = 1;
            p.maxVal = 4;
            p.stepVal = 1;
            p.type = uInt;
            p.def = 1;
            params[1023] = p;
        }
};

#endif /* ParamBuilder_h */





