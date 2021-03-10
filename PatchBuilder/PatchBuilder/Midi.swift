//
//  Midi.swift
//  PatchBuilder
//
//  Created by Mathias Dietrich on 09.03.21.
//

import Foundation
import CoreMIDI
import CoreAudio
import AudioToolbox

class Midi {
    
    func notifyCallback(message:UnsafePointer<MIDINotification>,refCon:UnsafeMutablePointer<Void>)
    {
        print("MIDI Notify")
    }

    func eventCallback(pktlist:UnsafePointer<MIDIPacketList>, refCon:UnsafeMutablePointer<Void>, connRefCon:UnsafeMutablePointer<Void>)
    {
        print("MIDI Read")
    }
    
    // method to collect display names of available MIDI destinations
    func midiDestinationNames() -> [String] {
        var names:[String] = []

        let count:Int = MIDIGetNumberOfDestinations()

        for i in 0..<count {
            let endpoint:MIDIEndpointRef = MIDIGetDestination(i)
            if  endpoint != 0 {
                names.append(midiObjectDisplayName(endpoint))
            }
        }
        return names
    }

    // helper method to extract the display name from a MIDIObjectRef
    func midiObjectDisplayName(_ obj: MIDIObjectRef) -> String {

        var param: Unmanaged<CFString>?
        var capturedName = "Error"
        let err = MIDIObjectGetStringProperty(obj, kMIDIPropertyDisplayName, &param)
        if err == OSStatus(noErr) {
          capturedName = param!.takeRetainedValue() as String
        }
        return capturedName
    }

    
    func send(cc:Int, value: Int){
        var status = OSStatus(noErr)
        
        let destinationNames = midiDestinationNames()

        // check if we have any available MIDI destinations.
        if destinationNames.count > 0 {

            // establish a MIDI client and output port, and send a note on/off pair.
            var midiClient:MIDIClientRef = 0
            var outPort:MIDIPortRef = 0

            MIDIClientCreate("Swift3 Test Client" as CFString, nil, nil, &midiClient)
            MIDIOutputPortCreate(midiClient, "Swift3 Test OutPort" as CFString, &outPort)

            let destNum = 0
            let destName = destinationNames[destNum]
            var dest:MIDIEndpointRef = MIDIGetDestination(destNum)

            var midiPacket:MIDIPacket = MIDIPacket()
            midiPacket.timeStamp = 0
            midiPacket.length = 3
            midiPacket.data.0 = 0x90 + 0 // Note On event channel 1
            midiPacket.data.1 = 0x3D // Note Db
            midiPacket.data.2 = 100 // Velocity

            var packetList:MIDIPacketList = MIDIPacketList(numPackets: 1, packet: midiPacket)
            print("Sending note on to \(destName)")
            MIDISend(outPort, dest, &packetList)

            midiPacket.data.0 = 0x80 + 0 // Note off event channel 1
            midiPacket.data.2 = 0 // Velocity
            sleep(1)
            packetList = MIDIPacketList(numPackets: 1, packet: midiPacket)
            MIDISend(outPort, dest, &packetList)
            print("Note off sent to \(destName)")
        }
    }

    var midiClient = MIDIClientRef()
    
    var outputPort = MIDIPortRef()
    
    var inputPort = MIDIPortRef()
    
    var virtualSourceEndpointRef = MIDIEndpointRef()
    
    var virtualDestinationEndpointRef = MIDIEndpointRef()
    
    var midiInputPortref = MIDIPortRef()
    
    var musicPlayer:MusicPlayer?
      
      var musicSequence:MusicSequence?
      
      var processingGraph:AUGraph?
      
      var samplerUnit:AudioUnit?

}
