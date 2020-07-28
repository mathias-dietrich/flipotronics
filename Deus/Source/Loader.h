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
        
        Param p;
        p.module = mMacro;
        p.pid = 0;
        p.name = "Macro0";
        p.valF = 0.5;
        p.type = uFloat;
        preset.params[mMacro][0] = preset.params[mMacro][1] = preset.params[mMacro][2] = preset.params[mMacro][3] =preset.params[mMacro][4] =preset.params[mMacro][5] =preset.params[mMacro][6] =preset.params[mMacro][7] =preset.params[mMacro][8] =preset.params[mMacro][9] =preset.params[mMacro][10] =preset.params[mMacro][11] =preset.params[mMacro][12] =preset.params[mMacro][13] =preset.params[mMacro][14] =preset.params[mMacro][15] = p;
        
        preset.params[mMacro][1].pid = 1;
        preset.params[mMacro][2].pid = 2;
        preset.params[mMacro][3].pid = 3;
        preset.params[mMacro][4].pid = 4;
        preset.params[mMacro][5].pid = 5;
        preset.params[mMacro][6].pid = 6;
        preset.params[mMacro][7].pid = 7;
        preset.params[mMacro][8].pid = 8;
        preset.params[mMacro][9].pid = 9;
        preset.params[mMacro][10].pid = 10;
        preset.params[mMacro][11].pid = 11;
        preset.params[mMacro][12].pid = 12;
        preset.params[mMacro][13].pid = 13;
        preset.params[mMacro][14].pid = 14;
        preset.params[mMacro][15].pid = 15;
        
        preset.params[mMacro][1].name = "Macro1";
        preset.params[mMacro][2].name = "Macro2";
        preset.params[mMacro][3].name = "Macro3";
        preset.params[mMacro][4].name = "Macro4";
        preset.params[mMacro][5].name = "Macro5";
        preset.params[mMacro][6].name = "Macro6";
        preset.params[mMacro][7].name = "Macro7";
        preset.params[mMacro][8].name = "Macro8";
        preset.params[mMacro][9].name = "Macro9";
        preset.params[mMacro][10].name = "Macro10";
        preset.params[mMacro][11].name = "Macro11";
        preset.params[mMacro][12].name = "Macro12";
        preset.params[mMacro][13].name = "Macro13";
        preset.params[mMacro][14].name = "Macro14";
        preset.params[mMacro][15].name = "Macro15";
        
        Model::of()->preset = preset;
    }
};
Loader * Loader::instance = 0;

#endif /* Loader_h */
