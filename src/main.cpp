//
//  main.cpp
//  sudoku
//
//  Created by Neslisah Torosdagli on 11/9/15.
//  Copyright (c) 2015 Neslisah Torosdagli. All rights reserved.
//


#include "Board.h"
#include "FileIO.h"
#include "localTimer.h"

#include <iostream>

int main(int argc, char **argv){
    
    bool verbose = true;
    
    std::string filename = "puzzle1.sdk";
    
    if (argc > 1){
        filename = std::string(argv[1]);
    }
    
    if (argc > 2){
        std::string verboseInp = std::string(argv[2]);
        if (verboseInp.compare("silent") == 0){
            verbose = false;
            std::cout << "SILENT MODE ... " << std::endl;
        }
    }
    
    Board board(verbose);
    
    parse(filename, &board);
    
    std::cout << std::endl << "Solving : \"" << filename << "\""<< std::endl;
    std::cout << std::endl << "Initial Board : " << std::endl << std::endl;
    board.print(0);
    
    localTimer timer;
    timer.start();
    board.solve();
    timer.stop();
    
    std::cout << std::endl << "Solved Board : " << std::endl << std::endl;
    board.print(0);
    
    std::cout << std::endl << "Solved in " << timer.getDuration() << "s." << std::endl;
    
    std::cout << std::endl << std::endl;

    return 0;
}
