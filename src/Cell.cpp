//
//  Cell.cpp
//  sudoku
//
//  Created by Neslisah Torosdagli on 11/9/15.
//  Copyright (c) 2015 Neslisah Torosdagli. All rights reserved.
//

#include "Cell.h"
#include <iostream>

static short mBitValues[10] = {0x0000, 0x0001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0100};

static short cleanBits = 0x03FF;

Cell::Cell(){
    
    mListOfValues[0] = 0x03FF; // set all applicable values to 1
    mListOfValues[1] = 0x03FF; // set all applicable values to 1
    mValue[0] = 0;
    mValue[1] = 0;
    
    for (int idx=0;idx<9;idx++){
        mPheromone[idx] = 0.f;
    }
}

Cell::~Cell(){
}

Cell::Cell(const Cell &other){
    mListOfValues[0] = other.mListOfValues[0];
    mListOfValues[1] = other.mListOfValues[1];
    mValue[0] = other.mValue[0];
    mValue[1] = other.mValue[1];
    
    for (int idx=0;idx<9;idx++){
        mPheromone[idx] = other.mPheromone[idx];
    }
}

void Cell::addValueToList(int bit, int index){

    short bitValue = mBitValues[bit];
    mListOfValues[index] |= bitValue;
}

void Cell::removeValueFromList(int bit, int index){
    
    short bitValue = ~(mBitValues[bit]);
    bitValue &= cleanBits;
    mListOfValues[index] &= bitValue;
}

std::vector<int> Cell::getListOfValues(int index){
    
    std::vector<int> lst;
    
    for (int idx=0;idx<10;idx++){
        if (mListOfValues[index] & mBitValues[idx]){
            lst.push_back(idx);
        }
    }
    
    return (lst);
}