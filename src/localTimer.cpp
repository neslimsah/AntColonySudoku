//
//  localTimer.cpp
//  VolumeRendering
//
//  Created by Neslisah Torosdagli on 7/7/15.
//  Copyright (c) 2015 Neslisah Torosdagli. All rights reserved.
//

#include "localTimer.h"
#include <iostream>  
#include <math.h>

const double nanoToSecond = 1000000000.0;

localTimer::localTimer(){
}

localTimer::~localTimer(){
}

void localTimer::start(){
    mStart = std::chrono::high_resolution_clock::now();//clock();
    mStop = mStart;
}

void localTimer::stop(){
    mStop = std::chrono::high_resolution_clock::now();//clock();
}

float localTimer::getDuration(){
    
	std::chrono::nanoseconds timePassed = std::chrono::duration_cast<std::chrono::nanoseconds>(mStop-mStart);
    		//((float)(mStop - mStart))/CLOCKS_PER_SEC; // in miliseconds
   
    float duration = timePassed.count() / nanoToSecond;
    duration = round(duration * 100.0) / 100.f;
    
    return (duration);
}