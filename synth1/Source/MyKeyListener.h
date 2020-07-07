//
//  KeyListener.h
//  synth1
//
//  Created by Mathias Dietrich on 07.07.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef MyKeyListener_h
#define MyKeyListener_h

class MyKeyListener{
public:
    
    void handle(int key, String desc){
        std::cout << desc << " key: " << key << std::endl;
        
        switch(key){
            case 49: //1
                Model::of().showDebugWidgets =  ! Model::of().showDebugWidgets;
                break;

            case 50: //2
                break;

            case 51: //3
                break;

            case 52: //4
                break;

            case 53: //5
                break;

            case 54: //6
                break;

            case 55: //7
                break;

            case 56: //8
                break;

            case 57: //9
                break;
        }
    }
    
};
#endif /* MyKeyListener_h */
