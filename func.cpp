#include "func.h"
#include <iostream>
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

