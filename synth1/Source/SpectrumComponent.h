
  /*
  ==============================================================================
    spectrumComponent.h
    Created: 25 Apr 2017 8:22:32pm
    Author:  Christofero Pollano
  ==============================================================================
*/

#ifndef spectrumComponent_H_INCLUDED
#define spectrumComponent_H_INCLUDED

#include <stdio.h>
#include <JuceHeader.h>

#include "CircularBuffer.h"

//==============================================================================
/*
*/
class SpectrumComponent : public Component , private Timer{
    
 public:
    SpectrumComponent (): forwardFFT (fftOrder), window (fftSize, dsp::WindowingFunction<float>::hann) {
        setOpaque (true);
        startTimerHz (10);
        isInit = true;
    }

    ~SpectrumComponent () {}
    
    void paint (Graphics& g) override {
        g.fillAll (Colours::black);
        g.setOpacity (1.0f);
        g.setColour (Colours::lightgreen);
        drawFrame(g);
    }
    
    void pushNextSampleIntoFifo (float sample) noexcept
    {
        if(!isInit) return;
        if (fifoIndex == fftSize)    // [11]
        {
            if (! nextFFTBlockReady) // [12]
            {
                zeromem (fftData, sizeof (fftData));
                memcpy (fftData, fifo, sizeof (fifo));
                nextFFTBlockReady = true;
            }
            fifoIndex = 0;
        }
        fifo[fifoIndex++] = sample;  // [12]
    }
    
    void setNextAudioBlock (AudioBuffer<float>& buffer)
    {
        auto* channelDataL = buffer.getReadPointer (0);
        for (auto i = 0; i < samplesperblock; ++i){
            pushNextSampleIntoFifo (channelDataL[i]);
        }
    }
    
    void drawFrame (Graphics& g)
    {
         for (int i = 1; i < scopeSize; ++i)
           {
               auto width  = getLocalBounds().getWidth();
               auto height = getLocalBounds().getHeight();
               
               float fromX = (float) jmap (i - 1, 0, scopeSize - 1, 0, width);
               float fromY = (float) jmap (scopeData[i - 1], 0.0f, 1.0f, (float) height, 0.0f);
               float toX =  (float) jmap (i, 0, scopeSize - 1, 0, width);
               float toY =  jmap (scopeData[i], 0.0f, 1.0f, (float) height, 0.0f);
              // g.drawLine (fromX,fromY,toX,toY);

               Rectangle<float> r;
               r.setX(fromX);
               r.setY(fromY);
               r.setWidth(toX-fromX);
               r.setHeight(height-fromY);
               
               g.fillRect(r);
           }
    }
    
    void timerCallback() override
    {
        if (nextFFTBlockReady)
        {
            drawNextFrameOfSpectrum();
            nextFFTBlockReady = false;
            repaint();
        }
    }
    
   void drawNextFrameOfSpectrum()
    {
        window.multiplyWithWindowingTable (fftData, fftSize);      // [1]
     
        forwardFFT.performFrequencyOnlyForwardTransform (fftData); // [2]
     
        auto mindB = -100.0f;
        auto maxdB =    0.0f;
        
        //std:: cout << fftSize << std::endl;
     
        for (int i = 0; i < scopeSize; ++i)                        // [3]
        {
            auto skewedProportionX = 1.0f - std::exp (std::log (1.0f - i / (float) scopeSize) * 0.2f);
            auto fftDataIndex = jlimit (0, fftSize / 2, (int) (skewedProportionX * fftSize / 2));
            auto level = jmap (jlimit (mindB, maxdB, Decibels::gainToDecibels (fftData[fftDataIndex])
                                                   - Decibels::gainToDecibels ((float) fftSize)),
                               mindB, maxdB, 0.0f, 1.0f);
     
            scopeData[i] = level;                                  // [4]
        }
    }
  
    void setFFTSize (size_t N)
    {

    }
    
    void setNumberOfSpectrums (size_t N)
    {

    }

    enum
    {
        fftOrder  = 11,            // 11
        fftSize   = 1 << fftOrder, // 1
        scopeSize = 128            // 256
    };
    
 private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SpectrumComponent)

    dsp::FFT forwardFFT;                  // [4]
    dsp::WindowingFunction<float> window; // [5]
    float fifo [fftSize];                 // [6]
    float fftData [2 * fftSize];          // [7]
    int fifoIndex = 0;                    // [8]
    bool nextFFTBlockReady = false;       // [9]
    float scopeData [scopeSize];          // [10]
    Colour freshLineColour;
    bool isInit = false;
};

#endif  // spectrumComponent_H_INCLUDED
