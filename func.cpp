#include "func.h"
#include <iostream>
using namespace std;

Role::Role(string cur_role): current_role(cur_role){}
Norole::Norole(): Role("Norole"){}
Nanny::Nanny(): Role("Nanny"){}
Soldier::Soldier(): Role("Soldier"){}
Pastuh::Pastuh(): Role("Pastuh"){}
Builder::Builder(): Role("Builder"){}
Gatherer::Gatherer(): Role("Gatherer"){}
Cleaner::Cleaner(): Role("Cleaner"){}
Ant::Ant(): health(100), age(0), role(make_unique<Norole>()){}

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

void Gatherer::work() const
{
    cout<<"Current role is a Gatherer."<<endl;
}

void Cleaner::work() const
{
    cout<<"Current role is a Cleaner."<<endl;
}

void Ant::change_role()
{
    if (age<10)
    {
        role=make_unique<Norole>();
    }
    else if (age<18)
    {
        role=make_unique<Nanny>();
    }
    else if (age<30)
    {
        if (health>=50)
        {
            role=make_unique<Soldier>();
        }
        else
        {
            role=make_unique<Pastuh>();
        }
    }
    else if (age<45)
    {
        if (health>=50)
        {
            role=make_unique<Gatherer>();
        }
        else
        {
            role=make_unique<Soldier>();
        }
    }
    else
    {
        role=make_unique<Cleaner>();
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
    cout<<"Age: "<<age<<", health: "<<health<<". ";
    role->work();
    cout<<endl;
}