//
//  FileIO.h
//  sudoku
//
//  Created by Neslisah Torosdagli on 11/9/15.
//  Copyright (c) 2015 Neslisah Torosdagli. All rights reserved.
//

#ifndef __sudoku__FileIO__
#define __sudoku__FileIO__

#include <stdio.h>
#include "Board.h"

bool parse(std::string filename, Board *pBoard);
bool saveFile(std::string filename);

#endif /* defined(__sudoku__FileIO__) */
