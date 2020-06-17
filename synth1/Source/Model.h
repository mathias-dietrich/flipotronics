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
    String www = "flipotronics.com";
    int noOfPatches = 5;
    PatchData patchData[256];
    String magicEnd = "FLOP";
};

extern int samplesperblock;
extern int samplerate;
extern std::atomic<float> par[MAXPARAM];
extern double parTargetDelta[MAXPARAM];
extern double paramsUndo[MAXPARAM];

extern Param params[MAXPARAM];

extern double tuneTable[256];
extern double tuneMulti[12];

extern int viewModeSetting;
extern int patchCurrent;
extern String patchNameCurrent;
extern String patchNameCurrentUndo;
extern bool compareMode;
extern BankData bankData;
extern std::atomic<float> scopeBuffer[SAMPLERATEMAX * OVERSAMPLING];

extern std::atomic<bool> isUpdateParams;

extern std::atomic<int64> timeTaken;

extern std::atomic<float> sumPeak;
extern std::atomic<float> sumRMS;

class Model {
    
public:

   void set(){
        for(int i=0;i<MAXPARAM;i++ ){
           paramsUndo[i] = par[i];
        }
        patchNameCurrentUndo = patchNameCurrent;
    }
    
    void recall(){
        for(int i=0;i<MAXPARAM;i++ ){
            par[i] = paramsUndo[i];
        }
        patchNameCurrent = patchNameCurrentUndo;
    }
    
    void swap(){
        String pn = patchNameCurrent;
        patchNameCurrent = patchNameCurrentUndo;
        patchNameCurrentUndo = pn;

        for(int i=0;i<MAXPARAM;i++ ){
            float t = par[i];
            par[i] = paramsUndo[i];
            paramsUndo[i] = t;
        }
    }
    
private:

};

#endif /* Model_h */
