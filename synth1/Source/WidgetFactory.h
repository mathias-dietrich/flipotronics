//
//  WidgetFactory.h
//  synth1
//
//  Created by Mathias Dietrich on 12.07.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef WidgetFactory_h
#define WidgetFactory_h

class WidgetFactory{
public:
    
    Widget * get(String type){
  
        if(type == "masterporti"){
            return new MasterPoti();
        }
       
        return new MasterPoti();
    }
};


#endif /* WidgetFactory_h */
