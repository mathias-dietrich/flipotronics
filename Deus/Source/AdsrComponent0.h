//
//  AdsrComponent,h.h
//  Deus
//
//  Created by Mathias Dietrich on 8/1/20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef AdsrComponent_h_h
#define AdsrComponent_h_h

#include "IComponent.h"
#include "MasterPoti.h"
#include "OutputMeter.h"
#include "MasterSwitch.h"
#include "MasterPoti.h"
#include "Poti.h"

#include "WidgetFactory.h"
#include "IFactory.h"

class AdsrComponent0 : public IComponent{

public:
        AdsrComponent0(){

        }
        
        ~AdsrComponent0(){
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
            Core::of()->update(params[sid].module, params[sid].pid, slider->getValue());
            setDials();
        }
        
         void setDials() override{
             int pid = 0;
             for(auto it = std::begin(widgets); it != std::end(widgets); ++it) {
                 Poti *p =  (Poti*) *it;
                 Param pr = Model::of()->getParam(params[pid].module, params[pid].pid);
                 p->setValue(pr.valF);
                 ++pid;
             }
         }
    
    int offset;
    
    private:
    
        E_Module getIndex(){
            switch(offset){
                case 0:
                    return mAdsr0;
                    
                case 1:
                    return mAdsr1;
                
                case 2:
                    return mAdsr2;
            }
            return mAdsr0;
        }
};

#endif /* AdsrComponent_h_h */
