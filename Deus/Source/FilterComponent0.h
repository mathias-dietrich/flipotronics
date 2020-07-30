//
//  FilterComponent.h
//  Deus
//
//  Created by Mathias Dietrich on 17.07.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef FilterComponent_h
#define FilterComponent_h

#include "IComponent.h"
#include "WidgetFactory.h"
#include "IFactory.h"

class FilterComponent0 :  public IComponent , public Slider::Listener {
public:
    
    FilterComponent0(){
        Param p;
        p.module = mFilter0;
        p.valF = 0.5;
        p.type = uFloat;
        params[0] = params[1] = params[2] = params[3] = p;
        
        params[0].name = "Cutoff";
        params[1].name = "Resonance";
        params[2].name = "Type";
        params[3].name = "Drive";
        
        params[0].pid = 0;
        params[1].pid = 1;
        params[2].pid = 2;
        params[3].pid = 3;

        params[0].minVal = 20;
        params[1].minVal = 0;
        params[2].minVal = 0;
        params[3].minVal = -96;
        
        params[0].maxVal = 7000;
        params[1].maxVal = 100;
        params[2].maxVal = 9;
        params[3].maxVal = 18;

        params[0].stepVal = 1;
        params[1].stepVal = 1;
        params[2].stepVal = 1;
        params[3].stepVal = 0.01;
        
        params[0].type = uHZ;
        params[1].type = uProcent;
        params[2].type = uFilterType;
        params[3].type = uDb;
    }
    
    ~FilterComponent0(){
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
        g.fillAll (juce::Colours::findColourForName (node->bgColor, defaultColour));
        
        // Border
        g.setColour(C_MODULE_BORDER);
        g.drawRoundedRectangle(r, 13.0f, 5.0f);
        g.fillRoundedRectangle(0,0,width, 10, 15.0f);
        g.fillRect(0.0f,8.0f,width, 12.0f);
       // g.fillRoundedRectangle(0,height-5,width, 5, 15.0f);
        
        g.setColour(C_MODULE_BG);
        g.fillRect(2.0f,17.0f,width-4, height - 20);
         
        // Title
        g.setColour(C_MODULE_TITLE);
        g.drawText(node->title, 5,3,100,20,Justification::topLeft, false);
    }
       
    void setDials() override{
        int pid = 0;
        for(auto it = std::begin(widgets); it != std::end(widgets); ++it) {
            Poti *p =  (Poti*) *it;
            Node *node = p->node;
            Param pr = Model::of()->getParam(mFilter0, node->paramId);
            setPoti( node, p, params[pid], pr.valF);
            p->setValue(pr.valF);
            ++pid;
        }
    }
    
    void build(Node * node) override{
       std::cout << node->name << std::endl;
        int pid = 0;
       for(auto it = std::begin(node->children); it != std::end(node->children); ++it){
             Node *n = *it;
            if(n->name.compare("poti")==0){
              Poti *wc = (Poti *) WidgetFactory::of()->get(n->name);
              wc->node = n;
              addAndMakeVisible(wc);
              wc->setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag );
              wc->setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 100, 20);
              wc->setNumDecimalPlacesToDisplay(2);
              wc->setName(toString(n->paramId));
              wc->addListener (this);
              wc->setRange(0,1,0.01f);
              wc->setTitle(node->title);
              setPoti( n, wc, params[pid], Model::of()->preset.params[mFilter0][pid].valF);
              widgets.push_back(wc);
               ++pid;
           }
       }
        setDials();
    }
    
    void sliderValueChanged(Slider *  slider) override {
           int sid = slider->getName().getIntValue();
           Core::of()->update(mFilter0, sid, slider->getValue());
           setDials();
    }
    
    void resized() override{
        for(auto it = std::begin(widgets); it != std::end(widgets); ++it) {
            Poti *p =  (Poti*) *it;
            Node *node = p->node;
            p->setTitle(node->title);
            p->setBounds(node->x , node->y, node->width,node->height);
            p->setVisible(node->isVisible);
        }
    }
    String title = "";
    
     std::map<int, Param> getParams() override{
         return params;
     }
     
     void setParams( std::map<int, Param> params) override{
         this->params = params;
     }
    
    int getParamCount() override{
        return 4;
    }
         
     private:
             std::map<int, Param> params;
};
#endif /* FilterComponent_h */
