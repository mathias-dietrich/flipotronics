//
//  Model.h
//  Deus
//
//  Created by Mathias Dietrich on 15.07.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef Model_h
#define Model_h

#include <JuceHeader.h>
#include "Param.h"
#include "Defines.h"

using namespace std;

class Model{
    protected:
           static Model *instance;
           Model() { }
    
    public:
           static Model * of() {
               if (instance == 0)
                   instance = new Model();
               return instance;
           }
    
    void init(){
        
    }
    
    Param params[MAXPARAM];
    std::atomic<float> par[MAXPARAM * 4];
    
    atomic<float> sumPeakL;
    atomic<float> sumPeakR;
    E_Master masterSel;
    
private:

};


#endif /* Model_h */
