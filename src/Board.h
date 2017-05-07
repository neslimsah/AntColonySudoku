//
//  Board.h
//  sudoku
//
//  Created by Neslisah Torosdagli on 11/9/15.
//  Copyright (c) 2015 Neslisah Torosdagli. All rights reserved.
//

#ifndef __sudoku__Board__
#define __sudoku__Board__

#include <stdio.h>
#include "Cell.h"

class Board{
    
private:
    Cell mCells[9][9];
    
    bool mVerbose;
    
    std::vector<int> computeRowValues(int rowId, int index);
    std::vector<int> computeColValues(int colId, int index);
    std::vector<int> computeSubBoardValues(int rowId, int colId, int index);
    
    bool isColValid(int colId, int index);
    bool isRowValid(int rowId, int index);
    bool isSubBoardValid(int rowId, int colId, int index);
    bool startAntPath(int *pRow, int *pCol, int *pValue);
    void Copy(Board src, Board dst);
    void simplify();
    
public:
    Board(bool verbose);
    ~Board();
    
    Board(const Board &other);
    
    void set(int rowId, int colId, int value, int index);
    int simplifyRow(int rowId, int index);
    int simplifyCol(int colId, int index);
    int simplifySubBoard(int subBoardId, int index); // subBoardId from 0 to 9
    bool isValid(int index);
    bool isFinished(int index);
    void runACO();
    void solve();
    void print(int index);
 };

#endif /* defined(__sudoku__Board__) */
