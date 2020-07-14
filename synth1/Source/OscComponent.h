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
            p->setValue(Model::of().par[node.paramId],dontSendNotification);
           
           int pid = node.paramId;
           p->setRange(Model::of().params[pid].minVal,Model::of().params[pid].maxVal,Model::of().params[pid].stepVal);
           p->setTitle(Model::of().params[pid].name);
           // boxes[i].setText(params[pid].name);
            if( Model::of().params[pid].type == uWaveType){
                p->setTextValueSuffix(" " + getWaveType(E_WaveType(int(Model::of().par[pid]))));
                p->setValue(Model::of().par[pid], dontSendNotification);
            }else if( Model::of().params[pid].type == uFilterType){
                   p->setTextValueSuffix(" " + getFilterTypeString(MultiModeLadderFilterTypes(int(Model::of().par[pid]))));
                   p->setValue(Model::of().par[pid], dontSendNotification);
            }
            else if( Model::of().params[pid].type == uPhase){
                p->setTextValueSuffix(" degrees");
                p->setValue(Model::of().par[pid], dontSendNotification);
            }
            else if( Model::of().params[pid].type == uTimeMsec){
                p->setTextValueSuffix(" msec");
                p->setSkewFactor(0.5);
                p->setValue(Model::of().par[pid], dontSendNotification);
            }
            else if( Model::of().params[pid].type == uDb){
                p->setSkewFactor (6);
                p->setTextValueSuffix(" dB");
                p->setValue(Model::of().par[pid], dontSendNotification);
            }
            else if( Model::of().params[pid].type == uHZ){
                p->setSkewFactor (0.3);
                p->setTextValueSuffix(" Hz");
                p->setValue(Model::of().par[pid], dontSendNotification);
            }
            else if( Model::of().params[pid].type == uBool){
                bool test = Model::of().par[pid];
                String text = test ? " on" : " off" ;
                p->setTextValueSuffix(text);
            }
            else if( Model::of().params[pid].type == uCurve){
                p->setSkewFactor(1);
                p->setTextValueSuffix(" %");
                p->setValue(Model::of().par[pid], dontSendNotification);
            }
            else if( Model::of().params[pid].type == uMidiNote){
               p->setTextValueSuffix(" " + midiNote(Model::of().par[pid]));
               p->setValue(Model::of().par[pid], dontSendNotification);
            }
            else if( Model::of().params[pid].type == uDevision){
               p->setTextValueSuffix(" " + devision(Model::of().par[pid]));
               p->setValue(Model::of().par[pid], dontSendNotification);
            }
            else if( Model::of().params[pid].type == uArpMode){
                p->setSkewFactor(1);
                if(Model::of().par[pid]==0){
                     p->setTextValueSuffix(" SEQ");
                }else if (Model::of().par[pid]==1){
                     p->setTextValueSuffix(" ARP");
                }else{
                    p->setTextValueSuffix(" CHORD");
                }
                p->setValue(Model::of().par[pid], dontSendNotification);
            }
            else if( Model::of().params[pid].type == uChordMode){
                switch(((int)Model::of().par[pid])){
                    case 0:
                     p->setTextValueSuffix(" Singe ");
                    break;
                    
                    case 1:
                     p->setTextValueSuffix(" Quinte ");
                    break;
                        
                    case 2:
                     p->setTextValueSuffix(" Quarte ");
                    break;
                    
                    case 3:
                     p->setTextValueSuffix(" Root ");
                    break;
                        
                    case 4:
                     p->setTextValueSuffix(" Inv 1 ");
                    break;
                    
                    case 5:
                     p->setTextValueSuffix(" Inv 2 ");
                    break;
                }
               p->setValue(Model::of().par[pid], dontSendNotification);
            }
            else{
                p->setTextValueSuffix("");
                p->setValue(Model::of().par[pid], dontSendNotification);
            }
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
