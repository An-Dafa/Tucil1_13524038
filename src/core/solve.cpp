#include "solve.h"
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

void Solve::setFrequency(long long k) {
    frequency = k;
}

bool Solve::solve(Board& board) {
    casesChecked = 0;
    bool success = solveRecursive(board, 0);
    cout << "\nCases checked: " << casesChecked << '\n';
    return success;
}

bool Solve::solveRecursive(Board& board, int regionIndex) {
    const vector<char>& regions = board.getUniqueRegions();
    if (board.getRows() != board.getCols()) return false;
    if (regions.size() != board.getRows()) return false;
    if (regionIndex >= regions.size()) return true;

    char currentRegionChar = regions[regionIndex];
    const vector<Point>& candidates = board.getCellsForRegion(currentRegionChar);

    for (const Point& p : candidates) {
        casesChecked++; 

        if (board.isValidPlacement(p.row, p.col)) {
            board.placeQueen(p.row, p.col);

            if (frequency > 0 && casesChecked % frequency == 0) {
                cout << "--- Step: " << casesChecked << " ---\n";
                board.print();
            }
            if (solveRecursive(board, regionIndex + 1)) return true;
            board.removeQueen(p.row, p.col);
        }
    }
    return false;
}

bool Solve::solveBruteForce(Board& board) {
    casesChecked = 0;
    vector<Point> tempQueens;
    bool success = solveBruteForce(board, 0, tempQueens);
    cout << "\nCases checked: " << casesChecked << '\n';
    return success;
}

bool Solve::solveBruteForce(Board& board, int regionIndex, vector<Point>& queens) {
    const vector<char>& regions = board.getUniqueRegions();
    if (board.getRows() != board.getCols()) return false;
    if (regions.size() != board.getRows()) return false;
    if (frequency > 0 && casesChecked > 0 && casesChecked % frequency == 0) {
        for (const Point& p : queens) {
        board.placeQueen(p.row, p.col);
        }
        cout << "--- Step: " << casesChecked << " ---\n";
        board.print();
        for (const Point& p : queens) {
            board.removeQueen(p.row, p.col);
        }
    }

    if (regionIndex >= regions.size()) {
        casesChecked++;
        if (checkFullBoard(board, queens)) {
            for (const Point& p : queens) {
                board.placeQueen(p.row, p.col);
            }
            return true; 
        }
        return false;
    }

    char currentRegionChar = regions[regionIndex];
    const vector<Point>& candidates = board.getCellsForRegion(currentRegionChar);

    for (const Point& p : candidates) {
        queens.push_back(p); 
        casesChecked++; 
        if (solveBruteForce(board, regionIndex + 1, queens)) return true;
        queens.pop_back();
    }
    return false;
}

bool Solve::checkFullBoard(const Board& board, const vector<Point>& queens) {
    for (size_t i = 0; i < queens.size(); ++i) {
        for (size_t j = i + 1; j < queens.size(); ++j) {
            Point p1 = queens[i];
            Point p2 = queens[j];

            if (p1.row == p2.row) return false;
            if (p1.col == p2.col) return false;

            int dr = abs(p1.row - p2.row);
            int dc = abs(p1.col - p2.col);
            if (dr <= 1 && dc <= 1) return false; 
        }
    }
    return true;
}