//
//  OutputComponent.h
//  synth1
//
//  Created by Mathias Dietrich on 21.06.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef OutputComponent_h
#define OutputComponent_h

#include "AbstractComponent.h"
#include "Color.h"

class OutputComponent : public AbstractComponent,  public Slider::Listener{

public:
    
     OutputComponent () {
        graphZoom.setSliderStyle(Slider::SliderStyle::LinearHorizontal );
        graphZoom.setName("103");
        graphZoom.addListener (this);
        graphZoom.setRange(5, 4000,1);
        graphZoom.setValue(zoomX);
        addAndMakeVisible(graphZoom);

        graphZoomY.setSliderStyle(Slider::SliderStyle::LinearVertical );
        graphZoomY.setName("104");
        graphZoomY.addListener (this);
        graphZoomY.setRange(0.5, 4,0.01);
        graphZoomY.setValue(zoomY);
        graphZoomY.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
        addAndMakeVisible(graphZoomY);
     }
    
     ~OutputComponent () {
         
     }

    void sliderValueChanged(Slider *  slider) override {
        int sid = slider->getName().getIntValue();

        // Zoom
        if(sid==103){
           zoomX = slider->getValue();
           return;
        }
        // Zoom Y
        if(sid==104){
           zoomY = slider->getValue();
           return;
        }
    }
    
    void getNextAudioBlock() {
        Msg * m = Model::of().getFront();
        int offset = scopeOffset * samplesPerBlock;
        for(int i = 0; i < samplesPerBlock; ++i){
            scope[offset + i] = m->blockBuffer[i];
        }
        ++scopeOffset;
        if(scopeOffset == blocksPerSecond){
            scopeOffset = 0;
        }
    }
    
    void paint (Graphics& g) override{
        Rectangle<int> r = getLocalBounds();
        int width = r.getWidth();
        int height = r.getHeight() ;
        int half = height / 2 - 10;

         // Plot
        g.setColour (Colours::white);
        g.drawLine (0, half, width, half, 0.5f);
        g.drawLine (0, half-180, width, half-180, 0.5f);
        g.drawLine (0, half+180, width, half+180, 0.5f);

        // search positive zero crossing ==========================================
        int offset = 0;
        while(scope[offset] > 0){
           ++offset;
        }

        while(offset < width){
           if(scope[offset] <0 && scope[offset+1] >=0) {
               break;
           }
           ++offset;
        }
        // search positive zero crossing end  =====================================
        
        float lastX = 0;
        float lastY = half;
        float z = 1.0f / ((float)zoomX)  / ((float) width);
        g.setColour (C_WAVEDISPLAY);
        for(float i=0; i < width; i += 0.1f) {
           float pos = (offset + i)  * sampleRate * z;
           if(pos >= width){
               pos -= width;
           }
           float a = tanh(3.0f * interpolate(pos, scope));
           //float a = tanh(3.0f * scope[(int)pos]);
           float v = half - a * 180.0f * zoomY;
           g.drawLine(lastX, lastY, i, v, 2.1f);
           lastX = i;
           lastY = v;
       }
    }
    
    void resized() override{
        Rectangle<int> r = getLocalBounds();
        int width = r.getWidth();
        int height = r.getHeight();
        graphZoom.setBounds (5 , 0, width-10,  20);
        graphZoomY.setBounds (5 , 15, 20,  height-20);
    }
    
private:
    float zoomX = 220;
    float zoomY = 1;
    Slider graphZoom;
    Slider graphZoomY;
    
    float scope[SAMPLERATEMAX];
    int scopeOffset = 0;
    
    forcedinline float interpolate(int currentIndex, float * table ) noexcept{
        auto index0 = (unsigned int) currentIndex;
        auto index1 = index0 == (sr - 1) ? (unsigned int) 0 : index0 + 1;
        auto frac = currentIndex - (float) index0;
        auto value0 = table[index0];
        auto value1 = table[index1];
        return value0 + frac * (value1 - value0);
    }
};

#endif /* OutputComponent_h */
