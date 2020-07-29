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


class IModule {
public:

    virtual ParamSet getSet() = 0;
    virtual void set(int i, float p) = 0;
    virtual int getParamCount() = 0;
    virtual E_Module getType() = 0;
};

#endif /* IModule_h */
