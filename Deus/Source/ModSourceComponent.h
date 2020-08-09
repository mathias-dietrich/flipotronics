//
//  ModSourceComponent.h
//  Deus
//
//  Created by Mathias Dietrich on 09.08.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef ModSourceComponent_h
#define ModSourceComponent_h

class ModSourceComponent :  public IComponent, public Button::Listener{
    public:
        ModSourceComponent(){
           
        }
        
        ~ModSourceComponent(){

        }
        
        void paint (Graphics& g) override {
             auto defaultColour = Colours::green;
             g.fillAll (juce::Colours::findColourForName (node->bgColor, defaultColour));
        }
    
    void buttonClicked(Button *  btn) override {
      //  int sid = slider->getName().getIntValue();
       // Model::of().par[sid] = slider->getValue();
        setDials();
    }
        
    void setDials() override{
 
               
          }
        
         void resized() override{
              for(auto it = std::begin(children); it != std::end(children); ++it) {
                    IComponent *c = *it;
                    Node *n = c->node;
                    c->setBounds(n->x,n->y,n->width,n->height);
                    c->resized();
                    c->setVisible(n->isVisible);
                    c->repaint();
                }
         }

        void build(Node * node) override{
            removeAllChildren();
            children.clear();
            for(auto it = std::begin( node->children); it != std::end( node->children); ++it) {
                Node *node = *it;
              
                
                if(node->type == 0){ //Component
                    std::cout << node->name << std::endl;
                    current = factory->get(node->name);
                    current->node = node;
                    current->factory = factory;
                    if(node->isVisible){
                        this->addAndMakeVisible(current);
                        current->repaint();

                    }else{
                       addChildComponent(current);
                    }
                    children.push_back(current);
                    
                    String xmlFile = "keysourcePanel.xml";
                    switch(Model::of()->editSel){
                         case s_NONE:
                             
                             break;
                         case s_VELOCITY:
                             
                             break;
                            
                         case s_AFTERTOUCH:
                             
                             break;
                            
                         case s_MODWHEEL:
                             
                             break;
                            
                         case s_KEYBOARD:
                             xmlFile = "keysourcePanel.xml";
                             break;
                            
                         case s_EXPRESSION:
                             
                             break;
                            
                         case s_ADSR0:
                            xmlFile = "adsr0.xml";
                             break;
                            
                         case s_ADSR1:
                             
                             break;
                         case s_ADSR2:
                             
                             break;
                         case s_LFO0:
                             
                             break;
                         case s_LFO1:
                             
                             break;
                         case s_LFO2:
                             
                             break;
                         case s_LFO3:
                             
                             break;
                         case s_FUNC0:
                             
                             break;
                         case s_FUNC1:
                             
                             break;
                         case s_FUNC2:
                             
                             break;
                         case s_RND0:
                             
                             break;
                         case s_RND1:
                             
                             break;
                         case s_RND2:
                             
                             break;
                         case s_COMB0:
                             
                             break;
                         case s_COMB1:
                             
                             break;
                         case s_COMB2:
                             
                             break;
                         case MACRO0:
                             
                             break;
                         case MACRO1:
                             
                             break;
                         case MACRO2:
                             
                             break;
                         case MACRO3:
                             
                             break;
                         case MACRO4:
                             
                             break;
                         case MACRO5:
                             
                             break;
                         case MACRO6:
                             
                             break;
                         case MACRO7:
                             
                             break;
                         case MACRO8:
                             
                             break;
                         case MACRO9:
                             
                             break;
                         case MACRO10:
                             
                             break;
                         case MACRO11:
                             
                             break;
                         case MACRO12:
                             
                             break;
                         case MACRO13:
                             
                             break;
                         case MACRO14:
                             
                             break;
                         case MACRO15:
                             
                             break;
                         case s_SOURCESCOUNT:
                             
                             break;
                     }
                    node->xmlFile = xmlFile;
                    Node *n = new Node();
                    uiloader.load(n, node->xmlFile);
                    current->build(n);
                }
            }
           repaint();
        }
        UILoader uiloader;
       
        private:
    
  MatrixSource editSel = s_NONE;

    };

#endif /* ModSourceComponent_h */
