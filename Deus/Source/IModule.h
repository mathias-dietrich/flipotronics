//
//  IModule.h
//  Deus
//
//  Created by Mathias Dietrich on 7/28/20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef IModule_h
#define IModule_h

enum E_Module {
    mOSCAnalog0=0,
    mOSCAnalog1=1,
    mOSCWave0=2,
    mOSCWave1=3,
    mOSCSample0=4,
    mOSCSample1=5,
    mFilter0=6,
    mFilter1=7,
    mAdsr0=8,
    mAdsr1=9,
    mAdsr2=10,
    mLFO0=11,
    mLFO1=12,
    mLFO2=13,
    mAmp=14,
    mInput=15,
    mLFX0=16,
    mLFX1=17,
    mLFX2=18,
    mLFX3=19,
    mMODULECOUNT
};

struct ParamSet{
    int moduleId;
    std::map<int, float> params;
};

class IModule{
public:
    virtual ~IModule() = 0;
    virtual ParamSet getSet() = 0;
    virtual void set(int i, float p) = 0;
};

class RootModule : public IModule{
public:
    RootModule(){
        
    }
    
    ~RootModule(){
        
    }
    
    ParamSet getSet(){
        ParamSet set;
        set.moduleId = 0;
        return set;
    }
    
    void set(int i, float p) {
        
    }
};

class ModuleFactory{
public:
    ModuleFactory(){
        modules_map[mOSCAnalog0] = new RootModule();
    }
    
    ~ModuleFactory(){
           
    }
    IModule * get(E_Module m){
        return modules_map[m];
    }
    
    std::vector<E_Module> getAll(){
        std::vector<E_Module> all;
        return all;
    }
    
private:
    std::map<E_Module, IModule *> modules_map;
};



#endif /* IModule_h */
