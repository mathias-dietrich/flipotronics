//
//  OutputComponent.h
//  synth1
//
//  Created by Mathias Dietrich on 21.06.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef OutputComponent_h
#define OutputComponent_h
class OutputComponent : public Component, public Slider::Listener{

public:
    
     OutputComponent () {
        graphZoom.setSliderStyle(Slider::SliderStyle::LinearHorizontal );
        graphZoom.setName("103");
        graphZoom.addListener (this);
        graphZoom.setRange(5, 4000,1);
        graphZoom.setValue(zoom);
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
               zoom = slider->getValue();
               return;
           }
           // Zoom Y
           if(sid==104){
               zoomY = slider->getValue();
               return;
           }
       }
    
    void paint (Graphics& g) override{
        Rectangle<int> r = getLocalBounds();
        int width = r.getWidth();
        int height = r.getHeight() ;
        int half = height / 2 -10;
        
         // Plot
        g.setColour (Colours::white);
        g.drawLine (0, half, width, half, 0.5f);
        g.drawLine (0, half-180, width, half-180, 0.5f);
        g.drawLine (0, half+180, width, half+180, 0.5f);

        g.setColour (Colours::blue);
        drawPlot( g, half, width, scopeBuffer );
    }
    
    void drawPlot(Graphics& g, int half, int width, std::atomic<float> * buf ){
        
        // search positive zero crossing
        int offset =0;
        while(buf[offset] > 0){
            ++offset;
        }
        
        while(offset < width){
            if(buf[offset] <0 && buf[offset+1] >=0){
                break;
            }
            ++offset;
        }
        
        int lastX = 0;
        int lastY = half;
        int sr = samplerate * OVERSAMPLING;
        
        for(int i=0; i< width;++i){
            int p = offset + i;
          
            int pos = p  * sr / zoom  / width;
            if(pos >= width){
                pos -= width;
            }
            
            float a = tanh(3.0f * buf[pos]);
            int v = half - a * 180 * zoomY;
             g.drawLine (lastX, lastY, i, v, 1.0f);
            lastX = i;
            lastY = v;
        }
    }
    
    void resized() override{
        Rectangle<int> r = getLocalBounds();
        int width = r.getWidth();
        int height = r.getHeight();
        graphZoom.setBounds (0 ,height-20, width-10,  20);
        graphZoomY.setBounds (0 ,  0, 20,  385);
    }
    
private:
    float zoom = 440;
    float zoomY = 1;
    Slider graphZoom;
    Slider graphZoomY;
};

#endif /* OutputComponent_h */
