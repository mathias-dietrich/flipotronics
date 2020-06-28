//
//  MasterSwitch.h
//  synth1
//
//  Created by Mathias Dietrich on 28.06.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef MasterSwitch_h
#define MasterSwitch_h

class MasterSwitch : public AbstractComponent{
    
public:
    
     void paint (Graphics& g){
        Rectangle<int> r = getLocalBounds();

        // Volumes
        g.setColour (C_RED);
        g.fillRect (r);
         
         r.setX(r.getX()+2);
         r.setY(r.getX()+2);
         r.setWidth(r.getWidth()-4);
         r.setHeight(r.getHeight()-8);
         g.setColour (C_BLACK);
         g.fillRect (r);
     }
    
    
private:
};

#endif /* MasterSwitch_h */
