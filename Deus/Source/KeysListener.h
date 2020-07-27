//
//  KeysListener.h
//  Deus
//
//  Created by Mathias Dietrich on 7/27/20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef KeysListener_h
#define KeysListener_h

class KeysListener{
    
public:
    
    bool keyPressed (const KeyPress &key, Component *originatingComponent){
        std::cout << key.getKeyCode() << std::endl;
        switch(key.getKeyCode()){
            case 61: // zoom in
            {
                int z = Model::of()->global.lastGuiZoom;
                ++z;
                if(z>11)z=11;
                Model::of()->global.lastGuiZoom = z;
                break;
            }
                
            case 45: // zoom out
            {
                int z = Model::of()->global.lastGuiZoom;
                --z;
                if(z<1)z=1;
                Model::of()->global.lastGuiZoom = z;
                break;
            }
        }
        return true;
    }
      
     
    bool  keyStateChanged (bool isKeyDown, Component *originatingComponent){
        std::cout << isKeyDown << std::endl;
        return true;
    }
     
};


#endif /* KeysListener_h */
