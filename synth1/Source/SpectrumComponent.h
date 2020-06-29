
  /*
  ==============================================================================
    spectrumComponent.h
    Author:  Flipflop
  ==============================================================================
*/
#ifndef spectrumComponent_H_INCLUDED
#define spectrumComponent_H_INCLUDED

#include <stdio.h>
#include <JuceHeader.h>
#include "CircularBuffer.h"
#include "Func.h"
#include "AbstractComponent.h"
//==============================================================================

class SpectrumComponent : public AbstractComponent , private Timer{
    
 public:
    SpectrumComponent (): forwardFFT (fftOrder), window (fftSize, dsp::WindowingFunction<float>::hann) {
        setOpaque (true);
        
        // Frequencies taken From Klark Analyzer
        freqTable[0] = 16.0f;
        freqTable[1] = 20.0f;
        freqTable[2] = 25.0f;
        freqTable[3] = 31.5f;
        freqTable[4] = 40.0f;
        freqTable[5] = 50.0f;
        freqTable[6] = 63.0f;
        freqTable[7] = 80.0f;
        freqTable[8] = 100.0f;
        freqTable[9] = 125.0f;
        freqTable[10] = 160.0f;
        freqTable[11] = 200.0f;
        freqTable[12] = 250.0f;
        freqTable[13] = 315.0f;
        freqTable[14] = 400.0f;
        freqTable[15] = 500.0f;
        freqTable[16] = 630.0f;
        freqTable[17] = 800.0f;
        freqTable[18] = 1000.0f;
        freqTable[19] = 1250.0f;
        freqTable[20] = 1600.0f;
        freqTable[21] = 2000.0f;
        freqTable[22] = 2500.0f;
        freqTable[23] = 3150.0f;
        freqTable[24] = 4000.0f;
        freqTable[25] = 5000.0f;
        freqTable[26] = 6300.0f;
        freqTable[27] = 8000.0f;
        freqTable[28] = 10000.0f;
        freqTable[29] = 12500.0f;
        freqTable[30] = 1600.0f;
        freqTable[31] = 20000.0f;
        sumLevel = 0.0f;
        startTimerHz (30);
    }

    ~SpectrumComponent () {}
    
    void paint (Graphics& g) override {
        Rectangle<int> r = getLocalBounds();
        auto width  = getLocalBounds().getWidth();
        auto height  = getLocalBounds().getHeight();
        
        g.fillAll (Colours::black);
        g.setOpacity (1.0f);
        g.setColour (Colours::lightgreen);
        drawFrame(g);
        
        // draw Sum
        Rectangle<int> rs;
        rs.setX(width-10);
        rs.setWidth(10);
        
        float level = linearToDecibles (sumLevel);
        float lin = 1.0f - level / -96;

        float scaled =   height * lin;
        rs.setY(height);
        rs.setHeight(-scaled);
        g.setColour (Colours::red);
        g.fillRect(rs);
        
        g.setColour (Colours::white);
     
        int steps = width / scopeSize;
        int x = 0;
        for (int i = 0; i < scopeSize; ++i){
            r.setX(x);
            float fr = freqTable[i];
            if(fr>999){
                g.drawFittedText (String( fr / 1000.0f, 1) + "K", r, Justification::bottomLeft, 1);
            }else{
                g.drawFittedText (String(fr, 0), r, Justification::bottomLeft, 1);
            }
            x += steps;
        }
    }

    void getNextAudioBlock ()
    {
        float * blockBuffer = Model::of().getFront()->blockBuffer;
        for (auto i = 0; i < samplesPerBlock; ++i){
            float sample = blockBuffer[i];
            if (fifoIndex == fftSize){
               if (! nextFFTBlockReady) {
                   zeromem (fftData, sizeof (fftData));
                   memcpy (fftData, fifo, sizeof (fifo));
                   nextFFTBlockReady = true;
               }
               fifoIndex = 0;
           }
           fifo[fifoIndex++] = sample;  // [12]
        }
    }
    
    void drawFrame (Graphics& g)
    {
        auto width  = getLocalBounds().getWidth();
        auto height = getLocalBounds().getHeight();
        for (int i = 1; i < scopeSize; ++i){
            float fromX = (float) jmap (i - 1, 0, scopeSize - 1, 0, width);
            float fromY = (float) jmap (scopeData[i - 1], 0.0f, 1.0f, (float) height, 0.0f);
            float toX =  (float) jmap (i, 0, scopeSize - 1, 0, width);
            Rectangle<int> r;
            r.setX(fromX + 2);
            r.setY(fromY);
            r.setWidth(toX - fromX - 4);
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
        window.multiplyWithWindowingTable (fftData, fftSize);
        forwardFFT.performFrequencyOnlyForwardTransform (fftData);
        auto mindB = -96.0f;
        auto maxdB =   0.0f;
        float levelTotal = 0;
        for (int i = 0; i < scopeSize; ++i)
        {
            float df = sampleRate / fftSize;
            float freq = freqTable[i];
            int fftDataIndex = freq/df + 6 ; // Why do we need to add 6 here ?? to make 440 look right
            float v = fftData[fftDataIndex] ;
            if(v > 0){
                levelTotal += v;
            }
            auto level = jmap (jlimit (mindB, maxdB, Decibels::gainToDecibels (v)
                 - Decibels::gainToDecibels ((float) fftSize)), mindB, maxdB, 0.0f, 1.0f);
            scopeData[i] = level;
            
        }
        sumLevel = levelTotal / scopeSize;
    }

    enum
    {
        fftOrder  = 12,            // 12
        fftSize   = 1 << fftOrder, // 4096
        scopeSize = 32            // 256
    };
    
    void setDials(){
        
    }
    
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
    float freqTable[32];
    std::atomic<float> sumLevel;
};

#endif  // spectrumComponent_H_INCLUDED
