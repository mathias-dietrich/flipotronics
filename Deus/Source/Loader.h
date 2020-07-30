//
//  Loader.h
//  Deus
//
//  Created by Mathias Dietrich on 15.07.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef Loader_h
#define Loader_h

class Loader{
    protected:
       static Loader *instance;
       Loader() { }
    
    public:
       static Loader * of() {
           if (instance == 0)
               instance = new Loader();
           return instance;
       }
    
    void init(){
        Preset preset;
        preset.name = "Hello";
        preset.author = "Flipotronics";
        preset.desc = "Inital Preset";
        

        preset.params[mMacro][16].valF = 440.0f;

        Model::of()->preset = preset;
    }
};
Loader * Loader::instance = 0;

#endif /* Loader_h */
