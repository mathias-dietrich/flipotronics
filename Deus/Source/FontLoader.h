//
//  FontLoader.hpp
//  Deus
//
//  Created by Mathias Dietrich on 15.07.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#pragma once

#include <stdio.h>
#include <JuceHeader.h>

#include "Inc.h"

namespace FontLoaderAntaro
{
    extern const char*  Antaro_ttf;
    const int           Antaro_ttfSize = 64140;

}
// https://www.urbanfonts.com/fonts/modern-fonts.htm

class FontLoader{

public:
    
    FontLoader(){
        antaro = Font(Typeface::createSystemTypefaceFor(FontLoaderAntaro::Antaro_ttf, FontLoaderAntaro::Antaro_ttfSize));
    }
    
    virtual ~FontLoader(){
       
    }
    
    Font& getAntaro() {
        return antaro;
    }
    
private:
    Font antaro;
};

