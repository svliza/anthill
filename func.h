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
    Norole(string cur_role): Role(cur_role){}
    void work() const override
    {
        cout<<"There is no role at the moment."<<endl;
    }
};

class Nanny: public Role
{
    Nanny(string cur_role): Role(cur_role){}
    void work() const override
    {
        cout<<"Current role is a Nanny."<<endl;
    }
};

class Soldier: public Role
{
    Soldier(string cur_role): Role(cur_role){}
    void work() const override
    {
        cout<<"Current role is a Soldier."<<endl;
    }
};

class Pastuh: public Role
{
    Pastuh(string cur_role): Role(cur_role){}
    void work() const override
    {
        cout<<"Current role is a Pastuh."<<endl;
    }
};

class Builder: public Role
{
    Builder(string cur_role): Role(cur_role){}
    void work() const override
    {
        cout<<"Current role is a Builder."<<endl;
    }
};

class Cleaner: public Role
{
    Cleaner(string cur_role): Role(cur_role){}
    void work() const override
    {
        cout<<"Current role is a Cleaner."<<endl;
    }
};


class Ant
{
public:
    int health;
    int age;
    Ant(): health(100), age(0){}
};