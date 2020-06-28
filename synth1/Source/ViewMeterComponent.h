//
//  ViewMeterComponent.h
//  synth1
//
//  Created by Mathias Dietrich on 27.06.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef ViewMeterComponent_h
#define ViewMeterComponent_h

class ViewMeterComponent : public AbstractComponent{
    
public:
    
    void paint (Graphics& g){
        g.drawImageWithin(ImageFactory::of().png[eMeter], 0, 0, 120,80, juce::RectanglePlacement::stretchToFit, false);
        g.drawImageWithin(ImageFactory::of().png[eMeter], 150, 0, 120,80, juce::RectanglePlacement::stretchToFit, false);
    }
    
    void resized(){
        
    }
    
private:
    
};

#endif /* ViewMeterComponent_h */
