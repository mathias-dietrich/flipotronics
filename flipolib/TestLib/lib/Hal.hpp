//
//  SimpleOsc.hpp
//  TestLib
//
//  Created by Mathias Dietrich on 02.03.21.
//

#ifndef SimpleOsc_hpp
#define SimpleOsc_hpp

#include <stdio.h>
#include <AudioUnit/AudioUnit.h>
#include "Renderer.h"

#define SAMPLE_RATE 44100

static Renderer * renderer;

class Hal {
    
public:
    AudioUnit toneUnit;

     static OSStatus Render(
             void *inRefCon,
             AudioUnitRenderActionFlags *ioActionFlags,
             const AudioTimeStamp *inTimeStamp,
             UInt32 inBusNumber,
             UInt32 inNumberFrames,
             AudioBufferList *ioData) {
         renderer->render(ioData, inNumberFrames);
         return noErr;
     }
    void setup(){
        OSErr err;

        AudioComponentDescription acd = {
            .componentType = kAudioUnitType_Output,
            .componentSubType = kAudioUnitSubType_DefaultOutput,
            .componentManufacturer = kAudioUnitManufacturer_Apple,
        };

        AudioComponent output = AudioComponentFindNext(NULL, &acd);
        if (!output) printf("Can't find default output\n");

       
        err = AudioComponentInstanceNew(output, &toneUnit);
        if (err) fprintf(stderr, "Error creating unit: %d\n", err);

        AURenderCallbackStruct input = { .inputProc = Render };
        err = AudioUnitSetProperty(toneUnit, kAudioUnitProperty_SetRenderCallback,
                kAudioUnitScope_Input, 0, &input, sizeof(input));
        if (err) printf("Error setting callback: %d\n", err);

        AudioStreamBasicDescription asbd = {
            .mFormatID = kAudioFormatLinearPCM,
            .mFormatFlags = 0
                | kAudioFormatFlagIsSignedInteger
                | kAudioFormatFlagIsPacked
                | kAudioFormatFlagIsNonInterleaved,
            .mSampleRate = SAMPLE_RATE,
            .mBitsPerChannel = 16,
            .mChannelsPerFrame = 2,
            .mFramesPerPacket = 1,
            .mBytesPerFrame = 2,
            .mBytesPerPacket = 2,
        };

        err = AudioUnitSetProperty(toneUnit, kAudioUnitProperty_StreamFormat,
                kAudioUnitScope_Input, 0, &asbd, sizeof(asbd));
        if (err) printf("Error setting stream format: %d\n", err);

        err = AudioUnitInitialize(toneUnit);
        if (err) printf("Error initializing unit: %d\n", err);

        err = AudioOutputUnitStart(toneUnit);
        if (err) printf("Error starting unit: %d\n", err);
    }
    
    void close(){
        AudioOutputUnitStop(toneUnit);
        AudioUnitUninitialize(toneUnit);
        AudioComponentInstanceDispose(toneUnit);
    }
};
#endif /* SimpleOsc_hpp */
