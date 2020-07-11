//
//  WaveComponent.h
//  synth1
//
//  Created by Mathias Dietrich on 21.06.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef WaveComponent_h
#define WaveComponent_h

#include "AbstractComponent.h"

class WaveComponent :  public AbstractComponent, public ChangeListener, public Timer {
   
public:
    
    ~WaveComponent(){
        for(auto it = std::begin(children); it != std::end(children); ++it) {
          delete *it;
        }
    }
    
    enum TransportState
    {
        Stopped,
        Starting,
        Playing,
        Stopping,
        Pausing,
        Paused
    };
    
    void build(Node node) override{
           
       }
    
   WaveComponent () : thumbnailCache (5),  thumbnail (512, formatManager, thumbnailCache)  {
      setOpaque (true);

      addAndMakeVisible (&openButton);
      openButton.setButtonText ("Open...");
      openButton.onClick = [this] { openButtonClicked(); };
   
      addAndMakeVisible (&playButton);
      playButton.setButtonText ("Play");
      playButton.onClick = [this] { playButtonClicked(); };
      playButton.setColour (TextButton::buttonColourId, Colours::green);
      playButton.setEnabled (false);
   
      addAndMakeVisible (&stopButton);
      stopButton.setButtonText ("Stop");
      stopButton.onClick = [this] { stopButtonClicked(); };
      stopButton.setColour (TextButton::buttonColourId, Colours::red);
      stopButton.setEnabled (false);
       
     thumbnail.addChangeListener (this);
       
     formatManager.registerBasicFormats();
       
     startTimer (40);
   }
    
    void changeListenerCallback (ChangeBroadcaster* source) override
    {
        if (source == &transportSource)  transportSourceChanged();
        if (source == &thumbnail)        thumbnailChanged();
    }
    
    void transportSourceChanged()
    {
        if (transportSource.isPlaying())
            changeState (Playing);
        else
            changeState (Stopped);
    }

   
    
    void thumbnailChanged()
    {
        repaint();
    }
    
    void resized() override{
        openButton.setBounds(10,10,80,20);
         playButton.setBounds(110,10,80,20);
         stopButton.setBounds(210,10,80,20);
    }
    
    void init(int sampleRate, int samplesPerBlock){
         transportSource.prepareToPlay (samplesPerBlock, sampleRate);
    }
    
    void timerCallback() override
    {
        if(Model::of().hasPlayed){
            Model::of().hasPlayed = false;
            changeState(Stopped);
        }
        repaint();
    }
    
    void setDials() override{
        
    }
    
    void changeState (TransportState newState)
    {
        if (state != newState)
        {
            state = newState;
     
            switch (state)
            {
                case Stopped:                           // [3]
                    stopButton.setEnabled (false);
                    playButton.setEnabled (true);
                   // transportSource.setPosition (0.0);
                    break;
     
                case Starting:                          // [4]
                    playButton.setEnabled (false);
                   // transportSource.start();
                    break;
     
                case Playing:                           // [5]
                    stopButton.setEnabled (true);
                    break;
     
                case Stopping:                          // [6]
                   // transportSource.stop();
                    break;
            }
        }
    }
    
    void playButtonClicked()
    {
        Model::of().noOfSamplesToPlay = noOfSamples;
    }
    
    void stopButtonClicked()
    {
         Model::of().noOfSamplesToPlay = 0;
        if (state == Paused)
            changeState (Stopped);
        else
            changeState (Stopping);
    }
  
  void paint (Graphics& g) override {
      Rectangle<int> r = getLocalBounds();
      auto width  = getLocalBounds().getWidth();
      auto height  = getLocalBounds().getHeight();
      r.setY(50);
      g.setColour(Colours::black);
      g.fillRect(r);
      
       Rectangle<int> thumbnailBounds (10, 100, getWidth() - 20, getHeight() - 120);
      
         if (thumbnail.getNumChannels() == 0)
             paintIfNoFileLoaded (g, thumbnailBounds);
         else
             paintIfFileLoaded (g, thumbnailBounds);
  }
    
    void paintIfFileLoaded (Graphics& g, const Rectangle<int>& thumbnailBounds){
           g.setColour (Colours::white);
           g.fillRect (thumbnailBounds);
        
           g.setColour (Colours::lightblue);
        
           auto audioLength (thumbnail.getTotalLength());                                      // [12]
           thumbnail.drawChannels (g,
                                   thumbnailBounds,
                                   0.0,
                                   audioLength,
                                   1.0f);
        
           g.setColour (Colours::green);
        
           auto audioPosition (transportSource.getCurrentPosition());
           auto drawPosition ((audioPosition / audioLength) * thumbnailBounds.getWidth()
                              + thumbnailBounds.getX());                                        // [13]
           g.drawLine (drawPosition, thumbnailBounds.getY(), drawPosition,
                       thumbnailBounds.getBottom(), 1.0f);
    }
    
    void paintIfNoFileLoaded (Graphics& g, const Rectangle<int>& thumbnailBounds)
    {
        g.setColour (Colours::darkgrey);
        g.fillRect (thumbnailBounds);
        g.setColour (Colours::white);
        g.drawFittedText ("No File Loaded", thumbnailBounds, Justification::centred, 1.0f);
    }
    
    void openButtonClicked ()  {
         FileChooser chooser ("Select Wave file", {}, "*.wav");
        
        if (chooser.browseForFileToOpen())
           {
               auto file = chooser.getResult();
               auto* reader = formatManager.createReaderFor (file);
                std::unique_ptr<AudioFormatReaderSource> newSource (new AudioFormatReaderSource (reader, true));
               thumbnail.setSource (new FileInputSource (file));          // [7]
               readerSource.reset (newSource.release());
               
               std::unique_ptr<AudioFormatReader> reader2 (formatManager.createReaderFor (file)); // [2]
        
               if (reader2.get() != nullptr)
               {
                   noOfSamples = reader2->lengthInSamples;
                   auto duration = reader2->lengthInSamples / reader2->sampleRate;                 // [3]
        
                   if (duration < 2)
                   {
                       Model::of().fileBuffer.setSize (reader2->numChannels, (int) reader2->lengthInSamples);  // [4]
                       reader2->read (&Model::of().fileBuffer,                                                // [5]
                                     0,                                                          //  [5.1]
                                     (int) reader->lengthInSamples,                              //  [5.2]
                                     0,                                                          //  [5.3]
                                     true,                                                       //  [5.4]
                                     true);                                                      //  [5.5]                                                          // [6]                               // [7]
                   }
                   else
                   {
                       // handle the error that the file is 2 seconds or longer..
                   }
                    playButton.setEnabled (true);
               }
           }
        /*
       if (chooser.browseForFileToOpen()){
           auto file = chooser.getResult();
           auto* reader = formatManager.createReaderFor (file);
    
           if (reader != nullptr){
               std::unique_ptr<AudioFormatReaderSource> newSource (new AudioFormatReaderSource (reader, true));
              transportSource.setSource (newSource.get(), 0, nullptr, reader->sampleRate);
              playButton.setEnabled (true);
              thumbnail.setSource (new FileInputSource (file));          // [7]
              readerSource.reset (newSource.release());
           }
       }
         */
    }
    

private:
    TextButton openButton;
    TextButton playButton;
    TextButton stopButton;
    
    AudioFormatManager formatManager;
    std::unique_ptr<AudioFormatReaderSource> readerSource;
    AudioTransportSource transportSource;
    AudioThumbnailCache thumbnailCache;                  // [1]
    AudioThumbnail thumbnail;
    TransportState state;
    long long noOfSamples;
};
#endif /* WaveComponent_h */
