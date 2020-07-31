//
//  LfoComponent.h
//  Deus
//
//  Created by Mathias Dietrich on 7/31/20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef LfoComponent_h
#define LfoComponent_h

#include "IComponent.h"
#include "MasterPoti.h"
#include "OutputMeter.h"
#include "MasterSwitch.h"
#include "MasterPoti.h"
#include "Poti.h"

#include "WidgetFactory.h"
#include "IFactory.h"

class LfoComponent : public IComponent, public Slider::Listener{

public:

        LfoComponent(){
            Param p;
            p.module = getIndex();
            p.valF = 0.5;
            p.type = uFloat;
            params[0] = params[1] = params[2] = p;

            params[0].pid = 0;
            params[1].pid = 1;
            params[2].pid = 2;

            params[0].minVal = 0;
            params[1].minVal = 0.1;
            params[2].minVal = 0;

            params[0].maxVal = 5;
            params[1].maxVal = 5;
            params[2].maxVal = 1;

            params[0].stepVal = 1;
            params[1].stepVal = 0.01;
            params[2].stepVal = 0.01;

            params[0].name = "Wave";
            params[1].name = "Freq";
            params[2].name = "Vol Osc0";
            
            params[1].type = uHZ;
        }
        
        ~LfoComponent(){
           for(auto it = std::begin(children); it != std::end(children); ++it) {
             delete *it;
           }
            for(auto it = std::begin(widgets); it != std::end(widgets); ++it) {
              delete *it;
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
                   wc->setTitle(n->title);
                   setPoti( n, wc, params[pid], Model::of()->preset.params[getIndex()][pid].valF);
                   widgets.push_back(wc);
                }
                ++pid;
            }
            setDials();
        }
        
        void paint (Graphics& g) override {
            Rectangle<float> r = convertRect(getLocalBounds());
           auto width  = r.getWidth();
           auto height  = r.getHeight();
           
           // Fill
           auto defaultColour = Colours::green;
           g.fillAll (juce::Colours::findColourForName (node->bgColor, defaultColour));

           g.fillAll (defaultColour);
           
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
           g.drawText(node->title, 5,3,100,20,Justification::topLeft, false);
        }
           
         void resized() override{
             for(auto it = std::begin(widgets); it != std::end(widgets); ++it) {
                 Poti *p =  (Poti*) *it;
                 Node * node = p->node;
                 p->setBounds(node->x , node->y, node->width,node->height);
                 p->setVisible(node->isVisible);
             }
         }
        
        void sliderValueChanged(Slider *  slider) override {
            int sid = slider->getName().getIntValue();
            Core::of()->update(getIndex(), sid, slider->getValue());
            setDials();
        }
        
         void setDials() override{
             for(auto it = std::begin(widgets); it != std::end(widgets); ++it) {
                 Poti *p =  (Poti*) *it;
                 Node *node = p->node;
                 Param pr = Model::of()->getParam(getIndex(), node->paramId);
                 p->setValue(pr.valF);
             }
         }

        std::map<int, Param> getParams() override{
            return params;
        }
        
        void setParams( std::map<int, Param> params) override{
            this->params = params;
        }
        
        int getParamCount() override{
               return 3;
        }
    
    int offset;
    
    private:
        std::map<int, Param> params;
    
        E_Module getIndex(){
            switch(offset){
                case 0:
                    return mLFO0;
                    
                case 1:
                    return mLFO1;
                
                case 2:
                    return mLFO2;
                    
                 case 3:
                    return mLFO3;
            }
            return mLFO0;
        }
};

#endif /* LfoComponent_h */
