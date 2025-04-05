#include "func.h"
#include <iostream>
#include <vector>
using namespace std;

Role::Role(string cur_role): current_role(cur_role){}
Norole::Norole(): Role("Norole"){}
Nanny::Nanny(): Role("Nanny"){}
Soldier::Soldier(): Role("Soldier"){}
Pastuh::Pastuh(): Role("Pastuh"){}
Builder::Builder(): Role("Builder"){}
Cleaner::Cleaner(): Role("Cleaner"){}
Ant::Ant(): health(100), age(0), Norole(){}

void Norole::work() const
{
    cout<<"There is no role at the moment."<<endl;
}

void Nanny::work() const
{
    cout<<"Current role is a Nanny."<<endl;
}

void Soldier::work() const
{
    cout<<"Current role is a Soldier."<<endl;
}

void Pastuh::work() const
{
    cout<<"Current role is a Pastuh."<<endl;
}

void Builder::work() const
{
    cout<<"Current role is a Builder."<<endl;
}

void Cleaner::work() const
{
    cout<<"Current role is a Cleaner."<<endl;
}

void Ant::change_role()
{
    if (age<10)
    {
        Norole();
    }
    else if (age<18)
    {
        Nanny();
    }
    else if (age<30)
    {
        if (health>=50)
        {
            Soldier();
        }
        else
        {
            Pastuh();
        }
    }
    else if (age<45)
    {
        Builder();
    }
    else
    {
        Cleaner();
    }
}

void Ant::change_age()
{
    age+=1;
    change_role();
}

void Ant::change_health(int current_health)
{
    health=current_health;
    change_role();
}

void Ant::print() const
{

    cout<<"Age: "<<age<<", health: "<<health<<endl;
}

Anthill::Anthill(int size, int cant, int food): size_of_anthill(size), count_of_ants(cant), count_of_food(food), branch(0),
maxAnts(1000), maxFood(1000)
{
    createAnt(ants, count_of_ants);
}

void Anthill::createAnt(vector<Ant *> &a, int k)
{
    for(int i = 0; i < k; i++) {
        Ant* temp = new Ant();
        a.push_back(temp);
    }
}


void Anthill::newFood(int f)
{
    if(count_of_food < maxFood) {
        if(count_of_food + f <= maxFood) count_of_food+=f;
        else count_of_food = maxFood;
    }
}

void Anthill::newBranches(int b)
{
    if(b >= 10) {
        size_of_anthill+= b/10;
        maxAnts+=b/4;
    }

}

void Anthill::newAnts(int k)
{
    if(count_of_ants < maxAnts) {
       if(count_of_ants+k <= maxAnts) {
            count_of_ants+=k;
            createAnt(ants, k);
       }
       else {
        createAnt(ants, maxAnts-count_of_ants);
        count_of_ants = maxAnts; 
       }
    }
}

void Anthill::emptyfood()
{
    for(int i = 0; i < count_of_ants;i++) {
        ants[i]->health -=15;
        if(ants[i]->health <=0) {
            ants.erase(ants.begin() + i);
            i--;
        }
    }
}

void Anthill::lowbranch()
{
    size_of_anthill*=0.95;
    maxAnts*=0.95;
    if(count_of_ants > maxAnts) {
        count_of_ants = maxAnts;
        ants.resize(maxAnts);
    }
}

