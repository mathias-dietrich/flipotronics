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

struct Msg {
    float blockBuffer[SAMPLERATEMAX];
};

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
    
    std::atomic<float> par[MAXPARAM];
};

class Model {
    
public:
    static Model& of()
    {
        static Model   instance;
        return instance;
    }
    Model(Model const&) = delete;
    void operator=(Model const&)  = delete;
    
   void set(){
        for(int i=0;i<MAXPARAM;i++ ){
           paramsUndo[i] = (float)par[i];
        }
        patchNameCurrentUndo = patchNameCurrent;
    }
    
    void recall(){
        for(int i=0;i<MAXPARAM;i++ ){
            par[i] = (float)paramsUndo[i];
        }
        patchNameCurrent = patchNameCurrentUndo;
    }
    
    void swap(){
        String pn = patchNameCurrent;
        patchNameCurrent = patchNameCurrentUndo;
        patchNameCurrentUndo = pn;

        for(int i=0;i<MAXPARAM;i++ ){
            float t = par[i];
            par[i] =  (float)paramsUndo[i];
            paramsUndo[i] = t;
        }
    }
    
    // boolean
    std::atomic<bool> hasPlayed;
    std::atomic<bool> compareMode;
    std::atomic<bool> isUpdateParams;
    
    // ints
    std::atomic<int64> timeTaken;
    std::atomic<int> noOfSamplesToPlay;
    std::atomic<int> patchCurrent;
    std::atomic<int> viewModeSetting;
    
    // floats
    std::atomic<float> par[MAXPARAM];
    std::atomic<float> sumPeakL;
    std::atomic<float> sumPeakR;
    std::atomic<float> sumRMSL;
    std::atomic<float> sumRMSR;
    
    std::atomic<float> paramsUndo[MAXPARAM];
    
    std::atomic<float> parTargetDelta[MAXPARAM];
    std::atomic<float> tuneTable[128];
    std::atomic<float> tuneMulti[12];

    // Strings
    String patchNameCurrent;
    String patchNameCurrentUndo;
    
    // buffer
    AudioBuffer<float> fileBuffer;
   
    // objects
    BankData bankData;
    Param params[MAXPARAM];

    bool flip;
    void pushMsgToUi() noexcept{
         flip = !flip;
     }

     ~Model() {
         delete msg0;
         delete msg1;
     }
    
    Msg * getBack(){
        if(flip){
            return msg0;
        }
        return msg1;
     }
    
    Msg * getFront(){
       if(flip){
           return msg1;
       }
       return msg0;
    }
                     
    
private:
    Msg * msg0 = new Msg();
    Msg * msg1 = new Msg();
    
    Model() {}
};

#endif /* Model_h */
