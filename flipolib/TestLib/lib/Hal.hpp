//
//  SimpleOsc.hpp
//  TestLib
//
//  Created by Mathias Dietrich on 02.03.21.
//

#ifndef SimpleOsc_hpp
#define SimpleOsc_hpp

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <chrono>

#include <AudioUnit/AudioUnit.h>


#include "Def.h"
#include "Renderer.h"

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;

static Renderer * renderer;

static float l[2048]; // or stack?
static float r[2048];
static long  ms_renderTime;

class Hal {

public:
    AudioUnit toneUnit;
    
    static OSStatus Render(void *inRefCon, AudioUnitRenderActionFlags *ioActionFlags, const AudioTimeStamp *inTimeStamp,
             UInt32 inBusNumber, UInt32 inNumberFrames, AudioBufferList *ioData) {
        auto t1 = high_resolution_clock::now();

         renderer->render(l, r, inNumberFrames);
         SInt16 *left = (SInt16 *)ioData->mBuffers[0].mData;
         SInt16 *right = (SInt16 *)ioData->mBuffers[1].mData;
         for(int i=0; i < inNumberFrames; ++i){
             left[i] = l[i] * 32767.0f * 0.125f;
             right[i] = r[i] * 32767.0f * 0.1256f;
        }
        auto t2 = high_resolution_clock::now();

        /* Getting number of milliseconds as an integer. */
        auto newTime = duration_cast<milliseconds>(t2 - t1).count();
        ms_renderTime = (ms_renderTime + newTime) / 2;
        
        float tAvailableMsec = 1000.0 * (float)inNumberFrames / (float)SAMPLE_RATE;
        if(ms_renderTime > tAvailableMsec){
            std::cout << "Timeout in Render" << std::endl;
        }
        return noErr;
    }
    
    void setup(){
        printf("Starting Audio setup\n");
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
        
        printf("Audio setup comlete\n");
        printf("======================================================\n");
    }
    
    void close(){
        AudioOutputUnitStop(toneUnit);
        AudioUnitUninitialize(toneUnit);
        AudioComponentInstanceDispose(toneUnit);
    }
};
#endif /* SimpleOsc_hpp */
