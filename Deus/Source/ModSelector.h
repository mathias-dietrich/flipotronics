//
//  ModSelector.h
//  Deus
//
//  Created by Mathias Dietrich on 7/26/20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef ModSelector_h
#define ModSelector_h

#include "ModSwitch.h"

class ModSelector:  public IComponent, public Button::Listener{

   public:
    
    ModSelector(){
       
    }
    
    ~ModSelector(){
       for(auto it = std::begin(children); it != std::end(children); ++it) {
         delete *it;
       }
        for(auto it = std::begin(widgets); it != std::end(widgets); ++it) {
          delete *it;
        }
    }
    
    void build(Node * node) override{
        std::cout << node->name << std::endl;
               for(auto it = std::begin(node->children); it != std::end(node->children); ++it){
                     Node *n = *it;
                    if(node->name.compare("modswitch")==1){
                      ModView *wc = (ModView *) WidgetFactory::of()->get(n->name);
                      wc->node = n;
                      addAndMakeVisible(wc);
                      wc->setName(toString(n->paramId));
                      wc->addListener (this);
                      widgets.push_back(wc);
                   }
               }
    }
    
    void paint (Graphics& g) override {
        // Rectangle<int> r = getLocalBounds();
       //  auto width  = r.getWidth();
        // auto height  = r.getHeight();
         auto defaultColour = Colours::black;
         g.fillAll (juce::Colours::findColourForName (node->bgColor, defaultColour));
    }
       
     void resized() override{
         for(auto it = std::begin(widgets); it != std::end(widgets); ++it) {
             ModSwitch *p =  (ModSwitch*) *it;
             Node * node = p->node;
             p->setBounds(node->x , node->y, node->width,node->height);
             p->setVisible(node->isVisible);
         }
     }
    
    void buttonClicked(Button *  slider) override {
      //  int sid = slider->getName().getIntValue();
       // Model::of().par[sid] = slider->getValue();
        setDials();
    }
    
     void setDials() override{
         for(auto it = std::begin(widgets); it != std::end(widgets); ++it) {
       //      MasterPoti *p =  (MasterPoti*) *it;
           //  Node *node = p->node;
            // p->setValue(Model::of().par[node.paramId],dontSendNotification);
         }
     }
    
    std::map<int, Param> getParams() override{
        return params;
    }
    
    void setParams( std::map<int, Param> params) override{
        this->params = params;
    }
        
    private:
            std::map<int, Param> params;
    
private:

};
#endif /* ModSelector_h */
