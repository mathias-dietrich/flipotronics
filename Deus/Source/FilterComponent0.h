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

class FilterComponent0 :  public IComponent  {
public:
    
    FilterComponent0(){
        
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
            setPoti(node, p, pr.valF);
            p->setValue(pr.valF);
            ++pid;
        }
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

     private:

};
#endif /* FilterComponent_h */
