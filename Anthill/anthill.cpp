#include <cmath>
#include "anthill.h"

//Anthill::Anthill(int size_, int ant_, int food_): 
//    size_of_anthill(size_), count_of_ants(ant_), 
//    count_of_food(food_), branch(0),
//    maxAnts(1000), maxFood(1000)
//{
//    createAnt(ants, count_of_ants);
//}

Anthill::Anthill():size_of_anthill(1), 
branch(size_of_anthill*100), maxAnts(std::pow(2, size_of_anthill)), 
count_of_ants(maxAnts/2), maxFood(maxAnts*125), 
count_of_food(50)
{
    createAnt(ants, count_of_ants);
}

Anthill::~Anthill()
{
    for (auto a : ants) delete a;
}

void Anthill::createAnt(std::vector<Ant*>& ants_, int k_)
{
    for (int i = 0; i < k_; i++) {
        Ant* temp = new Ant();
        ants_.push_back(temp);
    }
}

void Anthill::newFood(int f_)
{
    count_of_food += f_;
    if (count_of_food < 0) count_of_food = 0;
    if (count_of_food > maxFood) count_of_food = maxFood;
}

void Anthill::newBranches(int b_)
{
    if (b_ >= 10) {
        size_of_anthill += b_ / 10;
        maxAnts += b_ / 4;
    }
}

void Anthill::newAnts(int k_)
{
    if (count_of_ants < maxAnts) {
        int toCreate = std::min(k_, maxAnts - count_of_ants);
        createAnt(ants, toCreate);
        count_of_ants += toCreate;
    }
}

void Anthill::emptyfood()
{
    for (size_t i = 0; i < ants.size(); ++i) {
        ants[i]->setHealth(ants[i]->getHealth() - 15);
        if (ants[i]->getHealth() <= 0) {
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
    if (count_of_ants > maxAnts) {
        for (size_t i = maxAnts; i < ants.size(); ++i) {
            delete ants[i];
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

Ant* Anthill::getAnt(int i) {
    return ants[i];
}

std::vector<Ant*>& Anthill::getAllAnts() {
    return ants;
}