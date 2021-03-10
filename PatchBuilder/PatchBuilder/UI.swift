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
    }
    
    // buttons
    required init?(coder: NSCoder) {
        super.init(coder:coder)
    }
    
    override func draw(_ dirtyRect: NSRect) {
        super.draw(dirtyRect)

        // Drawing code here.
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
        osc.send(prefix:tbxOscPrefix.stringValue, cc: Int(tbxCcControl.intValue), value: Int(tbxCcValue.intValue))
        midi.send(cc: Int(tbxCcControl.intValue), value: Int(tbxCcValue.intValue))
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
        osc.setup(host: tbxOscTargetHost.stringValue, port:Int(tbxOscTargetPort.intValue))
        print("btnSetup")
    }
    
}
