#ifndef SOLVE_H
#define SOLVE_H

#include "board.h"
#include <iostream>

class Solve {
public:
    // The smart solution I guess :), I don't know if this allowed or not but I made two solution :3
    bool solve(Board& board);

    // The very "Naive" Brute Force, I hope this work with large n-test cases
    bool solveBruteForce(Board& board);

    // For the output (live update)
    void setFrequency(long long k);

    long long getCasesChecked() const { 
        return casesChecked; 
    }

private:
    bool solveRecursive(Board& board, int regionIndex);

    bool solveBruteForce(Board& board, int regionIndex, std::vector<Point>& queens);

    bool checkFullBoard(const Board& board, const std::vector<Point>& queens);

    long long casesChecked = 0;

    long long frequency = 0;
};

#endif