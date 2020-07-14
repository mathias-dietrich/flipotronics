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
        Rectangle<int> r = getLocalBounds();
        auto width  = r.getWidth();
        auto height  = r.getHeight();
        auto defaultColour = Colours::black;
        g.fillAll (C_BACKGROUND);
    }
    
    void setDials() override{
       for(auto it = std::begin(widgets); it != std::end(widgets); ++it) {
           Poti *p =  (Poti*) *it;
           Node node = p->node;
           int pid = node.paramId;
           setPoti(pid, p);
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
