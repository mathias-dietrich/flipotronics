//
//  Curve.h
//  synth1
//
//  Created by Mathias Dietrich on 12.06.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef Curve_h
#define Curve_h

#include <stdio.h>
#include <JuceHeader.h>


#define CURVESAMPLES 200
class Curve {

public:
    float sample[CURVESAMPLES];
    
    void set(float prozent){
        if(prozent==0){
            for(int i=0; i < CURVESAMPLES;++i){
                sample[i] = i / ((float)CURVESAMPLES);
            }
            return;
        }
        float pr = prozent / 10.0f;
        float cs = CURVESAMPLES;
        
        float cof = 0;
         if(prozent>0){
             cof = 1.0f + pr;
         }else{
             cof =  1.0 / (1.0f - pr);
         }
        for(int i=0; i < CURVESAMPLES;++i){
            sample[i] = pow(i/cs, cof);
        }
    }

    float getScaled(int pos, int max){
        int p = pos * CURVESAMPLES / max;
        return sample[p];
    }
    
private:
   
};

#endif /* Curve_h */
