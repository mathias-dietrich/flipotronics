//
//  IModule.h
//  Deus
//
//  Created by Mathias Dietrich on 7/28/20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef IModule_h
#define IModule_h

#include "Enums.h"
#include "Model.h"

class Core;

class IModule {
public:
    virtual ~IModule()=0;
    
    virtual void init(int sampleRate, int samplesPerBlock) = 0;
    virtual ParamSet getSet() = 0;
    virtual void set(int pid, float val) = 0;
    virtual int getParamCount() = 0;
    virtual E_Module getType() = 0;
    virtual float getNextL(float inputL, bool move) = 0;
    virtual float getNextR(float inputR, bool move) = 0;
    virtual void noteOn(int channel, int note) = 0;
    virtual void noteOff(int channel, int note) = 0;
    
    void setTuning(float tuning){
        this->tuning = tuning;
    }
    
    atomic<float> tuning;
    
};

inline IModule::~IModule() { }

#endif /* IModule_h */
