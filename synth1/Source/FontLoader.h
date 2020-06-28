/* (Auto-generated binary data file). */

#pragma once

#include <stdio.h>
#include <JuceHeader.h>

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
    
    Font& getAntaro() {
        return antaro;
    }
    
private:
    Font antaro;
};
