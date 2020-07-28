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
