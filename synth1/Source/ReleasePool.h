//
//  ReleasePool.h
//  synth1
//
//  Created by Mathias Dietrich on 17.06.20.
//  Copyright © 2020 Flipotronics. All rights reserved.
//

#ifndef ReleasePool_h
#define ReleasePool_h

#include <stdio.h>
#include <JuceHeader.h>

class ReleasePool : private Timer{
public:
    ReleasePool(){
        startTimer(1000);
    }
    
    template<typename T> void add (const std::shared_ptr<T>& object){
        if(object.epmty()){
            return;
        }
        std::lock_guard<std::mutex> lock(m);
        pool.emplace_back(object);
    }
    
private:
    void timerCallback() override {
         std::lock_guard<std::mutex> lock(m);
          pool.erase(
            std::remove_if(pool.begin(), pool.end(), [] (auto& object){
            return object.use_count() <= 1;
        }),
        pool.end());
    }

    std::vector<std::shared_ptr<void>> pool;
    std::mutex m;
};
#endif /* ReleasePool_h */
