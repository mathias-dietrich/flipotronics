//
//  LfoComponent.h
//  synth1
//
//  Created by Mathias Dietrich on 21.06.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef LfoComponent_h
#define LfoComponent_h

class LfoComponent: public Component{
   public:
   
    LfoComponent () {

    }
   
    ~LfoComponent () {
        
    }
    
     void paint (Graphics& g) override{
         Rectangle<int> r = getLocalBounds();
         auto width  = getLocalBounds().getWidth();
         auto height  = getLocalBounds().getHeight();
         
         g.setColour(Colours::orange);
         g.fillRect(r);
     }
    
     void init(float sampleRate, int samplesPerBlock){
           this->samplesPerBlock = samplesPerBlock;
           this->sampleRate = sampleRate;
     }

    void resized() override{
        
    }
    
private:
    float sampleRate;
    int samplesPerBlock;
    
};
#endif /* LfoComponent_h */
