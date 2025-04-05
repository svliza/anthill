#pragma once
#include <iostream>
#include <string>
using namespace std;

class Role
{
public:
    Role(string cur_role): current_role(cur_role) {}
    virtual void work() const=0;
private:
    string current_role;
};

class Norole: public Role
{
public:
    Norole(): Role("Norole"){}
    void work() const override
    {
        cout<<"There is no role at the moment."<<endl;
    }
};

class Nanny: public Role
{
public:
    Nanny(): Role("Nanny"){}
    void work() const override
    {
        cout<<"Current role is a Nanny."<<endl;
    }
};

class Soldier: public Role
{
public:
    Soldier(): Role("Soldier"){}
    void work() const override
    {
        cout<<"Current role is a Soldier."<<endl;
    }
};

class Pastuh: public Role
{
public:
    Pastuh(): Role("Pastuh"){}
    void work() const override
    {
        cout<<"Current role is a Pastuh."<<endl;
    }
};

class Builder: public Role
{
public:
    Builder(): Role("Builder"){}
    void work() const override
    {
        cout<<"Current role is a Builder."<<endl;
    }
};

class Cleaner: public Role
{
public:
    Cleaner(): Role("Cleaner"){}
    void work() const override
    {
        cout<<"Current role is a Cleaner."<<endl;
    }
};


class Ant: public Norole, public Nanny, public Soldier, public Pastuh, public Builder, public Cleaner
{
private:
    int health;
    int age;
public:
    Ant(): health(100), age(0), Norole(){}

    void change_role()
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

    void change_age()
    {
        age+=1;
        change_role();
    }

    void change_health(int current_health)
    {
        health=current_health;
        change_role();
    }

    void print()
    {
        cout<<"Age: "<<age<<", health: "<<health<<endl;
    }
};