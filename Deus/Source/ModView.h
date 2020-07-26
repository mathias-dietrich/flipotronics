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

class ModView : public TextButton,  public Widget, public Button::Listener  {
    
public:
    ModView(){

    }
    
    ~ModView(){

    }

    void paint (Graphics& g) override{
        Rectangle<int> r = getLocalBounds();

        // Volumes
        g.setColour (C_RED);
        g.fillRect (r);
        
        // Title
      g.setColour(C_MODULE_TITLE);
      g.drawText(node->title, 5,3,100,20,Justification::topLeft, false);
         
    }
    
    void buttonClicked (Button *) override{
           
    }
    
    void setDials() override{
        
    }
    
    void resized() override{
         
    }
    
private:
};
#endif /* ModView_h */
