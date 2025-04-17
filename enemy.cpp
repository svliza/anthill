#include "enemy.h"
#include "anthill.h"
using namespace std;
Enemy::Enemy(int str) : strength(str) {}

void Enemy::attack(Anthill& hill) 
{
    cout << "\n⚠️ Враг напал на муравейник!" << endl;
    hill.getSoldierInformer().notifyAll("Enemy!"); 

    bool soldier_found = false;
    for (auto ant : hill.getAllAnts()) 
    {
        ant->notify("Enemy!");
        if (ant->getHealth() > 0 && ant->getRoleName() == "Soldier") 
        {
            soldier_found = true;
            int result = rand() % 100;
            if (result < 40) 
            {
                cout << "Солдат отразил нападение!" << endl;
            } 
            else if (result < 70) 
            {
                cout << "Солдат и враг оба погибли." << endl;
                ant->setHealth(0);
            } 
            else 
            {
                cout << "Враг победил, муравейник потерял еду!" << endl;
                hill.newFood(-30);
            }
            return;
        }
    }

    if (!soldier_found) 
    {
        cout << "Солдат не найден. Враг забрал еду и убил одного муравья." << endl;
        auto& ants = hill.getAllAnts();
        if (!ants.empty()) 
        {
            ants[0]->setHealth(0);
            hill.newFood(-30);
        }
    }
}