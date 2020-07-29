//
//  BlankComponent.h
//  Deus
//
//  Created by Mathias Dietrich on 7/29/20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef BlankModule_h
#define BlankModule_h

#include "IModule.h"


class BlankModule:  public IModule{
public:
    
    BlankModule(){

    }

    ~BlankModule(){

    }
    
    ParamSet getSet() override{
          ParamSet set;
          set.moduleId = mBlank;
          return set;
       }
       
       void set(int pid, float p) override{
           
       }
       
       int getParamCount() override{
             return 0;
       }
       
       E_Module getType() override{
           return mBlank;
       }
    
private:
    std::map<int, Param> params;
};
#endif /* IModule_h */
