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

class ShowTableComponent: public AbstractComponent{
   public:
   
    ShowTableComponent () {
       
    }
   
    ~ShowTableComponent () {
        
    }
    
    void build(Node node) override{
           
       }
    
     void paint (Graphics& g) override{
         int freq = 2;
         Rectangle<int> r = getLocalBounds();
         auto width  = r.getWidth();
         auto height  = r.getHeight();
         auto half  = height / 2;
         
         int sr = sampleRate * OVERSAMPLING;
         g.setColour(Colours::orange);
         g.fillRect(r);
         
         g.setColour(Colours::black);
         int lastY = half;
         
         for(int i=0; i < width; i++){
             int pos = freq * i * sr / width ;
             while(pos >= sr ){
                 pos -= sr;
             }
             int y = half - half * wt->sinBuffer[pos] ;
             g.drawLine(i-1,lastY, i ,y);
             lastY = y;
         }
         
         g.drawFittedText (" Hz: " + String(freq), r, Justification::bottomLeft, 1);
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
