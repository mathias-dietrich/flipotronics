//
//  Midi.swift
//  PatchBuilder
//
//  Created by Mathias Dietrich on 09.03.21.
//

import Foundation

class Midi {
    func send( cc: Int,  value : Int){
        print ("midi send " + String(cc) + " " + String(value))
    }
}
