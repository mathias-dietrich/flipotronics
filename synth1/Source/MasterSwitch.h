//
//  MasterSwitch.h
//  synth1
//
//  Created by Mathias Dietrich on 28.06.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef MasterSwitch_h
#define MasterSwitch_h

class MasterSwitchFeel : public juce::LookAndFeel_V4
{
public:
    MasterSwitchFeel()
    {
         setColour (juce::TextButton::textColourOnId, juce::Colours::blue);
         setColour (juce::TextButton::textColourOffId, juce::Colours::white);
    }
    
    void drawButtonText (juce::Graphics& g, juce::TextButton& button, bool isMouseOverButton, bool isButtonDown) override
    {
        auto font = getTextButtonFont (button, button.getHeight()/2.6);
        g.setFont (font);
        g.setColour (button.findColour (button.getToggleState() ? juce::TextButton::textColourOffId
                                                                : juce::TextButton::textColourOffId)
                           .withMultipliedAlpha (button.isEnabled() ? 1.0f : 0.5f));
     
        auto yIndent = juce::jmin (4, button.proportionOfHeight (0.2f));
        auto cornerSize = juce::jmin (button.getHeight(), button.getWidth()) / 2;
     
        auto fontHeight = juce::roundToInt (font.getHeight() * 0.2f);
        auto leftIndent  = juce::jmin (fontHeight, 2 + cornerSize / (button.isConnectedOnLeft()  ? 4 : 2));
        auto rightIndent = juce::jmin (fontHeight, 2 + cornerSize / (button.isConnectedOnRight() ? 4 : 2));
        auto textWidth = button.getWidth() - leftIndent - rightIndent;
     
        if (textWidth > 0)
            /*
            g.drawFittedText (button.getButtonText(),
                              leftIndent, yIndent, textWidth, button.getHeight() - yIndent * 2,
                              juce::Justification::centred, 2);
             */
            g.drawFittedText (button.getButtonText(),
                                         leftIndent, button.getHeight()-30, textWidth, button.getHeight() - yIndent * 2,
                                         juce::Justification::centred, 2);
    }
    
    void drawButtonBackground (juce::Graphics& g, juce::Button& button, const juce::Colour& backgroundColour,bool shouldDrawButtonAsHighlighted, bool isButtonDown) override {
        
        Rectangle<int> r = g.getClipBounds();
        auto buttonArea = button.getLocalBounds();
        g.setColour (C_DARKGREY);
        if(isButtonDown){
             g.setColour (C_BUTTONDOWN);
        }
        g.fillRect (buttonArea);
        if(isButtonDown ||  button.getToggleState()){
            g.setColour (C_BUTTONDOWN_LED);
            g.fillEllipse(r.getWidth() / 2 -12, r.getHeight()/2 - 17, 20, 20);
        }
    }
};

class MasterSwitch : public TextButton {
    
public:
    
    MasterSwitchFeel feel;
    
    MasterSwitch(){
     setLookAndFeel (&feel);
    }
    
     E_Master masterSel;
    
    ~MasterSwitch() override
    {
        setLookAndFeel (nullptr);
    }
    
    /*
     void paint (Graphics& g) override{
        Rectangle<int> r = getLocalBounds();

        // Volumes
        g.setColour (C_RED);
        g.fillRect (r);
         
         r.setX(r.getX()+2);
         r.setY(r.getX()+2);
         r.setWidth(r.getWidth()-4);
         r.setHeight(r.getHeight()-8);
         g.setColour (C_BLACK);
         g.fillRect (r);
     }
     */
    
   
    
    void setDials() {
        
    }
    
    
private:
};

#endif /* MasterSwitch_h */
