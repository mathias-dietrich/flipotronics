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

class PatchData {
    public:
    PatchData(){
        
    }
    
    ~PatchData(){
        
    }
    String name;

    int intCount = 0;
    int floatCount= 1024;
    int doubleCount= 0;
    int stringCount= 0;
    int binCount= 0;
    int intNumbers[128];
    float floatNumbers[1024];
    double doubleNumbers[16];
    String stringTable[16];
    char binaries[0];
};

class BankData {
public:
    BankData(){
        patchData[0].name = "Flipotronics";
         patchData[1].name = "Sommer";
         patchData[2].name = "Rocktron";
         patchData[3].name = "Ballad";
        patchData[4].name = "Shit Storm";
    }
    
    ~BankData(){
        
    }
    String magicStart = "FLIP";
    int checksum;
    int lengthTotal;
    int synthId = 1;
    int type = 1;
    int version = 1;
    String name = "Default Bank";
    String author = "Flipotronics";
    String www = "fliptoronics.com";
    int noOfPatches = 5;
    PatchData patchData[256];
    String magicEnd = "FLOP";
};

extern int samplesperblock;
extern int samplerate;
extern double par[MAXPARAM];
extern Param params[MAXPARAM];
extern double tuneTable[256];
extern double tuneMulti[12];

extern int viewModeSetting;
extern int patchCurrent;
extern String patchNameCurrent;
extern bool compareMode;
extern BankData bankData;

class Model {
    
public:
    double par[MAXPARAM];
    Param params[MAXPARAM];
    String patchNameCurrent;
    
    Model copy(){
        Model m;
        m.patchNameCurrent = String(patchNameCurrent);
        for(int i=0;i<MAXPARAM;i++ ){
            m.par[i] =  par[i];
            m.params[i] =  params[i].copy();
        }
        return m;
    }
    
    Model swap(Model m){
        Model old = copy();
        for(int i=0;i<MAXPARAM;i++ ){
            par[i] = m.par[i];
            params[i] = m.params[i].copy();
        }
        return old;
    }
};

#endif /* Model_h */
