//
//  ModuleFactory.h
//  Deus
//
//  Created by Mathias Dietrich on 7/29/20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef ModuleFactory_h
#define ModuleFactory_h

#include "Inc.h"
#include "Enums.h"
#include "IModule.h"
#include "AnalogOsc0.h"
#include "AnalogOsc1.h"
#include "BlankModule.h"
#include "Filter0.h"
#include "Lfo0.h"
#include "DelayFX.h"

class ModuleFactory{
    protected:
       static ModuleFactory *instance;
       ModuleFactory() {
           modules_map[mOSCAnalog0] = new AnalogOsc0();
           modules_map[mOSCAnalog1] = new AnalogOsc1();
           
           modules_map[mFilter0] = new Filter0();
           modules_map[mFilter1] = new Filter0();
           
           modules_map[mLFO0] = new Lfo0();
           
           modules_map[mBlank] = new BlankModule();
           modules_map[mDelay] = new DelayFX();
           
       }
    
    public:
          static ModuleFactory * of() {
              if (instance == 0)
                  instance = new ModuleFactory();
              return instance;
          }
    
    IModule * get(E_Module m){
        map<E_Module, IModule *>::iterator it = modules_map.find(m);
        if(it != modules_map.end())
        {
            return modules_map[m];
        }
        
        return modules_map[mBlank];
    }
    
    std::vector<E_Module> getAll(){
        std::vector<E_Module> all;
        return all;
    }
    
private:
    std::map<E_Module, IModule *> modules_map;
};

#endif /* ModuleFactory_h */
