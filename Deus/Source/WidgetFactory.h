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
#include "Poti.h"
#include "MasterPoti.h"
#include "ModView.h"

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
        
        if(type == "modview"){
            return new ModView();
        }
        return new MasterPoti();
    }
private:
    

};

    
#endif /* WidgetFactory_h */
