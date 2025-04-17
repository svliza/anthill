#include "enemy.h"
#include "anthill.h"
using namespace std;
Enemy::Enemy(int str) : strength(str) {}

void Enemy::attack(Anthill& hill)
{
    cout << "\n!! The enemy has attacked the anthill!" << endl;
    hill.getSoldierInformer().notifyAll("Enemy!");

    bool soldier_found = false;
    for(int i = 0; i < hill.ants.size(); i++)
    {
        hill.ants[i]->notify("Enemy!");
        if (hill.ants[i]->health > 0 && hill.ants[i]->getRoleName() == "Soldier")
        {
            soldier_found = true;
            int result = rand() % 100;
            if (result < 40)
            {
                cout << "The soldier repelled the attack!" << endl;
            }
            else if (result < 70)
            {
                cout << "The soldier and the enemy both died." << endl;
                hill.death(i);
                i--;
            }
            else
            {
                cout << "The enemy has won, the anthill has lost its food!" << endl;
                hill.death(i);
                i--;
                hill.newFood(-30);
            }
            return;
        }
    }

    if (!soldier_found)
    {
        cout << "The soldier has not been found. The enemy took the food and killed one ant." << endl;
        auto& ants = hill.getAllAnts();
        if (!ants.empty())
        {
            ants[0]->setHealth(0);
            hill.newFood(-30);
        }
    }
}