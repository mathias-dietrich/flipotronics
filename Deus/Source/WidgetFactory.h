//
//  WidgetFactory.h
//  Deus
//
//  Created by Mathias Dietrich on 15.07.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef WidgetFactory_h
#define WidgetFactory_h

#include "IWidget.h"

class WidgetFactory{
public:
    
    protected:
              static WidgetFactory *instance;
              WidgetFactory() { }
       
       public:
              static WidgetFactory * of() {
                  if (instance == 0)
                      instance = new WidgetFactory();
                  return instance;
              }
       
       void init(){
           
       }
    
    Widget * get(String type){
        if(type == "poti"){
            return new Poti();
        }
        return new MasterPoti();
    }
};
WidgetFactory * WidgetFactory::instance = 0;
    
#endif /* WidgetFactory_h */
