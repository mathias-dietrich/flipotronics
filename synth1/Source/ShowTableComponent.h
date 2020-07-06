//
//  ShowTableComponent.h
//  synth1
//
//  Created by Mathias Dietrich on 06.07.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef ShowTableComponent_h
#define ShowTableComponent_h

#include "AbstractComponent.h"

class ShowTableComponent:  public AbstractComponent{
   public:
   
    ShowTableComponent () {
       
    }
   
    ~ShowTableComponent () {
        
    }
    
     void paint (Graphics& g) override{
         
         int tableId = 20;
         
         int freq = 440.0f * pow(2.0f, ((tableId - 69) / 12.0f));
         Rectangle<int> r = getLocalBounds();
         auto width  = r.getWidth();
         auto height  = r.getHeight();
         auto half  = height / 2;
         
         g.setColour(Colours::orange);
         g.fillRect(r);
         
         g.setColour(Colours::black);
         int lastY = half;
         for(int i=0; i < 2048; i++){
             int y = half - half * wt->sinBuffer[tableId][i] ;
             int x = i * width / 2048;
             g.drawLine(x-1,lastY, x ,y);
             lastY = y;
         }
         
         g.drawFittedText ("ID: " + String(tableId) + " Hz: " + String(freq), r, Justification::bottomLeft, 1);
     }
    
     void init(float sampleRate, int samplesPerBlock){
        this->samplesPerBlock = samplesPerBlock;
        this->sampleRate = sampleRate;
        wt->init(sampleRate, samplesPerBlock);
     }

    void resized() override{
        
    }
    
    void setDials() override{
        
    }
    
private:
    float sampleRate;
    int samplesPerBlock;
    WaveTable *wt = WaveTable::of();
};
#endif /* ShowTableComponent_h */
