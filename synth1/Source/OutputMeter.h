//
//  OutputMeter.h
//  synth1
//
//  Created by Mathias Dietrich on 28.06.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef OutputMeter_h
#define OutputMeter_h

class OutputMeter : public AbstractComponent{
    
public:
    
     void paint (Graphics& g){
        Rectangle<int> r = getLocalBounds();

        // Volumes
        g.setColour (C_BLACK);
        g.fillRect (r);
         

         drawChannel(g, 1.0f, 10);
         drawChannel(g, 1.0f, 25);
     }
    
    void drawChannel(Graphics& g, float val, int x){
        for(int i=0;i < 8;i++){
            g.setColour (juce::Colours::lightgreen);
            if(i==0){
                 g.setColour (juce::Colours::red);
            }
            if(i==1){
                 g.setColour (juce::Colours::yellow);
            }
            Rectangle<int> r;
            r.setWidth(10);
            r.setHeight(4);
            r.setX(x);
            r.setY(1 + i * 6);
            g.fillRect (r);
        }
    }
    
private:
};

#endif /* OutputMeter_h */
