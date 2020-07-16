//
//  IFactory.h
//  Deus
//
//  Created by Mathias Dietrich on 16.07.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef IFactory_h
#define IFactory_h


#include "IComponent.h"

class IComponent;

class IFactory{
public:
    
    virtual ~IFactory(){}
    
    virtual IComponent * get(String type) = 0;
};


#endif /* IFactory_h */
