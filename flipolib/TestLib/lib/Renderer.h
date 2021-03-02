//
//  Renderer.h
//  TestLib
//
//  Created by Mathias Dietrich on 02.03.21.
//

#ifndef Renderer_h
#define Renderer_h

#include <AudioUnit/AudioUnit.h>

class Renderer{
public:
    virtual void render(AudioBufferList *ioData, int inNumberFrames) = 0;
};

#endif /* Renderer_h */
