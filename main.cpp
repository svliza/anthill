#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include "ant.h"
#include "anthill.h"
#include "enemy.h"
#include "Life.h"

using namespace std;

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    Anthill hill(10, 10, 200);
    Life life;

    for (int day = 1; day <= 30; ++day) {
        life.simulateDay(day, hill);
        this_thread::sleep_for(chrono::milliseconds(1000));
    }

    cout << "\nИтоговое состояние муравейника:\n";
    hill.showAllAnts();

    return 0;
}