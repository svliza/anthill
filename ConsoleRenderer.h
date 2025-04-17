#pragma once
#include <vector>

class ConsoleRenderer {
public:
    void draw(const std::vector<std::vector<char>>& field, int day);
    void clearScreen();
};