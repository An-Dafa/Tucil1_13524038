#include "board.h"
#include <iostream>

using namespace std;

Board::Board() : rows(0), cols(0) {}

void Board::load(const vector<string>& rawLines) {
    originalGrid = rawLines;
    rows = rawLines.size();

    if (rows > 0) {
        cols = rawLines[0].size();
    }
    else {
        cols = 0;
    }

    queenGrid.assign(rows, vector<bool>(cols, false));
    regionMap.clear();
    uniqueRegions.clear();

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            char regionChar = originalGrid[r][c];
            regionMap[regionChar].push_back({r,c});
        }
    }

    for (auto const& [key,val]: regionMap) {
        uniqueRegions.push_back(key);
    }
}

int Board::getRows() const {
    return rows;
}
int Board::getCols() const {
    return cols;
}

vector<char> Board::getUniqueRegions() const {
    return uniqueRegions;
}

const vector<Point>& Board::getCellsForRegion(char regionChar) const {
    return regionMap.at(regionChar);
}

char Board::getRegionAt(int r, int c) const {
    if (r >= 0 && r < rows && c >= 0 && c < cols) {
        return originalGrid[r][c];
    }
    return ' ';
}
    
bool Board::isValidPlacement(int r, int c) const {
    if (r < 0 || r >= rows || c < 0 || c >= cols) return false;

    for (int i = 0; i < cols; i++) {
        if(queenGrid[r][i]) return false;
    }

    for (int i = 0; i < rows; i++) {
        if(queenGrid[i][c]) return false;
    }

    for (int ar = -1; ar <= 1; ar++) {
        for(int ac = -1; ac <= 1; ac++) {
            int nr = r + ar;
            int nc = c + ac;

            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
                if (queenGrid[nr][nc]) return false;
            }
        }
    }
    return true;
}

void Board::placeQueen(int r, int c) {
    if (r >= 0 && r < rows && c >= 0 && c < cols) {
        queenGrid[r][c] = true;
    }
    return;
}

void Board::removeQueen(int r, int c) {
    if (r >= 0 && r < rows && c >= 0 && c < cols) {
        queenGrid[r][c] = false;
    }
    return;
}

bool Board::hasQueen(int r, int c) const {
    if (r >= 0 && r < rows && c >= 0 && c < cols) {
        return queenGrid[r][c];
    }
    return false;
}
    
vector<string> Board::getCurrentState() const {
    vector<string> curGrid = originalGrid;

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (queenGrid[r][c]) {
                curGrid[r][c] = '#'; // '#' for the queen
            }
        }
    }
    return curGrid;
}

void Board::print() const {
    vector<string> curGrid = getCurrentState();
    for (const string& row: curGrid) {
        cout << row << '\n';
    }
}