//
//  Curve.h
//  Deus
//
//  Created by Mathias Dietrich on 8/2/20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef Curve_h
#define Curve_h

#include <stdio.h>
#include <JuceHeader.h>


#define CURVESAMPLES 1000
class Curve {

public:
    double sample[CURVESAMPLES];
    float prozentOld = 0;
    
    Curve(){
        for(int i=0; i < CURVESAMPLES;++i){
            sample[i] = i / ((float)CURVESAMPLES);
        }
    }
    
    void set(float prozent){
        
        // check if the table needs rebuildng
        if(prozentOld == prozent){
            return;
        }
        prozentOld = prozent;
        
        // rebuild table
        if(prozent==0){
            for(int i=0; i < CURVESAMPLES;++i){
                sample[i] = i / ((float)CURVESAMPLES);
            }
            return;
        }

        // https://www.desmos.com/calculator/2p237rbfrn
        float cs = CURVESAMPLES;
        float factor = 3.0f;
        float cof = prozent * factor * 0.01f;
        float e = std::exp(1.0);
        for(int i=0; i < CURVESAMPLES;++i){
            sample[i] = pow(float(i/cs), pow(e, cof));
        }
    }

    float getScaled(int pos, int max){
        int p = pos * CURVESAMPLES / max;
        if(p>=CURVESAMPLES){
            return 1.0;
        }
        return sample[p];
    }
    
private:
   
};
#endif /* Curve_h */
