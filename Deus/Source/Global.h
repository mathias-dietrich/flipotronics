//
//  Global.h
//  Deus
//
//  Created by Mathias Dietrich on 7/27/20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef Global_h
#define Global_h


class Model;

class Global {
    
public:
    
    Global(){

    }

    // Build
    int version = 1;
    int build = 1;
    
    // Files and Folders
    String appRoot;
    String docRoot;
    
    // Sound selection
    String lastPatch;
    String lastBank;
    String lastPerformance;
    
    // Sample rates
    int lastSampleRate;
    int lastBlockSize;
    
    // Volume
    float lastMasterVolume;
    
    // Volume

    // UI
    int lastGuiZoom = 6; // 6 for small Mac, 7 for pro
    
};

#endif
