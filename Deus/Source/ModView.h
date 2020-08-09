//
//  ModView.h
//  Deus
//
//  Created by Mathias Dietrich on 7/26/20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef ModView_h
#define ModView_h

#include <JuceHeader.h>
#include "IWidget.h"

class ModView : public TextButton,  public Widget{
    
public:
    ModView(){

    }
    
    ~ModView(){

    }

    void paint (Graphics& g) override{
        Rectangle<int> r = getLocalBounds();

        // Volumes
        g.setColour (C_BLACK);
        g.fillRect (r);
        
        g.setColour (C_DARKGRAY);
        g.fillRect ( 0,0,60,20);
        
        g.setColour(C_LIGHTGRAY);
        g.drawRect(r,1);
        
        // Title
      g.setColour(C_MODULE_TITLE);
      g.drawFittedText(node->title, 0,2,60,20,Justification::centredTop, false);
         
    }
    
    void setDials() override{
      
    }
    
    void resized() override{
         
    }
    
private:
      
};
#endif /* ModView_h */
