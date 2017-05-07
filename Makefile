all:
	g++ -std=c++11 -g src/localTimer.cpp src/FileIO.cpp src/Cell.cpp src/Board.cpp src/main.cpp -o sudoku.x
clean:
	rm sudoku.x
