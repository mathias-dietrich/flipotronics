//
//  FileManager.h
//  synth1
//
//  Created by Mathias Dietrich on 02.06.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef FileManager_h
#define FileManager_h

#include <stdio.h>
#include <JuceHeader.h>
#include "WaveTable.h"

class FileManager {       // The class

    public:
    const String path = "data.txt";
    
    void load(){
        File rp = File::getCurrentWorkingDirectory().getChildFile (path);
       
            File resourceFile (rp);
            
            if (! resourceFile.existsAsFile())
                   return;  // file doesn't exist
            
            FileInputStream inputStream (resourceFile); // [2]
            
            if (! inputStream.openedOk())
                   return;  // failed to open
        
        int paramId = 0;
            for(int i=0; i < 1024;++i){
               double v = inputStream.readDouble();
               par[paramId] = v;
               ++paramId;
            }
        std::cout << "loaded from  " << rp.getFullPathName() << std::endl;
    }
    
    void save(){
        File rp = File::getCurrentWorkingDirectory().getChildFile (path);
        File resourceFile (rp);
        
        FileOutputStream outputStream (resourceFile); // [2]
        outputStream.setPosition(0);
        
        if (! outputStream.openedOk())
               return;  // failed to open
        
        for(int i=0; i < 1024;++i){
            outputStream.writeDouble(par[i] );
        }
        outputStream.flush();
        std::cout << "Saved to " << rp.getFullPathName()  << std::endl;
    }
    
    private:

    
};
#endif /* FileManager_h */
