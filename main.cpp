#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h> // Для system("cls")
#include "ant.h"
#include "anthill.h"
#include "enemy.h"

using namespace std;

void clearScreen() {
    system("cls");
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    // Создаем муравейник
    Anthill hill(10, 10, 200);
    cout << "The anthill has been created: 10 ants, 200 food reserves.\n" << endl;

    // Основной игровой цикл
    for (int day = 1; day <= 30; ++day) {
        clearScreen();
        cout << "=== Day " << day << " ===" << endl;

        // Логика симуляции
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
            cout << "The ants brought food: " << food << ", branches: " << branches << endl;
        }

        if (day % 5 == 0) {
            int born = rand() % 5 + 1;
            hill.newAnts(born);
            cout << born << " new ants were born in the anthill" << endl;
        }

        if (day % 7 == 0) {
            Enemy enemy(rand() % 100 + 30);
            enemy.attack(hill);
        }

        if (day % 4 == 0) {
            cout << "There was not enough food - the health of the ants is decreasing!" << endl;
            hill.emptyfood();
        }

        if (day % 10 == 0) {
            cout << "The anthill crumbles - the size and capacity decrease." << endl;
            hill.lowbranch();
        }

        cout << "\npress Enter to continue...";
        cin.ignore();
    }

    clearScreen();
    cout << "The final state of the anthill: " << endl;
    hill.showAllAnts();

    return 0;
}