//
//  DebugComponent.h
//  synth1
//
//  Created by Mathias Dietrich on 27.06.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef DebugComponent_h
#define DebugComponent_h

class DebugComponent : public AbstractComponent{
    
public:
    
     void paint (Graphics& g){
        Rectangle<int> r = getLocalBounds();

        // Debug speed of render
        g.setFont (11.0f);

        // Time taken in the Render Loop
        float taken = Model::of().timeTaken * 0.000001f;
        if(taken > processor->maxTimeMsec){
         g.setColour (Colours::red);
        }else{
         g.setColour (C_GREENTEXT);
        }
        float cpu = taken / processor->maxTimeMsec * 100.0f;
        g.drawFittedText ("CPU: " +  String(cpu,2) + "%  Taken: " + String(taken,3) + " msec  Max: " + String(processor->maxTimeMsec,3) + " msec", r, Justification::topLeft, 1);

        // Volumes
        g.setColour (C_GREENTEXT);
        g.setFont (15.0f);

        r.setY(20);
        g.drawFittedText ("Peak: " + String(Model::of().sumPeakL), r, Justification::topLeft, 1);

        r.setY(40);
        g.drawFittedText ("RMS: " + String(Model::of().sumRMSL,2), r, Justification::topLeft, 1);
         
         
     }
    
    void setDials() override{
           
    }
    
    Synth1AudioProcessor * processor;
    
private:
};
#endif /* DebugComponent_h */
