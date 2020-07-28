//
//  Core.h
//  Deus
//
//  Created by Mathias Dietrich on 7/28/20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef Core_h
#define Core_h

#include "Preset.h"

class Core{
public:
    void processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages, int totalNumInputChannels, int totalNumOutputChannels){
        
            ScopedNoDenormals noDenormals;
        
            // In case we have more outputs than inputs, this code clears any output
            // channels that didn't contain input data, (because these aren't
            // guaranteed to be empty - they may contain garbage).
            // This is here to avoid people getting screaming feedback
            // when they first compile a plugin, but obviously you don't need to keep
            // this code if your algorithm always overwrites all the output channels.
            for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
                buffer.clear (i, 0, buffer.getNumSamples());
        
            // This is the place where you'd normally do the guts of your plugin's
            // audio processing...
            // Make sure to reset the state if your inner loop is processing
            // the samples and the outer loop is handling the channels.
            // Alternatively, you can process the samples with the channels
            // interleaved by keeping the same state.
            for (int channel = 0; channel < totalNumInputChannels; ++channel)
            {
               // auto* channelData = buffer.getWritePointer (channel);
        
                // ..do something to the data...
            }
    }
    
    void configure(Preset preset){
        
    }
};
#endif /* Core_h */
