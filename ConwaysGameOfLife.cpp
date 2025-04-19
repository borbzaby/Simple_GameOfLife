#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <sstream> // for splitting the string
using namespace std;

void DisplayScreen(const vector<vector<string>>& ArrayToPrint);
int CountNeighbours(int y, int x, const vector<vector<int>>& Matrix);

signed main() {
    int sw, sh; // screen width and height
    cout << "Give width of screen:" << endl; cin >> sw;
    cout << "Give height of screen:" << endl; cin >> sh; // get screen width and height

    cout << "\033[2J\033[1;1H"; // clear screen

    vector<vector<int>> CalculateMatrix(sh, vector<int>(sw, 0)); // stores current state
    vector<vector<string>> ScreenMatrix(sh, vector<string>(sw, "*"));

    int inp_x, inp_y; // for inputting coords
    string input = "";

    //get starting coords
    while (true) {
        cout << "\033[2J\033[1;1H";
        cout << "Input coords. no spaces: ";
        cin >> input;
        if (input == "done") break;
        
        stringstream ss(input);
        string item;
        
        getline(ss, item, ','); // Extract first part
        inp_x = stoi(item);
        getline(ss, item, ','); // Extract second part
        inp_y = stoi(item);
        
        CalculateMatrix[inp_y][inp_x] = 1;
        ScreenMatrix[inp_y][inp_x] = "O";
    }

    // CORE SIM LOOP
    while (true) {
        DisplayScreen(ScreenMatrix); // display screen
        this_thread::sleep_for(chrono::milliseconds(500)); // wait for 0.5s

        vector<vector<int>> NextMatrix(sh, vector<int>(sw, 0));
        for (int i = 0; i < sh; i++) {
            for (int j = 0; j < sw; j++) {
                int neighbours = CountNeighbours(i, j, CalculateMatrix);
                if (CalculateMatrix[i][j] == 1 && (neighbours == 2 || neighbours == 3)) {
                    NextMatrix[i][j] = 1;
                } else if (CalculateMatrix[i][j] == 0 && neighbours == 3) {
                    NextMatrix[i][j] = 1;
                }
            }
        }

        CalculateMatrix = NextMatrix;

        // Screenmatrix is readable calculatematrix
        for (int i = 0; i < sh; i++) {
            for (int j = 0; j < sw; j++) {
                if (CalculateMatrix[i][j] == 1) {
                    ScreenMatrix[i][j] = "O";
                } else {
                    ScreenMatrix[i][j] = "*";
                }
            }
        }
        
        
        cout << "\033[2J\033[1;1H"; // clear screen
    }
}

//yo yo swanky baaaaaby on da mic

void DisplayScreen(const vector<vector<string>>& ArrayToPrint) {
    for (int i = 0; i < ArrayToPrint.size(); i++) {
        for (int j = 0; j < ArrayToPrint[i].size(); j++) {
            cout << ArrayToPrint[i][j];
        }
        cout << endl;
    }
}


int CountNeighbours(int y, int x, const vector<vector<int>>& Matrix) {
    int count = 0;
    int rows = Matrix.size();
    int cols = Matrix[0].size();
    
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue; // Skip middle / the self one
            int new_y = y + i, new_x = x + j;
            if (new_y >= 0 && new_y < rows && new_x >= 0 && new_x < cols) { //in range?
                count += Matrix[new_y][new_x];
            }
        }
    }
    return count;
}
