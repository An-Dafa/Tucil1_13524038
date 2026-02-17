#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>
#include <map>
#include <iostream>

struct Point {
    int row;
    int col;
};

class Board {
public:
    // Basically a constructor
    Board();

    // So the idea is parsing the raw text lines that we got from txt file into internal grid and regionMap that I will expalin it later :D
    void load(const std::vector<std::string>& rawLines);

    // Basically a getter / returns the total number of rows and columns
    int getRows() const;
    int getCols() const;

    // Returns a list of all unique region characters (['A', 'B', 'C']) to know how many regions are
    std::vector<char> getUniqueRegions() const;

    // Returns all cell coordinates belonging to a specific region color, it's the regionMap thing
    const std::vector<Point>& getCellsForRegion(char regionChar) const;

    char getRegionAt(int r, int c) const;
    
    // Checks if placing a queen at (r, c) is valid or not
    bool isValidPlacement(int r, int c) const;

    // Modifies the board state to place a queen
    void placeQueen(int r, int c);

    // Reverses a move or unplace the queen
    void removeQueen(int r, int c);

    // Returns true if a queen is currently placed at (r, c)
    bool hasQueen(int r, int c) const;
    
    // Returns the current state of the grid for the print state (spec)
    std::vector<std::string> getCurrentState() const;

    // Prints the current state to the console (for debugging)
    void print() const;

private:
    int rows;
    int cols;

    // The static layout of the board (Colors 'A', 'B', et cetera)
    std::vector<std::string> originalGrid;

    // The dynamic state of the board (Where queens are)
    // true = queen is here, false = empty.
    std::vector<std::vector<bool>> queenGrid;

    // regionMap['A'] = [{0,0}, {0,1}, {1,0}]
    std::map<char, std::vector<Point>> regionMap;
    
    // Stores the unique regions in the order they were found or sorted
    std::vector<char> uniqueRegions;
};

// Hmm I think it's enough, by the way I also uses github online references for designing how to store the input, and I came up with this idea, using map ;D

#endif