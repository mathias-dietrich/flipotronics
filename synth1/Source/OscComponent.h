//
//  OscComponent.h
//  synth1
//
//  Created by Mathias Dietrich on 13.07.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef OscComponent_h
#define OscComponent_h

#include "AbstractComponent.h"
#include "WidgetFactory.h"
#include "Factory.h"

class OscComponent :  public AbstractComponent, public Slider::Listener {
public:
    
    OscComponent(){
        
    }
    
    ~OscComponent(){
        for(auto it = std::begin(children); it != std::end(children); ++it) {
            delete *it;
        }
        for(auto it = std::begin(widgets); it != std::end(widgets); ++it) {
            delete *it;
        }
    }
    
    void paint (Graphics& g) override {
        Rectangle<float> r = convertRect(getLocalBounds());
               auto width  = r.getWidth();
               auto height  = r.getHeight();
               
               // Fill
               auto defaultColour = Colours::black;
               g.fillAll (juce::Colours::findColourForName (node.bgColor, defaultColour));
               
               // Border
               g.setColour(C_MODULE_BORDER);
               g.drawRoundedRectangle(r, 13.0f, 5.0f);
               g.fillRoundedRectangle(0,0,width, 10, 15.0f);
               g.fillRect(0.0f,8.0f,width, 12.0f);
               g.fillRoundedRectangle(0,height-5,width, 5, 15.0f);
               
               g.setColour(C_MODULE_BG);
               g.fillRect(2.0f,17.0f,width-4, height - 22);
                
               // Title
               g.setColour(C_MODULE_TITLE);
               g.drawText(node.title, 5,3,100,20,Justification::topLeft, false);
    }
    
    void setDials() override{
       for(auto it = std::begin(widgets); it != std::end(widgets); ++it) {
           Poti *p =  (Poti*) *it;
           Node node = p->node;
           setPoti(node, p);
           p->setValue(Model::of().par[node.paramId],dontSendNotification);
       }
    }
    
    void build(Node node) override{
        if(node.type == 0){ //Component
              current = factory->get(node.name);
              current->node = node;
              this->addAndMakeVisible(current);
              children.push_back(current);
            return;
        }
        if(node.name == "poti"){
           Poti *wc = (Poti *)widgetFactory.get(node.name);
           wc->node = node;
           addAndMakeVisible(wc);
           wc->setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag );
           wc->setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 100, 20);
           wc->setNumDecimalPlacesToDisplay(2);
           wc->setName(toString(node.paramId));
           wc->addListener (this);
           wc->setRange(0,1,0.01f);
           wc->setTitle(node.title);
           widgets.push_back(wc);
        }
    }
    
    void sliderValueChanged(Slider *  slider) override {
        int sid = slider->getName().getIntValue();
        Model::of().par[sid] = slider->getValue();
        setDials();
    }
    
    void resized() override{
         for(auto it = std::begin(widgets); it != std::end(widgets); ++it) {
            MasterPoti *p =  (MasterPoti*) *it;
            Node node = p->node;
            p->setBounds(node.x , node.y, node.width,node.height);
            p->setVisible(node.isVisible);
        }
    }
    
    AbstractComponent *current;
    WidgetFactory widgetFactory;
    Factory * factory;
};


#endif /* OscComponent_h */
