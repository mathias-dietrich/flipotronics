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
    
    var destinationNames : [String]!
    // establish a MIDI client and output port, and send a note on/off pair.
    var midiClient:MIDIClientRef = 0
    var outPort:MIDIPortRef = 0
    var inPort:MIDIPortRef = 0
    var dest:MIDIEndpointRef = 0
    var destName = ""
    
    var midiClientListen = MIDIClientRef()
    
    func notifyCallback(message:UnsafePointer<MIDINotification>,refCon:UnsafeMutablePointer<Void>)
    {
        print("MIDI Notify")
    }

    func eventCallback(pktlist:UnsafePointer<MIDIPacketList>, refCon:UnsafeMutablePointer<Void>, connRefCon:UnsafeMutablePointer<Void>)
    {
        print("MIDI Read")
    }
    
    func myNotifyCallback(message:UnsafePointer<MIDINotification>) -> Void {
            print("callback")
    }
    
    func MyMIDIReadProc (_ pktList: UnsafePointer<MIDIPacketList>,
                            readProcRefCon: UnsafeMutableRawPointer?,
                            srcConnRefCon: UnsafeMutableRawPointer?) -> Void{
            let packetList:MIDIPacketList = pktList.pointee
            let srcRef:MIDIEndpointRef = srcConnRefCon!.load(as: MIDIEndpointRef.self)
            var packet:MIDIPacket = packetList.packet
            for _ in 1...packetList.numPackets
            {
                let bytes = Mirror(reflecting: packet.data).children
                var dumpStr = ""
                var i = packet.length
                for (_, attr) in bytes.enumerated()
                {
                    dumpStr += String(format:"$%02X ", attr.value as! UInt8)
                    i -= 1
                    if (i <= 0){
                        break
                    }
                }
                print(dumpStr)
                packet = MIDIPacketNext(&packet).pointee

            }
        }

    
    func setup(){
        destinationNames = midiDestinationNames()
        
        MIDIClientCreate("Swift3 Test Client" as CFString, nil, nil, &midiClient)
        MIDIClientCreate("patchbuilder" as CFString, nil, nil, &midiClientListen)
        MIDIOutputPortCreate(midiClient, "Swift3 Test OutPort" as CFString, &outPort)
       // MIDIInputPortCreate(midiClientListen, "patchbuilder" as CFString, MyMIDIReadProc, nil, &inPort)
        
        MIDIInputPortCreateWithBlock(midiClient, "PatchBuilder" as CFString, &inPort, {
                (unsafePacketList: UnsafePointer<MIDIPacketList>, pointer: UnsafeMutableRawPointer?) in
                let packetList = unsafePacketList.pointee
                if packetList.numPackets == 1 {
                    //print("Midi in ")
                    let packet = packetList.packet
                    if(packet.data.0 == 176){
                        var cc = packet.data.1
                        var val = packet.data.2
                        print("CC" + String(cc) + " Val: " + String(val) + "")
                    }
                    if packet.length == 3 && packet.data.0 == 144 {
                        /* Note-On */
                        let note = packet.data.1
                        let velocity = packet.data.2
                        if velocity > 0 {
                            DispatchQueue.main.async(execute: {
                                // use note
                            })
                        }
                    }
                }
            })
        
        let sourceCount = MIDIGetNumberOfSources()
        var count = 0
        while count < sourceCount{
            let src:MIDIEndpointRef = MIDIGetSource(count)
            MIDIPortConnectSource(inPort, src, nil)
            count += 1
        }
        /*
       // let clientName = "com.flipotronics.patch" as CFString
        let clientName = destinationNames[0] as CFString
        _ = MIDIClientCreateWithBlock(clientName, &midiClientListen) { (notificationPtr: UnsafePointer<MIDINotification>) in
            let notification = notificationPtr.pointee
            switch notification.messageID {
                case .msgSetupChanged: // Can ignore, really
                    break

                case .msgObjectAdded:
                    let rawPtr = UnsafeRawPointer(notificationPtr)
                    let message = rawPtr.assumingMemoryBound(to: MIDIObjectAddRemoveNotification.self).pointee
                    print("MIDI \(message.childType) added: \(message.child)")

                case .msgObjectRemoved:
                    let rawPtr = UnsafeRawPointer(notificationPtr)
                    let message = rawPtr.assumingMemoryBound(to: MIDIObjectAddRemoveNotification.self).pointee
                    print("MIDI \(message.childType) removed: \(message.child)")

                case .msgPropertyChanged:
                    let rawPtr = UnsafeRawPointer(notificationPtr)
                    let message = rawPtr.assumingMemoryBound(to: MIDIObjectPropertyChangeNotification.self).pointee
                    print("MIDI \(message.object) property \(message.propertyName.takeUnretainedValue()) changed.")

                case .msgThruConnectionsChanged:
                    fallthrough
                case .msgSerialPortOwnerChanged:
                    print("MIDI Thru connection was created or destroyed")

                case .msgIOError:
                    let rawPtr = UnsafeRawPointer(notificationPtr)
                    let message = rawPtr.assumingMemoryBound(to: MIDIIOErrorNotification.self).pointee
                    print("MIDI I/O error \(message.errorCode) occurred")

                default:
                    break
            }
        }
 */

        let destNum = 2
        destName = destinationNames[destNum]
        dest = MIDIGetDestination(destNum)
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
        let destinationNames = midiDestinationNames()

        // check if we have any available MIDI destinations.
        if destinationNames.count > 0 {

            var midiPacket:MIDIPacket = MIDIPacket()
            midiPacket.timeStamp = 0
            midiPacket.length = 3
            midiPacket.data.0 = 176 // Note On event channel 1
            midiPacket.data.1 = UInt8(cc)
            midiPacket.data.2 = UInt8(value)

            var packetList:MIDIPacketList = MIDIPacketList(numPackets: 1, packet: midiPacket)
            print("Sending midi on to \(destName)")
            MIDISend(outPort, dest, &packetList)

            /*
            midiPacket.data.0 = 0x80 + 0 // Note off event channel 1
            midiPacket.data.2 = 0 // Velocity
            sleep(1)
            packetList = MIDIPacketList(numPackets: 1, packet: midiPacket)
            MIDISend(outPort, dest, &packetList)
             */
        }
    }
}
