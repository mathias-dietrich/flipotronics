//
//  ModSwitch.h
//  Deus
//
//  Created by Mathias Dietrich on 7/26/20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef ModSwitch_h
#define ModSwitch_h

class ModSwitch : public TextButton,  public Widget, public Button::Listener  {
    
public:
    ModSwitch(){

    }
    
    ~ModSwitch(){

    }

    void paint (Graphics& g) override{
        Rectangle<int> r = getLocalBounds();

        // Volumes
        g.setColour (C_DARKGRAY);
        g.fillRect (r);
        
        g.setColour (C_DARKGRAY);
        g.fillRect ( 0,0,240,20);
        
        g.setColour(C_LIGHTGRAY);
        g.drawRect(r,1);
        
        // Title
      g.setColour(C_MODULE_TITLE);
      g.drawFittedText(node->title, 0,0,240,20,Justification::centred, false);
         
    }
    
    void buttonClicked (Button *) override{
           
    }
    
    void setDials() override{
        
    }
    
    void resized() override{
         
    }
    
private:
};

#endif /* ModSwitch_h */
