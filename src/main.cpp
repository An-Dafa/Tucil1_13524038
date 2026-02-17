#include "raylib.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <chrono>

#include "core/board.h"
#include "core/solve.h"
#include "utils/file_utils.h"
#include "utils/tinyfiledialogs.h"

using namespace std;

#define PANEL_WIDTH 280
#define BG_COLOR RAYWHITE
#define PANEL_COLOR (Color){230, 230, 230, 255}

Color GetRegionColor(char region) {
    if (region == ' ') return LIGHTGRAY;
    int hash = (int)region * 11423; 
    return (Color){
        (unsigned char)((hash % 100) + 155), 
        (unsigned char)(((hash / 100) % 100) + 155), 
        (unsigned char)(((hash / 10000) % 100) + 155), 
        255 
    };
}

bool solveDirection(Solve& solver, Board& board, bool bruteForce, long long freq, string filename) {
    streambuf* originalCout = cout.rdbuf();
    ofstream file(filename);
    if (file.is_open()) {
        cout.rdbuf(file.rdbuf());
    }

    solver.setFrequency(freq);
    bool result = false;

    if (bruteForce) result = solver.solveBruteForce(board);
    else result = solver.solve(board);

    cout.rdbuf(originalCout);
    file.close();
    return result;
}

bool DrawButton(Rectangle bounds, const char* text, bool active = true) {
    if (!active) {
        DrawRectangleRec(bounds, Fade(LIGHTGRAY, 0.5f));
        DrawRectangleLinesEx(bounds, 1, GRAY);
        DrawText(text, bounds.x + 10, bounds.y + 10, 20, Fade(GRAY, 0.5f));
        return false;
    }
    Vector2 mousePoint = GetMousePosition();
    bool isHovered = CheckCollisionPointRec(mousePoint, bounds);
    DrawRectangleRec(bounds, isHovered ? SKYBLUE : WHITE);
    DrawRectangleLinesEx(bounds, 2, isHovered ? BLUE : DARKGRAY);
    int textWidth = MeasureText(text, 20);
    DrawText(text, bounds.x + (bounds.width - textWidth)/2, bounds.y + 10, 20, BLACK);
    return (isHovered && IsMouseButtonReleased(MOUSE_LEFT_BUTTON));
}

int main() {
    InitWindow(1000, 700, "Queens Solver");
    SetTargetFPS(60);

    Board board;
    Solve solver;

    bool fileLoaded = false;
    bool isSolved = false;
    string currentFile = "None";
    string statusMsg = "Please Load a File";
    string lastAlgo = "";
    
    long long timeTaken = 0;
    long long casesChecked = 0;
    long long frequency = 1000;
    bool saveProcess = false;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BG_COLOR);

        DrawRectangle(0, 0, PANEL_WIDTH, 700, PANEL_COLOR);
        DrawLine(PANEL_WIDTH, 0, PANEL_WIDTH, 700, GRAY);

        int y = 20;
        DrawText("QUEEN SOLVER", 20, y, 30, DARKGRAY); y += 50;

        if (DrawButton((Rectangle){20, (float)y, 240, 40}, "Load Input File...")) {
            const char *filterPatterns[1] = { "*.txt" };
            const char *filePath = tinyfd_openFileDialog("Select Input File", "", 1, filterPatterns, "Text Files", 0);

            if (filePath) {
                try {
                    vector<string> lines = readInputFile(filePath);
                    board.load(lines);
                    
                    fileLoaded = true;
                    isSolved = false;
                    timeTaken = 0;
                    casesChecked = 0;
                    string fullPath = filePath;
                    size_t lastSlash = fullPath.find_last_of("/\\");
                    currentFile = (lastSlash == string::npos) ? fullPath : fullPath.substr(lastSlash + 1);
                    statusMsg = "File Loaded.";
                } 
                catch (...) {
                    statusMsg = "Error: Invalid File";
                }
            }
        }
        y += 50;
        
        DrawText(("File: " + currentFile).c_str(), 20, y, 20, fileLoaded ? BLACK : RED);
        y += 40;

        DrawText("OUTPUT OPTIONS", 20, y, 20, DARKGRAY); y += 25;
        
        DrawRectangle(20, y, 20, 20, saveProcess ? BLUE : WHITE);
        DrawRectangleLines(20, y, 20, 20, BLACK);
        DrawText("Save Process?", 50, y, 20, DARKGRAY);
        if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){20, (float)y, 200, 20}) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            saveProcess = !saveProcess;
        }
        y += 30;

        if (saveProcess) {
            DrawText("Freq:", 20, y+5, 20, DARKGRAY);
            if (DrawButton((Rectangle){80, (float)y, 50, 30}, "100")) frequency = 100;
            if (DrawButton((Rectangle){140, (float)y, 50, 30}, "1000")) frequency = 1000;
            y += 40;
        } 
        else {
            y += 40;
        }

        if (DrawButton((Rectangle){20, (float)y, 240, 45}, "Solve (Backtrack)", fileLoaded)) {
            statusMsg = "Solving...";
            EndDrawing(); 
            BeginDrawing();

            auto start = chrono::high_resolution_clock::now();
            bool success = false;
            
            if (saveProcess) {
                const char *lFilter[1] = { "*.txt" };
                const char *logPath = tinyfd_saveFileDialog("Save Process Log", "process_bt.txt", 1, lFilter, "Text File");
                
                if (logPath) success = solveDirection(solver, board, false, frequency, logPath);
                else success = solver.solve(board);
            } 
            else {
                success = solver.solve(board);
            }

            auto stop = chrono::high_resolution_clock::now();
            timeTaken = chrono::duration_cast<chrono::milliseconds>(stop - start).count();
            casesChecked = solver.getCasesChecked();
            lastAlgo = "Backtracking";

            if (success) {
                isSolved = true;
                statusMsg = "Solved!";
            } 
            else {
                isSolved = false;
                statusMsg = "No Solution Found";
            }
        }
        y += 55;

        if (DrawButton((Rectangle){20, (float)y, 240, 45}, "Solve (BruteForce)", fileLoaded)) {
            statusMsg = "Solving...";
            EndDrawing(); 
            BeginDrawing();

            auto start = chrono::high_resolution_clock::now();
            bool success = false;
            
            if (saveProcess) {
                const char *lFilter[1] = { "*.txt" };
                const char *logPath = tinyfd_saveFileDialog("Save Process Log", "process_bf.txt", 1, lFilter, "Text File");
                if (logPath) success = solveDirection(solver, board, true, frequency, logPath);
                else success = solver.solveBruteForce(board);
            } 
            else {
                success = solver.solveBruteForce(board);
            }
            
            auto stop = chrono::high_resolution_clock::now();
            timeTaken = chrono::duration_cast<chrono::milliseconds>(stop - start).count();
            casesChecked = solver.getCasesChecked();
            lastAlgo = "Brute Force";
            
            if (success) {
                isSolved = true;
                statusMsg = "Solved!";
            } 
            else {
                isSolved = false;
                statusMsg = "No Solution Found";
            }
        }
        y += 60;
        DrawText(TextFormat("Time: %lld ms", timeTaken), 20, y, 20, DARKBLUE); y += 25;
        DrawText(TextFormat("Cases: %lld", casesChecked), 20, y, 20, DARKPURPLE); y += 35;
        
        Color statusColor = DARKGREEN;
        if (statusMsg.find("Error") != string::npos || statusMsg.find("No Solution") != string::npos) {
            statusColor = RED;
        }
        DrawText(statusMsg.c_str(), 20, y, 20, statusColor);
        y += 35;

        if (isSolved) {
            if (DrawButton((Rectangle){20, (float)y, 240, 45}, "Save Final Result", true)) {
                const char *filterPatterns[1] = { "*.txt" };
                const char *savePath = tinyfd_saveFileDialog("Save Solution As...", ("solution_" + currentFile).c_str(), 1, filterPatterns, "Text File");
                if (savePath) {
                    saveSolution(savePath, board.getCurrentState(), timeTaken, casesChecked, lastAlgo);
                    statusMsg = "File Saved!";
                }
            }
        }

        if (fileLoaded) {
            int rows = board.getRows();
            int cols = board.getCols();
            int availableWidth = 1000 - PANEL_WIDTH - 40;
            int availableHeight = 700 - 40;
            int maxDim = max(rows, cols);
            int cellSize = min(availableWidth, availableHeight) / maxDim;
            int startX = PANEL_WIDTH + 20 + (availableWidth - (cols * cellSize)) / 2;
            int startY = 20 + (availableHeight - (rows * cellSize)) / 2;

            vector<string> grid = board.getCurrentState();

            for (int r = 0; r < rows; r++) {
                for (int c = 0; c < cols; c++) {
                    int x = startX + c * cellSize;
                    int py = startY + r * cellSize;

                    DrawRectangle(x, py, cellSize, cellSize, GetRegionColor(board.getRegionAt(r, c)));
                    DrawRectangleLines(x, py, cellSize, cellSize, BLACK);

                    if (grid[r][c] == '#') {
                        DrawCircle(x + cellSize/2, py + cellSize/2, cellSize/2.5f, BLACK);
                        DrawText("Q", x + cellSize/2 - 6, py + cellSize/2 - 10, cellSize/2, WHITE);
                    } 
                    else {
                        char s[2] = {board.getRegionAt(r, c), '\0'};
                        DrawText(s, x + 5, py + 5, cellSize/3, Fade(BLACK, 0.2f));
                    }
                }
            }
        } 
        else {
            DrawText("Please Load an Input File", PANEL_WIDTH + 200, 350, 30, LIGHTGRAY);
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}