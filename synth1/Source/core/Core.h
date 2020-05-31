//
//  Core.hpp
//  synth1
//
//  Created by Mathias Dietrich on 30.05.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef Core_hpp
#define Core_hpp

#include <stdio.h>
#include <JuceHeader.h>

class Core {       // The class
  public:             // Access specifier
    Core(){
        
    }
    
    ~Core(){
        
    }
    
    void handle(AudioBuffer<float>& buffer, MidiBuffer& midiMessages);
    
};

#endif /* Core_hpp */
