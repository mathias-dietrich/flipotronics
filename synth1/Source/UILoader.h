//
//  UILoader.h
//  synth1
//
//  Created by Mathias Dietrich on 11.07.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef UILoader_h
#define UILoader_h

#include "AbstractComponent.h"
#include "ComponentFactory.h"

class UILoader{
public:
    void loadRoot(Node & rootNode, String xmlFile){
        File f = File(File::getCurrentWorkingDirectory().getFullPathName()).getChildFile("xml").getChildFile(xmlFile);
        XmlDocument dataDoc(f);
        std::unique_ptr<XmlElement> root{ dataDoc.getDocumentElement() };
        rootNode.name = "root";
        auto el =  root.release();
        parse(rootNode, el);
        el->deleteAllChildElements();
        delete el;
       // printNode(*rootNode);
    }
    
    void printNode(Node & node){
        std::cout << "type: "  << node.type << std::endl;
        std::cout <<"x: " << node.x << std::endl;
        std::cout <<"y: "  << node.y << std::endl;
        std::cout <<"width: "  << node.width << std::endl;
        std::cout <<"height: " << node.height << std::endl;
        std::cout <<"paramId: " << node.paramId << std::endl;
        for(auto it = std::begin( node.childen); it != std::end( node.childen); ++it) {
            printNode(*it);
        }
    }

    void parse(Node  & node, XmlElement * el){
        for(int i=0; i < el->getNumChildElements() ;++i){
            auto child = el->getChildElement(i);
            Node n;
           n.type = child->getIntAttribute("t");
           n.name = child->getStringAttribute("n");
           n.x = child->getIntAttribute("x");
           n.y = child->getIntAttribute("y");
           n.width = child->getIntAttribute("w");
           n.height = child->getIntAttribute("h");
            n.isVisible = child->getStringAttribute("v").compare("true") ==0;
   
           if(child->hasAttribute("p")){
               n.paramId = child->getIntAttribute("p");
           }
          if(child->hasAttribute("bg")){
                n.bgColor = child->getStringAttribute("bg");
           }
           node.childen.push_back(n);
           parse(node, child);
        }
    }
    
private:
    ComponentFactory componentFactory;
    
};

#endif /* UILoader_h */
