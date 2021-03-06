//
//  Core.cpp
//  synth1
//
//  Created by Mathias Dietrich on 30.05.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#include "Core.h"

using namespace std;

void Core::init (double sampleRate, int samplesPerBlock){

    this->sampleRate = sampleRate;
    this->samplesPerBlock = samplesPerBlock;
    this->blocksPerSeccond = sampleRate / samplesPerBlock;
    
    // Tuning
    BankLoader::of().initTunfile();

    for (int i=0; i<128; ++i) {
       // Model::of().tuneTable[i] = MidiToFreq(i,440);
        Model::of().tuneTable[i] = BankLoader::of().tunReader.GetMIDINoteFreqHz(i);
    }
    for (int i=0; i<12; ++i) {
        Model::of().tuneMulti[i] = 1.0;
    }
    
    // Wave Table
    WaveTable::of()->init(sampleRate,samplesPerBlock );
    Model::of().patchCurrent = 1;

    for(int i =0; i < MAXPARAM;++i){
       p[i] = Model::of().par[i] ;
    }

    // Voices
    for (int i=0; i<MAXVOICE; ++i) {
        voices[i].vid = i;
        voices[i].init( sampleRate, samplesPerBlock, p);
        voices[i].active = false;
    }
    
    // FX
    delay.init( sampleRate, samplesPerBlock);
    
    // Detector
    detector.init( sampleRate, samplesPerBlock);
    detector.setAttack(20);
    detector.setRelease(200);
    
    timeAllowedMsec =  samplesPerBlock / sampleRate * 1000 ;
    
    // Build Modulation Matrix
    // MatrixSource , MatrixDest , paramMulti, paramAdd, MatrixTransform ,isEnabled=true
    matrix.addEntry(matrix.createEntry(s_LFO1, d_OSC1_FREQ, P_LFO1_PITCH, P_FIXTURN, t_BIPOLAR_TO_UNIPOLAR));
    matrix.addEntry(matrix.createEntry(s_LFO1, d_OSC1_VOL, P_LFO1_VOL, P_FIXTURN, t_BIPOLAR_TO_UNIPOLAR));
    matrix.addEntry(matrix.createEntry(s_LFO1, d_FILTER1_CUTOFF, P_LFO1_FILTER, P_FIXTURN, t_BIPOLAR_TO_UNIPOLAR));
}

void Core::handle(AudioBuffer<float>& buffer, MidiBuffer& midiMessages, int totalNumInputChannels, int totalNumOutputChannels) {
    ScopedNoDenormals noDenormals;
    
    auto begin = std::chrono::high_resolution_clock::now();
    
    // Copy PARAMS from the Heap
    float p[MAXPARAM * 4];
    for(int i =0; i < MAXPARAM * 4;++i){
        p[i] = Model::of().par[i] ;
    }

    // Handle Midi Messages
    MidiMessage result;
    int samplePosition;
    MidiBuffer::Iterator n(midiMessages);
    
    while(n.getNextEvent (result, samplePosition)){
        if(result.isNoteOn()){
            int note = result.getNoteNumber();
            float velocity = result.getVelocity() / 127.0f;
            int channel = result.getChannel();
            startVoice(channel,note, velocity, 0);
        }
        if(result.isNoteOff()){
            int note = result.getNoteNumber();
            int channel = result.getChannel();
            endVoice(channel,note);
        }
    }
    
    // Update Parameter
    if(updateCounter % UPDATEDEVIDER == 0){
        
        // handle Smoothing
        float c = sampleRate * 0.001f * UPDATEDEVIDER;
        for(int i =0; i < MAXPARAM;++i){
            if(Model::of().params[i].smoothTime > 0){
                if(abs(Model::of().par[i]) < abs(Model::of().par[i] + Model::of().parTargetDelta[i]) - 0.001){
                    float delta =  Model::of().parTargetDelta[i] /  (Model::of().params[i].smoothTime *c);
                    Model::of().par[i] = Model::of().par[i] + delta;
                }
            }
        }
        for(int i=0; i < MAXVOICE;++i){
            if(voices[i].active){
              voices[i].update(clock,p);
            }
        }
    }
    ++updateCounter;
    
    // Prepare audio uffer
    auto* channelDataL = buffer.getWritePointer (0);
    auto* channelDataR = buffer.getWritePointer (1);
    std::fill(channelDataL, channelDataL + samplesPerBlock, 0);
    std::fill(channelDataR, channelDataR + samplesPerBlock, 0);

    // Render Voices
    for(int i=0; i < MAXVOICE;++i){
       if(voices[i].active){
           voices[i].render(clock, buffer, p, matrix);
       }
     }

    // Sampler
    if(Model::of().noOfSamplesToPlay > 0){
        for (int i=0; i<samplesPerBlock; ++i) {
            
            auto* buf = Model::of().fileBuffer.getReadPointer (0);
            channelDataL[i] += buf[samplePlayerPos];
            channelDataR[i] += buf[samplePlayerPos];
            ++samplePlayerPos;
            
            if(samplePlayerPos >= Model::of().noOfSamplesToPlay){
                Model::of().noOfSamplesToPlay =0;
                samplePlayerPos = 0;
                Model::of().hasPlayed = true;
                break;
            }
        }
    }
    
    // Render FX
    delay.handle(buffer,  totalNumInputChannels,  totalNumOutputChannels, p);
    
    // Set Scope Buffer for the Ouput UI
    Msg *m = Model::of().getBack();
    for (int i=0; i<samplesPerBlock; ++i) {
       m->blockBuffer[i] =  (channelDataL[i] + channelDataR[i]) * 0.5f;
    }
    
    // Master Volume
    float linVolume = DecibelToLinear( Model::of().par[P_MASTERVOL]);
    for (int i=0; i<samplesPerBlock; ++i){
        channelDataL[i] *= linVolume;
        channelDataR[i] *= linVolume;
    }
    
    // Detector Peak and RMS Meter
    detector.handle(buffer, totalNumInputChannels, totalNumOutputChannels);

    // Move Clock
    clock += samplesPerBlock;
    Model::of().pushMsgToUi();
    
    // Measure time taken
    auto end = std::chrono::high_resolution_clock::now();
    int64 nanoSec = std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
    Model::of().timeTaken = (Model::of().timeTaken+nanoSec) * 0.5;
}
