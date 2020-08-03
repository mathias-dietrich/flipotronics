//
//  FileManager.h
//  Deus
//
//  Created by Mathias Dietrich on 8/2/20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef FileManager_h
#define FileManager_h

#include <stdio.h>
#include <JuceHeader.h>

class FileManager {       // The class

public:
    const String path = "patch_0.flip";
    
    void load(){
        File rp = File::getCurrentWorkingDirectory().getChildFile (path);
        auto fileText = rp.loadFileAsString();
        
        StringArray tokens;
        tokens.addTokens (fileText, "\n", "\"");
        for (int i=0; i<tokens.size(); i++){
            switch(i){
                case 0:
                
                   std::cout << tokens[i] <<std::endl;
                break;
                case 1:
                    Model::of()->preset.name = tokens[i];
                    std::cout << tokens[i] <<std::endl;
                break;
                case 2:
                     Model::of()->preset.author = tokens[i];
                    std::cout << tokens[i] <<std::endl;
                break;
                case 3:
                    Model::of()->preset.desc = tokens[i];
                    std::cout << tokens[i] <<std::endl;
                break;
                case 4:
                   Model::of()->preset.tags = tokens[i];
                   std::cout << tokens[i] <<std::endl;
               break;
                case 5:
                  Model::of()->preset.tuning = tokens[i].getFloatValue();
                  std::cout << tokens[i] <<std::endl;
              break;
                    
                default:
                    StringArray sub;
                    sub.addTokens (tokens[i], ",", "\"");
                    E_Module module;
                    int pid;
                    
                    for (int y=0; y<sub.size(); y++){
                        std::cout << sub[y] << std::endl; // holds next token
                        switch(y){
                            case 0:
                            {
                                if(sub[y].getIntValue() == 21){
                                   std::cout << "";
                                }
                                std::cout << sub[y] << std::endl;
                                String s = sub[y];
                                std::cout << s << std::endl;
                                int t = intFromString(s);
                                module = (E_Module) t;
                            }
                                break;
                                
                            case 1:
                                pid = intFromString(sub[y]);
                                break;
                                
                            case 2:
                                float v = sub[y].getFloatValue();
                                Model::of()->preset.params[module][pid].valF = v;
                                break;
                        }
                    }
            }
        }
        std::cout << "loaded Preset from  " << rp.getFullPathName() << std::endl;
    }
    
    void save(){
        Model::of()->preset.params[mGlobal][gMasterVolume].pid = 0;
        Model::of()->preset.params[mGlobal][gMasterVolume].minVal = -96;
        Model::of()->preset.params[mGlobal][gMasterVolume].maxVal = 6;
        Model::of()->preset.params[mGlobal][gMasterVolume].type = uDb;
        Model::of()->preset.params[mGlobal][gMasterVolume].stepVal = 0.01f;
        Model::of()->preset.params[mGlobal][gMasterVolume].module = mGlobal;
        
        Model::of()->preset.params[mGlobal][gNoOfVoices].pid = 1;
        Model::of()->preset.params[mGlobal][gNoOfVoices].minVal = 1;
        Model::of()->preset.params[mGlobal][gNoOfVoices].maxVal = 32;
        Model::of()->preset.params[mGlobal][gNoOfVoices].stepVal = 1.0f;
        Model::of()->preset.params[mGlobal][gNoOfVoices].module = mGlobal;
        
        File rp = File::getCurrentWorkingDirectory().getChildFile (path);
        File resourceFile (rp);
        
        TemporaryFile tempFile (resourceFile);
        
        FileOutputStream outputStream (tempFile.getFile()); // [2]
        outputStream.setPosition(0);
        outputStream.setNewLineString("\n");
        
        Preset pr = Model::of()->preset;
        
        // Patch Header
        outputStream.writeText("FLIP, preset, flipotronics.com, 1\n",false,false,"\n");
        outputStream.writeText(pr.name + "\n",false,false,"\n");
        outputStream.writeText(pr.author + "\n",false,false,"\n");
        outputStream.writeText(pr.desc + "\n",false,false,"\n");
        outputStream.writeText(pr.tags + "\n",false,false,"\n");
        outputStream.writeText(String(pr.tuning) + "\n"      ,false,false,"\n");
        
        // Patch Data
        std::map<E_Module,std::map<int, Param>> p = pr.params;
        
        std::map<E_Module,std::map<int, Param>>::iterator    it = p.begin();
        while (it != p.end()){
            auto mod = it->first;
            std::cout << mod << std::endl;
            if(mGlobal == mod){
                
            }
            map<int, Param> par = p[mod];
            std::map<int, Param>::iterator iti = par.begin();
            while (iti != par.end()) {
                Param param = par[iti->first];
                std::cout << param.name << std::endl;
                if(((int)param.module)  > -1 && param.pid > -1){
                    String line = String(param.module) + "," + String(param.pid) +"," +   String(param.valF) + "\n";
                    outputStream.writeText(line,false,false,"\n");
                }
                ++iti;
            }
            ++it;
        }
        
        outputStream.flush();
        
        bool success = tempFile.overwriteTargetFileWithTemporary();
        std::cout << "saved to  " << rp.getFullPathName() << std::endl;
    }
    
    private:
};

#endif /* FileManager_h */
