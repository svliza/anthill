#include "anthill.h"
#include <vector>
Anthill::Anthill(int size, int cant, int food)
    : size_of_anthill(size), count_of_ants(cant), count_of_food(food), branch(0),
    maxAnts(cant*2), maxFood(food*2), soldierInformer(), builderInformer(), nannyInformer(), cleanerInformer(), pastuhInformer() {
    createAnt(ants, count_of_ants);
}


Anthill::~Anthill()
{
    for (auto a : ants) delete a;
}

void Anthill::createAnt(vector<Ant*>& a, int k) {
    for (int i = 0; i < k; i++) {
        Ant* temp = new Ant(soldierInformer, builderInformer, nannyInformer, cleanerInformer, pastuhInformer);
        temp->maxAge = rand()%8 + 7;
        a.push_back(temp);
    }
}

void Anthill::newFood(int f)
{
    count_of_food += f;
    if (count_of_food > maxFood) count_of_food = maxFood;
}

void Anthill::newBranches(int b)
{
    if (b >= 5)
    {
        size_of_anthill += b / 5;
        maxAnts += b/5;
        maxFood+=b/5;
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

void Anthill::emptyfood(int i)
{
    for(int j = i; j < ants.size(); j++) {
        ants[j]->health-10;
        if(ants[j]->health <= 0) {
            death(j);
        }
    }   
}

void Anthill::lowbranch()
{
    size_of_anthill -=5;
    maxAnts -=5;
    if (count_of_ants > maxAnts && maxAnts >= 0)
    {
        for (size_t i = maxAnts; i < ants.size(); ++i)
        {
            death(i);
            i--;
        }
        ants.resize(maxAnts);
        count_of_ants = maxAnts;
    }
    if(maxAnts <=0) {
        ants.resize(0);
    }
    maxFood-=5;
    if(count_of_food > maxFood) count_of_food = maxFood;
}

void Anthill::showAllAnts() const
{
    for (const auto& a : ants)
        a->print();
}

void Anthill::controlLives()
{
    bool normal_count_of_food = 1; // изначально предполагается, что еды хватило всем, но потом.....
    for(int i = 0; i < ants.size(); i++) {
        ++ants[i]->age;
        ants[i]->change_role();
        if(ants[i]->age > ants[i]->maxAge) {
            death(i);
            i--;
            if(ants.size() == 0) {
                break;
            }
        }
        else {
            if(count_of_food >= 1){
                count_of_food-=1;
                if(ants[i]->health < 100) ants[i]->health = 100;
                if(count_of_food== 0 && i+1 <=ants.size()) {
                    emptyfood(i+1);
                }
            }
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

void Anthill::getAllAnts(vector<Ant*> antsinhill)
{

    for(int i = 0; i < antsinhill.size(); i++) {
        cout << "Role: " << antsinhill[i]->getRoleName()<< " " << "age: " << antsinhill[i]->age<< " " << "health: " << antsinhill[i]->health << endl;
    }
}
