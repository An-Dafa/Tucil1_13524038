#include "file_utils.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

vector<string> readInputFile(const string& filename) {
    string line;
    vector<string> rawLines;
    ifstream inputfile(filename);

    if (!inputfile) {
        cout << "Error opening input file" << '\n';
        return {};
    }

    while (getline(inputfile,line)) {
        rawLines.push_back(line);
    }
    return rawLines;
}

void saveSolution(const string& filename, const vector<string>& gridData, long long timeMs, long long cases, const string& algo) {
    
    ofstream outfile(filename);

    if (!outfile) {
        cout << "Error: Could not create output file " << filename << '\n';
        return;
    }

    for (const string& row : gridData) {
        outfile << row << '\n';
    }

    outfile << "\n";
    outfile << "Algorithm: " << algo << "\n";
    outfile << "Time Taken: " << timeMs << " ms\n";
    outfile << "Cases Checked: " << cases << "\n";

    outfile.close();
    cout << "Saved solution to " << filename << endl;
}