//
//  UILoader.h
//  Deus
//
//  Created by Mathias Dietrich on 16.07.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef UILoader_h
#define UILoader_h

#include "IComponent.h"
#include "ComponentFactory.h"

class UILoader{
public:
    void load(Node * node, String xmlFile){
        File f = File(File::getCurrentWorkingDirectory().getFullPathName()).getChildFile("xml").getChildFile(xmlFile);
        if(!f.exists()){
            std::cout << "XML file missing " << f.getFullPathName() << std::endl;
        }
        XmlDocument dataDoc(f);
        std::unique_ptr<XmlElement> root{ dataDoc.getDocumentElement() };
        node->name = "root";
        auto el =  root.release();
        parse(node, el);
        el->deleteAllChildElements();
        delete el;
    }

    void parse(Node  * node, XmlElement * el){
        for(int i=0; i < el->getNumChildElements() ;++i){
            auto child = el->getChildElement(i);
           Node *n = new Node();
            n->type = child->getIntAttribute("t");
            n->name = child->getStringAttribute("n");
            n->x = child->getIntAttribute("x");
            n->y = child->getIntAttribute("y");
            n->width = child->getIntAttribute("w");
            n->height = child->getIntAttribute("h");
            n->isVisible = child->getStringAttribute("v").compare("true") ==0;
   
            if(child->hasAttribute("p")){
                n->paramId = child->getIntAttribute("p");
            }
            if(child->hasAttribute("bg")){
                n->bgColor = child->getStringAttribute("bg");
            }
            if(child->hasAttribute("title")){
                n->title = child->getStringAttribute("title");
            }
            if(child->hasAttribute("xml")){
                n->xmlFile= child->getStringAttribute("xml");
            }
            node->childen.push_back(n);
            parse(n, child);
        }
        
    }
    
private:
    ComponentFactory componentFactory;
    
};

#endif /* UILoader_h */
