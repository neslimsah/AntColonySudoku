//
//  localTimer.h
//  VolumeRendering
//
//  Created by Neslisah Torosdagli on 7/7/15.
//  Copyright (c) 2015 Neslisah Torosdagli. All rights reserved.
//

#ifndef __VolumeRendering__localTimer__
#define __VolumeRendering__localTimer__

#include <stdio.h>
#include <string>
#include <ctime>
#include <chrono>

class localTimer{
private:
	std::chrono::high_resolution_clock::time_point mStart;
	std::chrono::high_resolution_clock::time_point mStop;
public:
    
    localTimer();
    ~localTimer();
    
    void start();
    void stop();
    float getDuration();
};

#endif /* defined(__VolumeRendering__localTimer__) */
