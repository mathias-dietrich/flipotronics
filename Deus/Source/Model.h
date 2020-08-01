//
//  Model.h
//  Deus
//
//  Created by Mathias Dietrich on 15.07.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef Model_h
#define Model_h

#include <JuceHeader.h>
#include "Param.h"
#include "Defines.h"
#include "Global.h"
#include "Preset.h"

using namespace std;


struct ParamSet{
    int moduleId;
    std::map<int, float> params;
};

class Model{
    protected:
       static Model *instance;
       Model() { }
    
    public:
       static Model * of() {
           if (instance == 0)
               instance = new Model();
           return instance;
       }
    
    void init(){
        
    }

    Preset preset;
    E_Master masterSel = mEdit;
    Global global;
    
    Param getParam(E_Module module, int paramId){
        return preset.params[module][paramId];
    }
    
    std::map<int, Param> getParams(E_Module module){
        return preset.params[module];
    }
    
    int64 timeTaken;
    
    float sumRMSL;
    float sumRMSR;
    float sumPeakL;
    float sumPeakR;
    
private:

};


#endif /* Model_h */
