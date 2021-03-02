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

#define SAMPLE_RATE 48000
#define TONE_FREQUENCY 440
#define M_TAU 2.0 * M_PI

class SimpleOsc {
    
public:
    AudioUnit toneUnit;
    
    static OSStatus Render(
            void *inRefCon,
            AudioUnitRenderActionFlags *ioActionFlags,
            const AudioTimeStamp *inTimeStamp,
            UInt32 inBusNumber,
            UInt32 inNumberFrames,
            AudioBufferList *ioData) {
        
        static float theta;

        SInt16 *left = (SInt16 *)ioData->mBuffers[0].mData;
        for (UInt32 frame = 0; frame < inNumberFrames; ++frame) {
            left[frame] = (SInt16)(sin(theta) * 32767.0f);
            theta += M_TAU * TONE_FREQUENCY / SAMPLE_RATE;
            if (theta > M_TAU) {
                theta -= M_TAU;
            }
        }

        // Copy left channel to right channel
        memcpy(ioData->mBuffers[1].mData, left, ioData->mBuffers[1].mDataByteSize);

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
            .mSampleRate = 48000,
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
