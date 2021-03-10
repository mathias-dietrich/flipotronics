//
//  UI.swift
//  PatchBuilder
//
//  Created by Mathias Dietrich on 09.03.21.
//

import Cocoa

class UI: NSView {

    let  midi =  Midi()
    let osc =  OSC()
    
    // fields
    @IBOutlet var tbxOscPrefix: NSTextField!
    @IBOutlet var tbxOscTargetHost: NSTextField!
    @IBOutlet var tbxOscTargetPort: NSTextField!
    @IBOutlet var tbxPatchName: NSTextField!
    @IBOutlet var tbxPatchFolder: NSTextField!
    @IBOutlet var tbxCcControl: NSTextField!
    @IBOutlet var tbxCcValue: NSTextField!
    @IBOutlet var tbxComment: NSTextField!
    @IBOutlet var slider: NSSlider!
    
    @IBOutlet var cbxSendMidi: NSButton!
    @IBOutlet var cbxSendFader: NSButton!
    @IBOutlet var cbxSendOsc: NSButton!
    
    @IBAction func slider(sender: AnyObject) {
        tbxCcValue.intValue = slider.intValue;
        if (cbxSendFader.intValue == 1){
            send()
        }
       
    }
    
    // buttons
    required init?(coder: NSCoder) {
        super.init(coder:coder)
        midi.setup()
    }
    
    override func draw(_ dirtyRect: NSRect) {
        super.draw(dirtyRect)

        // Drawing code here.
    }
    
    func send(){
        osc.send(prefix:tbxOscPrefix.stringValue, cc: Int(tbxCcControl.intValue), value: Int(tbxCcValue.intValue))
        midi.send(cc: Int(tbxCcControl.intValue), value: Int(tbxCcValue.intValue))
    }
    
    @IBAction func btnLoad(sender: NSButton) {
        print("btnLoad")
    }
    
    @IBAction func btnSave(sender: NSButton) {
        print("btnSave")
    }
    
    @IBAction func btnAdd(sender: NSButton) {
        print("btnAdd")
    }
    
    @IBAction func btnSend(sender: NSButton) {
        send()
    }
    
    @IBAction func btnSendAll(sender: NSButton) {
        print("btnSendAll")
    }
    
    @IBAction func btnDelete(sender: NSButton) {
        print("btnDelete")
    }
    
    @IBAction func btnNew(sender: NSButton) {
        print("btnNew")
    }
    
    @IBAction func btnSetup(sender: NSButton) {
        DispatchQueue.global(qos: .background).async {
            print("This is run on the background queue")

            self.osc.setup(host: self.tbxOscTargetHost.stringValue, port:Int(self.tbxOscTargetPort.intValue))
        }
    
       
        print("btnSetup")
    }
    
}
