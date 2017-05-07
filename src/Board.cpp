//
//  Board.cpp
//  sudoku
//
//  Created by Neslisah Torosdagli on 11/9/15.
//  Copyright (c) 2015 Neslisah Torosdagli. All rights reserved.
//

#include "Board.h"
#include <iostream>

Board::Board(bool verbose){
    mVerbose = verbose;
}

Board::~Board(){
}

Board::Board(const Board &other){
    
    for (int r=0;r<9;r++){
        for (int c=0;c<9;c++){
            mCells[r][c] = other.mCells[r][c];
        }
    }
}

std::vector<int> Board::computeRowValues(int rowId, int index){
    
    std::vector<int> lstOfValues;
    for (int c=0;c<9;c++){
        
        if (mCells[rowId][c].mValue[index] > 0){
                lstOfValues.push_back(mCells[rowId][c].mValue[index]);
        }
    }
    
    return (lstOfValues);
}

std::vector<int> Board::computeColValues(int colId, int index){
    
    std::vector<int> lstOfValues;
    for (int r=0;r<9;r++){
        
        if (mCells[r][colId].mValue[index] > 0){
                lstOfValues.push_back(mCells[r][colId].mValue[index]);
        }
    }

    return (lstOfValues);
}

std::vector<int> Board::computeSubBoardValues(int rowId, int colId, int index){
    
    std::vector<int> lstOfValues;
    for (int r=rowId;r<rowId+3;r++){
        for (int c=colId;c<colId+3;c++){
            
            if (mCells[r][c].mValue[index] > 0){
                    lstOfValues.push_back(mCells[r][c].mValue[index]);
            }
        }
    }
    
    return (lstOfValues);
}

int Board::simplifyRow(int rowId, int index){
    
    int numUpdates = 0;
    std::vector<int> lstOfActualValues = computeRowValues(rowId, index);
    
    for (int c=0;c<9;c++){
        
        if (mCells[rowId][c].mValue[index] > 0){
            continue;
        }
        
        std::vector<int> cellValues = mCells[rowId][c].getListOfValues(index);
        
        if (cellValues.size() == 1){
            mCells[rowId][c].mValue[index] = cellValues.data()[0];
            lstOfActualValues = computeRowValues(rowId, index);
            numUpdates++;
            continue;
        }
        
        for (std::vector<int>::iterator it=lstOfActualValues.begin();it != lstOfActualValues.end(); ++it){
            int value = *it;
            std::vector<int>::iterator iter = std::find(cellValues.begin(), cellValues.end(), value);
            
            if (iter != cellValues.end()){ // found in the list, so remove it
                
                mCells[rowId][c].removeValueFromList(value, index);
                numUpdates++;
            }
        }
    }
    
    return (numUpdates);
}

int Board::simplifyCol(int colId, int index){
    
    int numUpdates = 0;
    
    std::vector<int> lstOfActualValues = computeColValues(colId, index);
    
    for (int r=0;r<9;r++){
        
        if (mCells[r][colId].mValue[index] > 0){
            continue;
        }
        
        std::vector<int> cellValues = mCells[r][colId].getListOfValues(index);
        if (cellValues.size() == 1){
            mCells[r][colId].mValue[index] = cellValues.data()[0];
            lstOfActualValues = computeColValues(colId, index);
            numUpdates++;
            continue;
        }
        for (std::vector<int>::iterator it=lstOfActualValues.begin();it != lstOfActualValues.end(); ++it){
            int value = *it;
            std::vector<int>::iterator iter = std::find(cellValues.begin(), cellValues.end(), value);
            
            if (iter != cellValues.end()){ // found in the list, so remove it
                
                mCells[r][colId].removeValueFromList(value, index);
                numUpdates++;
                
                cellValues = mCells[r][colId].getListOfValues(index); // for testing
            }
        }
    }
    
    return (numUpdates);
}

int Board::simplifySubBoard(int subBoardId, int index){
    
    int numUpdates = 0;
    
    int rowId = subBoardId / 3;
    int colId = (subBoardId - rowId * 3);
    
    rowId *= 3;
    colId *= 3;
    
    std::vector<int> lstOfActualValues = computeSubBoardValues(rowId, colId, (index == 0));
    
    for (int r=rowId;r<rowId+3;r++){
        for (int c=colId;c<colId+3;c++){
            
            if (mCells[r][c].mValue[index] > 0){
                continue;
            }
            
            std::vector<int> cellValues = mCells[r][c].getListOfValues(index);
            if (cellValues.size() == 1){
                mCells[r][c].mValue[index] = cellValues.data()[0];
                lstOfActualValues = computeSubBoardValues(rowId, colId, index);
                numUpdates++;
                continue;
            }
            
            for (std::vector<int>::iterator it=lstOfActualValues.begin();it != lstOfActualValues.end(); ++it){
                int value = *it;
                std::vector<int>::iterator iter = std::find(cellValues.begin(), cellValues.end(), value);
            
                if (iter != cellValues.end()){ // found in the list, so remove it
                
                    mCells[r][c].removeValueFromList(value, index);
                    numUpdates++;
                }
            }
        }
    }
    
    return (numUpdates);
}

void Board::set(int rowId, int colId, int value, int index){
    
    mCells[rowId][colId].mValue[index] = value;
}

bool Board::isColValid(int colId, int index){
    
    int values[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::vector<int> lstOfActualValues = computeColValues(colId, index);
    
    for (int r=0;r<9;r++){
        
        int value = mCells[r][colId].mValue[index];
        if (value > 0){
            if (values[value-1] > 0){
                return (false);
            }
            values[value-1] = 1;
            continue;
        }
        
        // Check for number of candidates for unassigned cells
        std::vector<int> cellValues = mCells[r][colId].getListOfValues(index);
        
        for (std::vector<int>::iterator it=lstOfActualValues.begin();it != lstOfActualValues.end(); ++it){
            int value = *it;
            std::vector<int>::iterator iter = std::find(cellValues.begin(), cellValues.end(), value);
            
            if (iter != cellValues.end()){ // found in the list, so remove it
                
                mCells[r][colId].removeValueFromList(value, index);
            }
        }
        
        cellValues = mCells[r][colId].getListOfValues(index);
        
        if (cellValues.size() == 0){
            return (false);
        }
    }
    
    return (true);
}

bool Board::isRowValid(int rowId, int index){
    
    int values[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    
    std::vector<int> lstOfActualValues = computeRowValues(rowId, index);
    
    for (int c=0;c<9;c++){
        
        int value = mCells[rowId][c].mValue[index];
        if (value > 0){
            if (values[value-1] > 0){
                return (false);
            }
            values[value-1] = 1;
            continue;
        }
        
        // Check for number of candidates for unassigned cells
        std::vector<int> cellValues = mCells[rowId][c].getListOfValues(index);
        
        for (std::vector<int>::iterator it=lstOfActualValues.begin();it != lstOfActualValues.end(); ++it){
            int value = *it;
            std::vector<int>::iterator iter = std::find(cellValues.begin(), cellValues.end(), value);
                
            if (iter != cellValues.end()){ // found in the list, so remove it
            
                mCells[rowId][c].removeValueFromList(value, index);
            }
        }
        
        cellValues = mCells[rowId][c].getListOfValues(index);
        
        if (cellValues.size() == 0){
            return (false);
        }
    }
    
    return (true);
    
}

bool Board::isSubBoardValid(int rowId, int colId, int index){
    
    int values[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

    rowId /= 3;
    colId /= 3;
    
    rowId *= 3;
    colId *= 3;

    std::vector<int> lstOfActualValues = computeSubBoardValues(rowId, colId, index);
    
    for (int r=rowId;r<rowId+3;r++){
      for (int c=colId;c<colId+3;c++){
        
          int value = mCells[r][c].mValue[index];
          if (value > 0){
            if (values[value-1] > 0){
                return (false);
            }
            values[value-1] = 1;
            continue;
          }
          
          // Check for number of candidates for unassigned cells
          std::vector<int> cellValues = mCells[r][c].getListOfValues(index);
          
          for (std::vector<int>::iterator it=lstOfActualValues.begin();it != lstOfActualValues.end(); ++it){
              int value = *it;
              std::vector<int>::iterator iter = std::find(cellValues.begin(), cellValues.end(), value);
              
              if (iter != cellValues.end()){ // found in the list, so remove it
                  
                  mCells[r][c].removeValueFromList(value, index);
              }
          }
          
          cellValues = mCells[r][c].getListOfValues(index);
          
          if (cellValues.size() == 0){
              return (false);
          }
      }
    }
    
    return (true);
}

bool Board::isValid(int index){
    
    for (int r=0;r<9;r++){
        for (int c=0;c<9;c++){
            
            if ((!isRowValid(r, index)) ||
                (!isColValid(c, index)) ||
                (!isSubBoardValid(r, c, index)))
                return (false);
        }
    }
    
    return (true);
}

void Board::runACO(){
    
    int iteration = 0;
    int validCount = 1;
    int totalIteration = 0;
    
    while (!isFinished(1) || !isValid(1)){
        
        int row, col, value;
        
        Board oldBoard(mVerbose);
        Copy(*this, oldBoard);
        
        bool valid = startAntPath(&row, &col, &value);
        
        if (valid){
            valid = isValid(1);
        }
        
        float punishment = 0.005f;
        if (!valid){ // decrement pheromones
            Copy(oldBoard, *this);
            mCells[row][col].mPheromone[value-1] = std::max(mCells[row][col].mPheromone[value-1] - punishment, 0.f);
            
        }
        else{ // increment pheromones
            simplify();
            
            //std::cout << "Simplified : " << std::endl;
            //print(1);
            
            valid = isValid(1);
            
            if (!valid){
                Copy(oldBoard, *this);
                mCells[row][col].mPheromone[value-1] = std::max(mCells[row][col].mPheromone[value-1] - punishment, 0.f);
            }
            else{
                validCount++;
                mCells[row][col].mPheromone[value-1] += 1;
            }
        }
        
        if (++iteration > (validCount + 2)){ // was 1000
            if (mVerbose){
                std::cout << std::endl << "Iteration : " << totalIteration++ << std::endl << std::endl;
            
                print(1);
            }
        
            //if (!isValid(1))
            {
                // no feasible solution, try from the beginning
                for (int r=0;r<9;r++){
                    for (int c=0;c<9;c++){
                        mCells[r][c].mValue[1] = mCells[r][c].mValue[0];
                        mCells[r][c].mListOfValues[1] = mCells[r][c].mListOfValues[0];
                    }
                }
                iteration = 0;
                validCount = 1;
                simplify();
            }
        }
    }
    
    for (int r=0;r<9;r++){
        for (int c=0;c<9;c++){
            mCells[r][c].mValue[0] = mCells[r][c].mValue[1];
        }
    }
    
}

bool Board::startAntPath(int *pRow, int *pCol, int *pValue){
    
    std::vector<int> unassignedCells;
    
    for (int r=0;r<9;r++){
        for (int c=0;c<9;c++){
            if (mCells[r][c].mValue[1] == 0){
                unassignedCells.push_back((r*9)+c);
            }
        }
    }
    
    if (unassignedCells.size() == 0)
        return (false);
    
    int rnd = rand() % unassignedCells.size();
    rnd = unassignedCells.data()[rnd];
    int row = rnd / 9;
    rnd = rnd - (row * 9);
    int col = rnd;
    
    float maxPher = -0.1;
    int selectedValue = -1;
    
    std::vector<int> cellValues = mCells[row][col].getListOfValues(1);
    
    if (cellValues.size() > 0){
        maxPher = mCells[row][col].mPheromone[cellValues.data()[0]] - 0.1; //-1.f * (cellValues.data()[0] + 0.1f);
    }
    
    for (std::vector<int>::iterator it=cellValues.begin();it!=cellValues.end();++it){
        
        int index = *it;
        
        if (mCells[row][col].mPheromone[index] >= maxPher) {
            maxPher = mCells[row][col].mPheromone[index];
            selectedValue = cellValues.data()[it-cellValues.begin()];
        }
    }
    
    int sz = cellValues.size();
    
    if (selectedValue == -1){
        
        if (sz == 0){
            return (false);
        }
        rnd = rand() % sz;
        selectedValue = cellValues.data()[rnd];
    }
    
    mCells[row][col].mValue[1] = selectedValue;
    
    *pRow = row;
    *pCol = col;
    *pValue = selectedValue;
    
    return (true);
}

void Board::solve(){
    
    simplify();
    runACO();
}


void Board::Copy(Board src, Board dst){

    for (int r=0;r<9;r++){
        for (int c=0;c<9;c++){
            dst.mCells[r][c] = src.mCells[r][c];
        }
    }
}

void Board::simplify(){
    
    while (true){
        
        int numUpdates = 0;
        for (int r=0;r<9;r++){
            int n = simplifyRow(r, 1);
            numUpdates += n;
        }
        
        for (int c=0;c<9;c++){
            int n = simplifyCol(c, 1);
            numUpdates += n;
        }
        
        for (int s=0;s<9;s++){
            int n = simplifySubBoard(s, 1);
            numUpdates += n;
        }
        
        if (numUpdates == 0){
            break;
        }
    }
}

bool Board::isFinished(int index){
    
    for (int r=0;r<9;r++){
        for (int c=0;c<9;c++){
            if (mCells[r][c].mValue[index] == 0){
                return (false);
            }
        }
    }
    
    return (true);
            
}

void Board::print(int index){
    
    for (int r=0;r<9;r++){
        for (int c=0;c<9;c++){
            if (mCells[r][c].mValue[index] > 0){
                std::cout << " " << mCells[r][c].mValue[index] << " ";
            }
            else{
                std::cout << " _ ";
            }
        }
        std::cout << std::endl;
    }
}