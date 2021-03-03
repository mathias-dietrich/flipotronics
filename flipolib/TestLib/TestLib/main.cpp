//
//  main.cpp
//  TestLib
//
//  Created by Mathias Dietrich on 02.03.21.

// Use >MidiKeys to Test on MAC  https://flit.github.io/projects/midikeys/
// Use CoreMidi and CoreFoundation Framework
//
#include <stdio.h>
#include <iostream>
#include <cstdlib>

#include <CoreMIDI/MIDIServices.h>
#include <CoreFoundation/CFRunLoop.h>

#include <arpa/inet.h>
#include <sys/select.h>
#include <fcntl.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <thread>

#include "VoiceMaster.hpp"
#include "TinyOsc.h"

VoiceMaster * voiceMaster;
MIDIPortRef     gOutPort = NULL;
MIDIEndpointRef gDest = NULL;
int             gChannel = 0;

static volatile bool keepRunning = true;

// handle Ctrl+C
static void sigintHandler(int x) {
  keepRunning = false;
}

static int parse(Byte b){
    int value = b;
    return value;
}

static void MyReadProc(const MIDIPacketList *pktlist, void *refCon, void *connRefCon) {
    if (gOutPort != NULL && gDest != NULL) {
        MIDIPacket *packet = (MIDIPacket *)pktlist->packet; // remove const (!)
        for (unsigned int j = 0; j < pktlist->numPackets; ++j) {
            for (int i = 0; i < packet->length; ++i) {
                int d0 = parse(packet->data[i]);
                int d1 = parse(packet->data[i+1]);
                int d2 = parse(packet->data[i+2]);
                i+=3;
                if(d0 > 143){
                    int channel = d0 - 143;
                    int note = d1;
                    int velocity = d2;
                    
                    if(channel>64){
                        // Aftertouch ?
                        //voiceMaster.aftertouch( channel - 64,  d1);
                    }else{
                        voiceMaster->noteOn( channel,  note,  velocity);
                    }
                }
                if(d0 < 144){
                    int channel = d0 - 127;
                    int note = d1;
                    int velocity = d2;
                    voiceMaster->noteOff( channel,  note,  velocity);
                }
            }
          //printf("\n");
            //packet = MIDIPacketNext(packet);
        }
        //MIDISend(gOutPort, gDest, pktlist);
    }
}

void createMidiDevices(){
    printf("Starting Midi setup\n");
    MIDIClientRef client = NULL;
    MIDIClientCreate(CFSTR("MIDI Echo"), NULL, NULL, &client);

    MIDIPortRef inPort = NULL;
    MIDIInputPortCreate(client, CFSTR("Input port"), MyReadProc, NULL, &inPort);
    MIDIOutputPortCreate(client, CFSTR("Output port"), &gOutPort);

    // enumerate devices (not really related to purpose of the echo program
    // but shows how to get information about devices)
    unsigned long i, n;
    CFStringRef pname, pmanuf, pmodel;
    char name[64], manuf[64], model[64];

    n = MIDIGetNumberOfDevices();
    for (i = 0; i < n; ++i) {
       MIDIDeviceRef dev = MIDIGetDevice(i);

       MIDIObjectGetStringProperty(dev, kMIDIPropertyName, &pname);
       MIDIObjectGetStringProperty(dev, kMIDIPropertyManufacturer, &pmanuf);
       MIDIObjectGetStringProperty(dev, kMIDIPropertyModel, &pmodel);

       CFStringGetCString(pname, name, sizeof(name), 0);
       CFStringGetCString(pmanuf, manuf, sizeof(manuf), 0);
       CFStringGetCString(pmodel, model, sizeof(model), 0);
       CFRelease(pname);
       CFRelease(pmanuf);
       CFRelease(pmodel);

       printf("name=%s, manuf=%s, model=%s\n", name, manuf, model);
    }

    // open connections from all sources
    n = MIDIGetNumberOfSources();
    printf("%d Midi sources found\n", n);
    for (i = 0; i < n; ++i) {
       MIDIEndpointRef src = MIDIGetSource(i);
       MIDIPortConnectSource(inPort, src, NULL);
    }

    // find the first destination
    n = MIDIGetNumberOfDestinations();
    if (n > 0)
       gDest = MIDIGetDestination(0);

    if (gDest != NULL) {
       MIDIObjectGetStringProperty(gDest, kMIDIPropertyName, &pname);
       CFStringGetCString(pname, name, sizeof(name), 0);
       CFRelease(pname);
    printf("Found MIDI destinations\n");
    } else {
       printf("No MIDI destinations present\n");
    }
    
    printf("MIDI setup comlete\n");
    printf("===========================\n");
}

void startOsc(){
    printf("Starting OSC setup\n");
    char buffer[2048]; // declare a 2Kb buffer to read packet data into
    const int fd = socket(AF_INET, SOCK_DGRAM, 0);
    fcntl(fd, F_SETFL, O_NONBLOCK); // set the socket to non-blocking
    struct sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(9000);
    sin.sin_addr.s_addr = INADDR_ANY;
    bind(fd, (struct sockaddr *) &sin, sizeof(struct sockaddr_in));
    printf("listening on port 9000 UDP\n");
    printf("OSC setup comlete\n");
    printf("===========================\n");
    while(keepRunning){
        fd_set readSet;
           FD_ZERO(&readSet);
           FD_SET(fd, &readSet);
           struct timeval timeout = {1, 0}; // select times out after 1 second
           if (select(fd+1, &readSet, NULL, NULL, &timeout) > 0) {
             struct sockaddr sa; // can be safely cast to sockaddr_in
             socklen_t sa_len = sizeof(struct sockaddr_in);
             int len = 0;
             while ((len = (int) recvfrom(fd, buffer, sizeof(buffer), 0, &sa, &sa_len)) > 0) {
               if (tosc_isBundle(buffer)) {
                 tosc_bundle bundle;
                 tosc_parseBundle(&bundle, buffer, len);
                 const uint64_t timetag = tosc_getTimetag(&bundle);
                 tosc_message osc;
                 while (tosc_getNextMessage(&bundle, &osc)) {
                   tosc_printMessage(&osc);
                 }
               } else {
                 tosc_message osc;
                 tosc_parseMessage(&osc, buffer, len);
                 tosc_printMessage(&osc);
               }
             }
        }
    }
    // close the UDP socket
    close(fd);
}

int main(int argc, const char * argv[]) {
    std::cout << "Starting Flipotronics Synth " << VERSION << " - " << BUILDDATE << "\n";
    printf("======================================================\n");
    
    voiceMaster = new VoiceMaster(8, 1);
    voiceMaster->configure(0, 1, 8);

    // setup Midi
    createMidiDevices();
    
    // Start OSC
    thread t1(startOsc);
    sleep(1);
    
    // Menu
    string help = "t:RenderTime - x:Exit - i:Info - h:Help \n";
    cout << help;
    string str;
    while(keepRunning){
        getline(cin, str);
        if(str == "x"){
            keepRunning = false;
        }
        if(str == "t"){
            voiceMaster->printTime();
        }
        if(str == "h"){
            cout << help;
        }
        if(str == "i"){
            cout << "SampleRate: " << SAMPLE_RATE << " MaxVoices: " << MAXVOICES  << " MaxZones: " << MAXZONES << endl;
        }
    }
    
    // clean up
    voiceMaster->close();
    
    // Wait for OSC Thread to exit
    t1.join();
    
    return 0;
}
