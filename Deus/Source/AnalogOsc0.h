//
//  AnalogOsc0.h
//  Deus
//
//  Created by Mathias Dietrich on 7/29/20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef AnalogOsc0_h
#define AnalogOsc0_h

#include "IModule.h"
#include "Model.h"

class AnalogOsc0 : public IModule{
public:
    AnalogOsc0() {
    }
    
    ~AnalogOsc0() {
    }
    
    ParamSet getSet() override{
       ParamSet set;
       set.moduleId = mOSCAnalog0;
       return set;
    }
    
    void set(int pid, float p) override{
        
    }
    
    int getParamCount() override{
          return 5;
    }
    
    E_Module getType() override{
        return mOSCAnalog0;
    }
};

#endif /* AnalogOsc0_h */
