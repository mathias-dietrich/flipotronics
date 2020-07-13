//
//  Factory.h
//  synth1
//
//  Created by Mathias Dietrich on 13.07.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef Factory_h
#define Factory_h

class Factory{
public:
    virtual AbstractComponent * get(String type) = 0;
};

#endif /* Factory_h */
