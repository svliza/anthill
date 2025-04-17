#include "anthill.h"
#include <vector>
Anthill::Anthill(int size, int cant, int food)
    : size_of_anthill(size), count_of_ants(cant), count_of_food(food), branch(0),
    maxAnts(1000), maxFood(1000), soldierInformer(), builderInformer(), nannyInformer(), cleanerInformer(), pastuhInformer() {
    createAnt(ants, count_of_ants);
}


Anthill::~Anthill()
{
    for (auto a : ants) delete a;
}

void Anthill::createAnt(vector<Ant*>& a, int k) {
    for (int i = 0; i < k; i++) {
        Ant* temp = new Ant(soldierInformer, builderInformer, nannyInformer, cleanerInformer, pastuhInformer);
        a.push_back(temp);
    }
}

void Anthill::newFood(int f)
{
    count_of_food += f;
    if (count_of_food < 0) count_of_food = 0;
    if (count_of_food > maxFood) count_of_food = maxFood;
}

void Anthill::newBranches(int b)
{
    if (b >= 10)
    {
        size_of_anthill += b / 10;
        maxAnts += b / 4;
    }
}

void Anthill::newAnts(int k)
{
    if (count_of_ants < maxAnts)
    {
        int toCreate = min(k, maxAnts - count_of_ants);
        createAnt(ants, toCreate);
        count_of_ants += toCreate;
    }
}

void Anthill::emptyfood()
{
    for (size_t i = 0; i < ants.size(); ++i)
    {
        ants[i]->setHealth(ants[i]->getHealth() - 15);
        if (ants[i]->getHealth() <= 0)
        {
            delete ants[i];
            ants.erase(ants.begin() + i);
            i--;
            count_of_ants--;
        }
    }
}

void Anthill::lowbranch()
{
    size_of_anthill *= 0.95;
    maxAnts *= 0.95;
    if (count_of_ants > maxAnts)
    {
        for (size_t i = maxAnts; i < ants.size(); ++i)
        {
            death(i);
            i--;
        }
        ants.resize(maxAnts);
        count_of_ants = maxAnts;
    }
}

void Anthill::showAllAnts() const
{
    for (const auto& a : ants)
        a->print();
}

void Anthill::controlLives()
{

    for(int i = 0; i < ants.size(); i++) {
        ++ants[i]->age;
        if(ants[i]->age > 10) {
            death(i);
            i--;
        }
    }
}

void Anthill::death(int i)
{
    ants.erase(ants.begin() + i);
}

Ant* Anthill::getAnt(int i)
{
    return ants[i];
}

vector<Ant*>& Anthill::getAllAnts()
{
    return ants;
}
