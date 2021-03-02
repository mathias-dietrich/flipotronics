//
//  Renderer.h
//  TestLib
//
//  Created by Mathias Dietrich on 02.03.21.
//

#ifndef Renderer_h
#define Renderer_h

class Renderer{
public:
    virtual void render(float *l, float *r, int noOfSamples) = 0;
};

#endif /* Renderer_h */
