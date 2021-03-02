//
//  main.cpp
//  TestLib
//
//  Created by Mathias Dietrich on 02.03.21.

// Use >MidiKeys to Test on MAC  https://flit.github.io/projects/midikeys/
// Use CoreMidi and CoreFoundation Framework
//

#include <iostream>
#include <cstdlib>
#include <CoreMIDI/MIDIServices.h>
#include <CoreFoundation/CFRunLoop.h>
#include <stdio.h>


#include "VoiceMaster.hpp"


VoiceMaster voiceMaster;

MIDIPortRef     gOutPort = NULL;
MIDIEndpointRef gDest = NULL;
int             gChannel = 0;


static int parse(Byte b){
    
    int value = b;

    return value;
}

static void MyReadProc(const MIDIPacketList *pktlist, void *refCon, void *connRefCon)
{
    if (gOutPort != NULL && gDest != NULL) {
        MIDIPacket *packet = (MIDIPacket *)pktlist->packet; // remove const (!)
        for (unsigned int j = 0; j < pktlist->numPackets; ++j) {
            for (int i = 0; i < packet->length; ++i) {
               // printf("%02X ", packet->data[i]);
                
                int d0 = parse(packet->data[i]);
                int d1 = parse(packet->data[i+1]);
                int d2 = parse(packet->data[i+2]);
                      
               /*
                printf( "length %i \n", packet->length);
                printf( "1 Status %i \n", d0);
                printf( "2 Status %i \n", d1);
                printf( "3 Status %i \n", d2);
                */
                i+=3;
        
                if(d0 > 143){
                    int channel = d0 - 143;
                    int note = d1;
                    int velocity = d2;
                    
                    if(channel>64){
                        // Aftertouch ?
                        //voiceMaster.aftertouch( channel - 64,  d1);
                    }else{
                        voiceMaster.noteOn( channel,  note,  velocity);
                    }
                }
                if(d0 < 144){
                    int channel = d0 - 127;
                    int note = d1;
                    int velocity = d2;
                    voiceMaster.noteOff( channel,  note,  velocity);
                }
        
                
                // rechannelize status bytes
               // if (packet->data[i] >= 0x80 && packet->data[i] < 0xF0)
                   // packet->data[i] = (packet->data[i] & 0xF0) | gChannel;
            }

          //printf("\n");
            //packet = MIDIPacketNext(packet);
        }

        //MIDISend(gOutPort, gDest, pktlist);
    }
}


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Starting Tests\n";
    
    
    // create client and ports
       MIDIClientRef client = NULL;
       MIDIClientCreate(CFSTR("MIDI Echo"), NULL, NULL, &client);

       MIDIPortRef inPort = NULL;
       MIDIInputPortCreate(client, CFSTR("Input port"), MyReadProc, NULL, &inPort);
       MIDIOutputPortCreate(client, CFSTR("Output port"), &gOutPort);

       // enumerate devices (not really related to purpose of the echo program
       // but shows how to get information about devices)
       int i, n;
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
       printf("%d sources\n", n);
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
           printf("Echoing to channel %d of %s\n", gChannel + 1, name);
       } else {
           printf("No MIDI destinations present\n");
       }

       CFRunLoopRun();
       // run until aborted with control-C

       return 0;


}
    
