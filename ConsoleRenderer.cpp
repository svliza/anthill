#include "ConsoleRenderer.h"
#include <iostream>

using namespace std;

void ConsoleRenderer::clearScreen() {
    cout << "\033[2J\033[1;1H"; 
}

void ConsoleRenderer::draw(const vector<vector<char>>& field, int day) {
    clearScreen();
    cout << "=== День " << day << " ===" << endl;
    for (const auto& row : field) {
        for (char cell : row)
            cout << cell;
        cout << '\n';
    }
}