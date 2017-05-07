//
//  Cell.h
//  sudoku
//
//  Created by Neslisah Torosdagli on 11/9/15.
//  Copyright (c) 2015 Neslisah Torosdagli. All rights reserved.
//

#ifndef __sudoku__Cell__
#define __sudoku__Cell__

#include <stdio.h>
#include <vector>

class Cell{
public:
    short mListOfValues[2]; // 0th bit - 0 can be used in this cell or not, 10th bit - 9 can be used in this cell or not
    short mValue[2]; // initially 0 if not set by the puzzle
    
    float mPheromone[9];

    Cell();
    ~Cell();
    Cell(const Cell &other);
    void addValueToList(int bit, int index);
    void removeValueFromList(int bit, int index);
    std::vector<int> getListOfValues(int index);
};

#endif /* defined(__sudoku__Cell__) */
