//
//  UI.swift
//  PatchBuilder
//
//  Created by Mathias Dietrich on 09.03.21.
//
// https://www.raywenderlich.com/830-macos-nstableview-tutorial

import Cocoa

class UI: NSView, NSTableViewDelegate, NSTableViewDataSource {

    let  midi =  Midi()
    let osc =  OSC()
    
    // fields
    @IBOutlet var tbxOscPrefix: NSTextField!
    @IBOutlet var tbxOscTargetHost: NSTextField!
    @IBOutlet var tbxOscTargetPort: NSTextField!
    
    @IBOutlet var tbxPatchName: NSTextField!
    @IBOutlet var tbxAuthor: NSTextField!
    @IBOutlet var tbxTags: NSTextField!
    @IBOutlet var tbxPatchFolder: NSTextField!
    @IBOutlet var tbxFileName: NSTextField!
    
    @IBOutlet var tbxCcControl: NSTextField!
    @IBOutlet var tbxCcValue: NSTextField!
    @IBOutlet var tbxComment: NSTextField!
    @IBOutlet var slider: NSSlider!
    
    @IBOutlet var cbxSendMidi: NSButton!
    @IBOutlet var cbxSendFader: NSButton!
    @IBOutlet var cbxSendOsc: NSButton!
    
    @IBOutlet var table: NSTableView!
    
    struct controlline {
        var cc: Int?
        var value: Int?
        var comment: String?
    }

    var data :[controlline] = []

    
    func numberOfRows(in tableView: NSTableView) -> Int {
            return data.count
   }
    
    func tableView(_ tableView: NSTableView, viewFor tableColumn: NSTableColumn?, row: Int) -> NSView? {
        return nil
    }
    
    func tableView(tableView: NSTableView, viewFor tableColumn: NSTableColumn?, row: Int) -> NSView? {
        let line = data[row]
     
        if tableColumn?.identifier == NSUserInterfaceItemIdentifier(rawValue: "cc") {
            let cellIdentifier = NSUserInterfaceItemIdentifier(rawValue: "cc")
                guard let cellView = tableView.makeView(withIdentifier: cellIdentifier, owner: self) as? NSTableCellView else { return nil }
                cellView.textField?.integerValue = line.cc ?? 0
                return cellView
        } else if tableColumn?.identifier == NSUserInterfaceItemIdentifier(rawValue: "value") {
            let cellIdentifier = NSUserInterfaceItemIdentifier(rawValue: "value")
                guard let cellView = tableView.makeView(withIdentifier: cellIdentifier, owner: self) as? NSTableCellView else { return nil }
                cellView.textField?.integerValue = line.value ?? 0
                return cellView
        } else {
            let cellIdentifier = NSUserInterfaceItemIdentifier(rawValue: "comment")
                guard let cellView = tableView.makeView(withIdentifier: cellIdentifier, owner: self) as? NSTableCellView else { return nil }
                cellView.textField?.stringValue = line.comment ?? ""
                return cellView
        }
    }
    
    
    @IBAction func slider(sender: AnyObject) {
        tbxCcValue.intValue = slider.intValue;
        if (cbxSendFader.intValue == 1){
            send()
        }
    }
    
    func numberOfRowsInTableView(tableView: NSTableView) -> Int {
        return data.count
    }

    // buttons
    required init?(coder: NSCoder) {
        super.init(coder:coder)
        midi.setup()
    }
    
    override func draw(_ dirtyRect: NSRect) {
        super.draw(dirtyRect)
    }
    
    func send(){
        osc.send(prefix:tbxOscPrefix.stringValue, cc: Int(tbxCcControl.intValue), value: Int(tbxCcValue.intValue))
        midi.send(cc: Int(tbxCcControl.intValue), value: Int(tbxCcValue.intValue))
    }
    
    func send(cc:Int, value:Int){
        osc.send(prefix:tbxOscPrefix.stringValue, cc: cc, value: value)
        midi.send(cc: cc, value: value)
    }
    
    @IBAction func btnLoad(sender: NSButton) {
        table.delegate = self
        table.dataSource = self
        
        print("btnLoad")
        let dialog = NSOpenPanel();
        dialog.directoryURL = URL(string: tbxPatchFolder.stringValue);
        dialog.title                   = "Choose Patch file";
        dialog.showsResizeIndicator    = true;
        dialog.showsHiddenFiles        = false;
        dialog.allowsMultipleSelection = false;
        dialog.canChooseDirectories = false;
        dialog.allowedFileTypes        = ["txt", "fly"];
        if (dialog.runModal() ==  NSApplication.ModalResponse.OK) {
            let result = dialog.url // Pathname of the file

            if (result != nil) {
                let path: String = result!.path
                do {
                    let content = try String(contentsOfFile:path, encoding: String.Encoding.utf8)
                    let lines = content.split(separator:"\n")
                    tbxFileName.stringValue = path
                    tbxPatchName.stringValue = String(lines[0])
                    tbxAuthor.stringValue = String(lines[1])
                    tbxTags.stringValue = String(lines[2])
                    var i = 3;
                    data.removeAll()
                    while(i < lines.count){
                        let l = String(lines[i])
                        let p = l.split(separator:":")
                        var line :controlline = controlline()
                        line.cc = Int(p[0]) as Int?
                        line.value = Int(p[1]) as Int?
                        line.comment = String(p[2]) as String?
                        data.append(line)
                        i += 1
                    }
                    table.reloadData()
                   }
                catch _ as NSError {
           
                   }
            }
        } else {
            // User clicked on "Cancel"
            return
        }
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
        for line in data {
            send(cc:line.cc!, value:line.value!)
        }
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
