//
//  AmpComponent.h
//  synth1
//
//  Created by Mathias Dietrich on 13.07.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef AmpComponent_h
#define AmpComponent_h

class AmpComponent :  public AbstractComponent {
public:
    
    AmpComponent(){
        
    }
    
    ~AmpComponent(){
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
        for(auto it = std::begin(children); it != std::end(children); ++it) {
            auto c = *it;
            c->setDials();
        }
    }
    
    void build(Node node) override{
       for(auto it = std::begin( node.childen); it != std::end( node.childen); ++it) {
           Node node = *it;
           if(node.type == 0){ //Component
               current = factory->get(node.name);
               current->node = node;
               this->addAndMakeVisible(current);
               children.push_back(current);
           }
           if(node.type == 1){ // Widget
               current->build(node);
           }
       }
    }
    
    void resized() override{
        for(auto it = std::begin(children); it != std::end(children); ++it) {
            AbstractComponent *c = *it;
            Node n = c->node;
            c->setBounds(n.x,n.y,n.width,n.height);
            c->resized();
            c->setVisible(n.isVisible);
        }
    }
    
    AbstractComponent *current;
    WidgetFactory widgetFactory;
    Factory * factory;
};

#endif /* AmpComponent_h */
