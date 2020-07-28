//
//  OutputMeter.h
//  Deus
//
//  Created by Mathias Dietrich on 15.07.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef OutputMeter_h
#define OutputMeter_h


#include "IWidget.h"
#include "Colors.h"

class OutputMeter : public Component,  public Widget {
    
public:
    OutputMeter(){

    }

    void paint (Graphics& g) override{
        Rectangle<int> r = getLocalBounds();

        // Volumes
        g.setColour (C_BLACK);
        g.fillRect (r);
         
        drawChannel(g,1, 10);
        drawChannel(g,1, 25);
    }
    
    void drawChannel(Graphics& g, float val, int x){
        for(int i=0;i < 8;i++){
            switch(i){
            case 0:
                // > 0 Db
                if(val>= 0){
                     g.setColour (juce::Colours::red);
                }else{
                     g.setColour (juce::Colours::darkgreen);
                }
            break;
            
           case 1:
                if(val> -10){
                   g.setColour (juce::Colours::yellow);
              }else{
                   g.setColour (juce::Colours::darkgreen);
              }
            break;
                   
            case 2:
                if(val> -20){
                   g.setColour (juce::Colours::lightgreen);
               }else{
                   g.setColour (juce::Colours::darkgreen);
               }
                break;
            
            case 3:
                if(val> -30){
                        g.setColour (juce::Colours::lightgreen);
                   }else{
                       g.setColour (juce::Colours::darkgreen);
                   }
                break;
            
            case 4:
                if( val> -40){
                    g.setColour (juce::Colours::lightgreen);
               }else{
                   g.setColour (juce::Colours::darkgreen);
               }
                break;
            
            case 5:
                if(val> -50){
                    g.setColour (juce::Colours::lightgreen);
               }else{
                   g.setColour (juce::Colours::darkgreen);
               }
                break;
            
            case 6:
                if(val> -60){
                    g.setColour (juce::Colours::lightgreen);
               }else{
                   g.setColour (juce::Colours::darkgreen);
               }
                break;
                    
            case 7:
                if(val> -70){
                     g.setColour (juce::Colours::lightgreen);
                }else{
                    g.setColour (juce::Colours::darkgreen);
                }
                break;
            }

            Rectangle<int> r;
            r.setWidth(10);
            r.setHeight(4);
            r.setX(x);
            r.setY(1 + i * 6);
            g.fillRect (r);
        }
    }
    
    void setDials() override{
        
    }
    
    //void resized() override{
             // setBounds(node.x, node.y, node.width, node.height);
     //  }
    
private:
};
#endif /* OutputMeter_h */
