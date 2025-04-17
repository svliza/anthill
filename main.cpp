#include <iostream> 
#include <cstdlib> 
#include <ctime> 
#include "func.h" 
using namespace std;
int main() 
{ 
    srand(time(nullptr));

Anthill hill(10, 10, 200);
cout << "Муравейник создан: 10 муравьёв, запас еды — 200.\n" << endl;

for (int day = 1; day <= 30; ++day)
{
    cout << "=== День " << day << " ===" << endl;

    // Муравьи стареют и работают
    for (int i = 0; i < hill.getAllAnts().size(); ++i) {
        Ant* ant = hill.getAnt(i);
        ant->change_age();
        ant->work();
    }

    // Раз в 3 дня — пополнение запасов
    if (day % 3 == 0) {
        int food = rand() % 50 + 20;
        int branches = rand() % 30 + 10;
        hill.newFood(food);
        hill.newBranches(branches);
        cout << "Муравьи принесли еду: " << food << ", веток: " << branches << endl;
    }

    // Раз в 5 дней — рождение новых муравьёв
    if (day % 5 == 0) {
        int born = rand() % 5 + 1;
        hill.newAnts(born);
        cout << "В муравейнике родилось " << born << " новых муравьёв." << endl;
    }

    // Раз в 7 дней — нападение врага
    if (day % 7 == 0) {
        Enemy enemy(rand() % 100 + 30);
        enemy.attack(hill);
    }

    // Раз в 4 дня — муравьи теряют здоровье от голода
    if (day % 4 == 0) {
        cout << "Еды не хватило — здоровье муравьёв снижается!" << endl;
        hill.emptyfood();
    }

    // Раз в 10 дней — муравейник стареет
    if (day % 10 == 0) {
        cout << "Муравейник осыпается — уменьшаются размер и вместимость." << endl;
        hill.lowbranch();
    }

    cout << endl;
}

cout << " Итоговое состояние муравейника: " << endl;
hill.showAllAnts();

return 0;
};
