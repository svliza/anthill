#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h> 
#include "ant.cpp"
#include "anthill.cpp"
#include "enemy.cpp"



using namespace std;

void antLife(Anthill& hill) {
    int day = 1;
    while(hill.ants.size() > 0 ) {
        if (day % (rand() % 5 + 1) == 0) {
            int food = rand() % 20 + 10;
            int branches = rand() % 20 + 10;
            hill.newFood(food);
            hill.newBranches(branches);
            cout << "Ants brought food: " << food << ", branches: " << branches << endl;
        }
    
        if (day % (rand() % 5 + 1) == 0) {
            int born = rand() % 5 + 1;
            hill.newAnts(born);
            cout << "The anthill was born " << born << " new ants." << endl;
        }
    
        if (day % (rand() % 5 + 1) == 0) {
            Enemy enemy(rand() % 100 + 30);
            enemy.attack(hill);
            if(hill.ants.size() == 0) {
                cout << "The end" << endl;
                break;
            }
        }
    
        if (day % (rand() % 5 + 1) == 0) {
            cout << "The anthill is peeling off - size and capacity are reduced." << endl;
            hill.lowbranch();
            if(hill.ants.size() == 0) {
                cout << "The end" << endl;
                break;
            }
        }
        if(day %10 == 0) {
            cout << "Day^: " << day << endl;
            hill.getAllAnts(hill.ants);
        }
        hill.controlLives(); //добавляет возраст, убивает старых, кормит оставшихся, если не хватило еды, то отнимает по 10 хп у голодных. Если не осталось муравьев, то все пизда
        if(hill.ants.size() == 0) {
            cout << "The end" << endl;
            break;
        }
        day+=1;
    }


}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));
    int size; 
    int antCount;
    int foodCount;
    cin >> size >> antCount >> foodCount;
    if(size <= 0 || antCount <= 0 || foodCount <= 0) {
        cout << "You lose" << endl;
    }
    
    Anthill hill(size, antCount, foodCount);
    antLife(hill);

    return 0;
}