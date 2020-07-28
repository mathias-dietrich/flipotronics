//
//  Patch.h
//  Deus
//
//  Created by Mathias Dietrich on 15.07.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef Preset_h
#define Preset_h
#include <JuceHeader.h>

#include "Param.h"
#include "Enums.h"

class Preset{
public:
    String name;
    String author;
    String desc;
    std::map<E_Module,std::map<int, Param> > params;
    
    
};
#endif /* Preset_h */
