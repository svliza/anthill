#include "Life.h"
#include "ConsoleRenderer.h"
#include <iostream>
#include <cstdlib>

using namespace std;

const int WIDTH = 20;
const int HEIGHT = 10;

void placeRandom(std::vector<std::vector<char>>& field, char symbol, int count) {
    int placed = 0;
    while (placed < count) {
        int x = rand() % (WIDTH - 2) + 1;
        int y = rand() % (HEIGHT - 2) + 1;
        if (field[y][x] == ' ') {
            field[y][x] = symbol;
            placed++;
        }
    }
}

void Life::simulateDay(int day, Anthill& hill) {
    // Логика муравейника
    for (size_t i = 0; i < hill.getAllAnts().size(); ++i) {
        Ant* ant = hill.getAnt(static_cast<int>(i));
        ant->change_age();
        ant->work();
    }

    if (day % 3 == 0) {
        int food = rand() % 50 + 20;
        int branches = rand() % 30 + 10;
        hill.newFood(food);
        hill.newBranches(branches);
    }

    if (day % 5 == 0) {
        int born = rand() % 5 + 1;
        hill.newAnts(born);
    }

    if (day % 7 == 0) {
        Enemy enemy(rand() % 100 + 30);
        enemy.attack(hill);
    }

    if (day % 4 == 0) {
        hill.emptyfood();
    }

    if (day % 10 == 0) {
        hill.lowbranch();
    }

    // Создание поля и отрисовка
    vector<vector<char>> field(HEIGHT, vector<char>(WIDTH, ' '));
    for (int x = 0; x < WIDTH; ++x) {
        field[0][x] = '*';
        field[HEIGHT - 1][x] = '*';
    }
    for (int y = 0; y < HEIGHT; ++y) {
        field[y][0] = '*';
        field[y][WIDTH - 1] = '*';
    }

    field[HEIGHT / 2][WIDTH / 2] = 'H'; // Центр муравейника

    placeRandom(field, 'F', 5); // Еда
    placeRandom(field, 'B', 3); // Ветки
    placeRandom(field, 'E', (day % 7 == 0) ? 1 : 0); // Враги
    placeRandom(field, 'A', 4); // Муравьи

    ConsoleRenderer renderer;
    renderer.draw(field, day);
}