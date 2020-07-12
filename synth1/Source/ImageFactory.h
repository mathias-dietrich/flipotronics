//
//  ImageFactory.h
//  synth1
//
//  Created by Mathias Dietrich on 24.06.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef ImageFactory_h
#define ImageFactory_h

template<typename T> struct map_init_helper
{
    T& data;
    map_init_helper(T& d) : data(d) {}
    map_init_helper& operator() (typename T::key_type const& key, typename T::mapped_type const& value)
    {
        data[key] = value;
        return *this;
    }
};

template<typename T> map_init_helper<T> map_init(T& item)
{
    return map_init_helper<T>(item);
}

enum E_Image {eMeter, ePoti, ePotiMaster, eFader,eModWheel, ePitchWheel, eExpressionWheel, eFloppy};

class ImageFactory{
public:
    
    static ImageFactory& of()
    {
        static ImageFactory   instance;
        return instance;
    }
    ImageFactory(ImageFactory const&) = delete;
    void operator=(ImageFactory const&)  = delete;
    
    void close(){
         png.clear();
    }
    
    void init(){
        map_init(imgEnumMap)
            (eMeter, "meter.png")
            (ePoti, "poti.png")
            (ePotiMaster, "potiMaster.png")
            (eFader, "fader.png")
            (eModWheel, "modwheel.png")
            (ePitchWheel, "pitchwheel.png")
            (eFloppy, "floppy.png")
            (eExpressionWheel, "expressionWheel.png");
        
        String filePath = File::getCurrentWorkingDirectory().getFullPathName();
       
        File  dir = File(filePath).getChildFile("images");
    
        std::cout << " filePath  " << dir.getFullPathName() << std::endl;
        
        std::map<E_Image, const char*>::iterator it;
        for ( it = imgEnumMap.begin(); it != imgEnumMap.end(); it++ ) {
            png[it->first ] = ImageFileFormat::loadFrom(dir.getChildFile(imgEnumMap[it->first ]));
        }
        
     std::cout << " loaded images " <<  png.size() << std::endl;
    }
    
    std::map<E_Image, Image > png;
    
    private:
    ImageFactory(){}
    
    ~ImageFactory(){
       
    }
   std::map<E_Image, const char*> imgEnumMap;
};

#endif /* ImageFactory_h */
