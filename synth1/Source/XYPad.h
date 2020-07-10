//
//  XYPad.h
//  synth1
//
//  Created by Mathias Dietrich on 09.07.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef XYPad_h
#define XYPad_h

class XYPad : public AbstractComponent {
    
public:
    XYPad(){

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
        float xVal = Model::of().par[P_PERFORM_X];
        float yVal = Model::of().par[P_PERFORM_Y];
         int xD = width * xVal - dotSize/2;
         int yD = height * yVal- dotSize/2;
         g.fillEllipse(xD,yD,dotSize, dotSize);
         
         g.drawLine(width/2,height/2,xVal*width, yVal*height, 3.0f);
    }
    
    void setDials() override{
        
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
              Model::of().par[P_PERFORM_X] = mouseDownX  / width;
              Model::of().par[P_PERFORM_Y] = mouseDownY / height;

          }
      }
      
    
private:
    int dotSize = 25;
    
    float mouseDownX;
    float mouseDownY;
    bool isMouseDown;
    bool isEditing;
    int width;
    int height;
};

#endif /* XYPad_h */
