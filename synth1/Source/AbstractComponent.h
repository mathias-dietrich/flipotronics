//
//  AbstractComponent.h
//  synth1
//
//  Created by Mathias Dietrich on 25.06.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef AbstractComponent_h
#define AbstractComponent_h

#include <stdio.h>
#include <JuceHeader.h>

struct Node{
    int width;
    int height;
    int x;
    int y;
    String type;
    std::vector<Node> childen;
    int paramId;
};

class AbstractComponent  :  public Component{

public:
    
    AbstractComponent(){
        
    }
    
    virtual ~AbstractComponent () {
        
    }
    
    void init(float sampleRate, int samplesPerBlock){
        this->samplesPerBlock = samplesPerBlock;
        this->sampleRate = sampleRate;
        this->sr = sampleRate * OVERSAMPLING;
        this->blocksPerSecond = sampleRate / samplesPerBlock;
    }
    
   
    
    Node node;
    
    virtual void setDials()=0;
    
    virtual void build(Node node)=0;
    
    float sampleRate;
    int samplesPerBlock;
    float sr;
    int blocksPerSecond;
    
    std::vector<AbstractComponent *> children;
    
private:
};

#endif /* AbstractComponent_h */
