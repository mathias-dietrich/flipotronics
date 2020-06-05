//
//  BankLoader.h
//  synth1
//
//  Created by Mathias Dietrich on 05.06.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef BankLoader_h
#define BankLoader_h

#include <stdio.h>
#include <JuceHeader.h>

#include "WaveTable.h"
#include "Const.h"
#include "Model.h"
// http://courses.cs.vt.edu/~cs2604/fall00/binio.html


class BankLoader {

    public:

        void save(){
            PatchData p;

            // copy the floats
            for(int i=0; i < MAXPARAM;i++){
                p.floatNumbers[i] = par[i];
            }
            p.floatCount = MAXPARAM;
            p.name = patchNameCurrent;
            
            bankData.patchData[patchCurrent] = p;
            save("default.flip", &bankData);
        }
    
        void save(BankData * data ){
            save("default.flip", data);
        }
        
        void save(String name, BankData * data){
            
            File f = File::getCurrentWorkingDirectory().getChildFile (name);
            int checksum = 0;
            f.replaceWithText ("FLIP\n",false,true,"\n"); // 0
            f.appendText("HEAD:\n",false,true,"\n"); // 1
            f.appendText(toString(checksum) + "\n",false,true,"\n"); // 2
            f.appendText(toString(data->lengthTotal)+ "\n",false,true,"\n"); // 3
            f.appendText(toString(data->synthId)+ "\n",false,true,"\n"); // 4
            f.appendText(toString(data->type)+ "\n",false,true,"\n"); // 5
            f.appendText(toString(data->version)+ "\n",false,true,"\n"); // 6
            f.appendText(toString(data->noOfPatches)+ "\n",false,true,"\n"); // 7
            f.appendText(data->name + "\n",false,true,"\n"); // 8
            f.appendText(data->author + "\n",false,true,"\n"); // 9
            f.appendText(data->www + "\n",false,true,"\n"); // 10
            f.appendText("BODY:\n",false,true,"\n"); // 11
            
            for(int i=0; i < data->noOfPatches;++i){
                PatchData p = data->patchData[i];
                f.appendText(toString(i) + "\n",false,true,"\n");
                f.appendText(p.name + "\n",false,true,"\n");
                f.appendText(toString(p.floatCount) + "\n",false,true,"\n");
                f.appendText(toString(p.doubleCount) + "\n",false,true,"\n");
                f.appendText(toString(p.intCount) + "\n",false,true,"\n");
                f.appendText(toString(p.stringCount) + "\n",false,true,"\n");
                f.appendText(toString(p.binCount) + "\n",false,true,"\n");
                
                for(int i=0; i < p.floatCount;++i){
                    f.appendText(toString(p.floatNumbers[i]) + "\n",false,true,"\n");
                }
                for(int i=0; i < p.doubleCount;++i){
                    f.appendText(toString(p.doubleNumbers[i]) + "\n",false,true,"\n");
                }
                for(int i=0; i < p.intCount;++i){
                    f.appendText(toString(p.intNumbers[i]) + "\n",false,true,"\n");
                }
                for(int i=0; i < p.stringCount;++i){
                    f.appendText(p.stringTable[i] + "\n",false,true,"\n");
                }
                for(int i=0; i < p.binCount;++i){

                }
                f.appendText("----\n",false,true,"\n");
            }
            f.appendText ("FLOP\n",false,true);
        
        }
        
        void load( ){
               load("default.flip");
        }
    
        void load(String name){
            File f = File::getCurrentWorkingDirectory().getChildFile (name);
            if (! f.existsAsFile()){
                std::cout << "Bank File does not exist" << std::endl;
                return;  // file doesn't exist
            }
            FileInputStream stream (f);
            if (stream.openedOk())
            {
                int lineId =0;
                
                int patchId = 0;
                while (! stream.isExhausted()) {
                    auto line = stream.readNextLine().trim();
                    std::cout << line << std::endl;
                    switch(lineId){
                        case 0:
                            if(line!="FLIP"){
                                std::cout << "This is not a Flipotronics File" << std::endl;
                                return;
                            }
                        case 1:
                             ++lineId;
                            continue;
                        case 2:
                              ++lineId;
                             continue;
                        case 3:
                              ++lineId;
                             continue;
                        case 4:
                              ++lineId;
                             continue;
                        case 5:
                              ++lineId;
                             continue;
                        case 6:
                              ++lineId;
                             continue;
                        case 7:
                            bankData.noOfPatches = intFromString(line);
                            ++lineId;
                            continue;
                            
                        case 8:
                          ++lineId;
                         continue;
                            
                        case 9:
                          ++lineId;
                         continue;
                        
                        case 10:
                          ++lineId;
                         continue;
                        
                        case 11:
                          ++lineId;
                         continue;
                    }
                   
                    PatchData pd = bankData.patchData[patchId];
                    int patchLineId = 0;
                    bool parsePatchHeader = true;
                    while(! stream.isExhausted() && parsePatchHeader){
                        auto line = stream.readNextLine().trim();
                        switch(patchLineId){
                            case 0:
                                pd.name = line;
                                ++patchLineId;
                                continue;
                            case 1:
                                pd.floatCount = intFromString(line);
                                ++patchLineId;
                                continue;
                            case 2:
                                 pd.doubleCount = intFromString(line);
                                ++patchLineId;
                                continue;
                            case 3:
                                 pd.intCount = intFromString(line);
                                ++patchLineId;
                                continue;
                            case 4:
                                 pd.stringCount = intFromString(line);
                                ++patchLineId;
                                continue;
                            case 5:
                                 pd.binCount = intFromString(line);
                                ++patchLineId;
                                parsePatchHeader = false;
                                break;
                        }
                    }

                    for(int i=0; i < pd.floatCount;++i){
                        auto line = stream.readNextLine().trim();
                        pd.floatNumbers[i] = line.getFloatValue();
                    }
                    for(int i=0; i < pd.doubleCount;++i){
                        auto line = stream.readNextLine().trim();
                        pd.doubleNumbers[i] = line.getDoubleValue();
                    }
                    for(int i=0; i < pd.intCount;++i){
                        auto line = stream.readNextLine().trim();
                        pd.intNumbers[i] = line.getIntValue();
                    }
                    for(int i=0; i < pd.stringCount;++i){
                        auto line = stream.readNextLine().trim();
                        pd.stringTable[i] = line;
                    }
                    for(int i=0; i < pd.binCount;++i){
                        auto line = stream.readNextLine().trim();
                    }
                    bankData.patchData[patchId] = pd;
                    ++patchId;
                    auto markerPatchEnd = stream.readNextLine().trim();
                    std::cout << markerPatchEnd << std::endl;
                }
            }
        }
    private:
};

#endif /* BankLoader_h */
