//
//  VoiceSelector.h
//  synth1
//
//  Created by Mathias Dietrich on 09.07.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef VoiceSelector_h
#define VoiceSelector_h

#include "Widget.h"

class VoiceSelector :  public Component,  public Widget {
    
public:
    VoiceSelector(){
        
    }
    
    void paint (Graphics& g) override{
        Rectangle<int> r = getLocalBounds();
        width = r.getWidth();
        height = r.getHeight();
        
        // Volumes
        g.setColour(C_DARKGREY);
        g.fillRect (r);
        
        g.setColour(C_LIGHTGREY);
        g.drawEllipse(r.getX(),r.getY(),r.getWidth(), r.getHeight(),2.0f);
        
        g.drawEllipse(r.getX(),r.getY(),r.getWidth(), r.getHeight(),2.0f);
        
       
        g.setColour(C_DOT);
        float xVal = Model::of().par[P_VOICESELECT_X];
        float yVal = Model::of().par[P_VOICESELECT_Y];
        int xD = width * xVal - dotSize/2;
        int yD = height * yVal- dotSize/2;
        g.fillEllipse(xD,yD,dotSize, dotSize);
        
        g.drawLine(width/2,height/2,xVal*width, yVal*height, 3.0f);
    }
    
    void mouseDown (const MouseEvent& event) override{
        mouseDownX = event.position.x;
        mouseDownY = event.position.y;
        isMouseDown = true;
        
        // hit test
        isEditing = true;
    }
    
    void mouseUp (const MouseEvent& event) override{
        isMouseDown = false ;
        isEditing = false;
    }
    
    void mouseDrag (const MouseEvent& event)override {
        mouseDownY = event.position.y;
        mouseDownX = event.position.x;
        if(mouseDownX < dotSize/2){
            mouseDownX = dotSize/2;
        }
        if(mouseDownX >= width - dotSize/2){
            mouseDownX = width - dotSize/2;
        }
        
        if(mouseDownY < dotSize/2){
            mouseDownY = dotSize/2;
        }
        if(mouseDownY >= height - dotSize/2){
            mouseDownY = height - dotSize/2;
        }
        
        if(isEditing){
            Model::of().par[P_VOICESELECT_X] = mouseDownX  / width;
            Model::of().par[P_VOICESELECT_Y] = mouseDownY / height;
        }
    }
    
    void setDials() override{
        
    }
    
    //void resized() override{
             // setBounds(node.x, node.y, node.width, node.height);
   
    //}
    
   // float xVal = 0.5;
   // float yVal  = 0.7;
    
private:
    int dotSize = 25;
    
    float mouseDownX;
    float mouseDownY;
    bool isMouseDown;
    bool isEditing;
    int width;
    int height;
};


#endif /* VoiceSelector_h */
