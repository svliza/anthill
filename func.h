#pragma once
#include <iostream>
#include <string>
#include <memory>
using namespace std;

class Role
{
public:
    Role(string cur_role);
    virtual void work() const=0;
    string GetRole() {return current_role;}
private:
    string current_role;
};

class Norole: public Role
{
public:
    Norole();
    void work() const override;
};

class Nanny: public Role
{
public:
    Nanny();
    void work() const override;
};

class Soldier: public Role
{
public:
    Soldier();
    void work() const override;
};

class Pastuh: public Role
{
public:
    Pastuh();
    void work() const override;
};

class Builder: public Role
{
public:
    Builder();
    void work() const override;
};

class Gatherer: public Role
{
public:
    Gatherer();
    void work() const override;
};

class Cleaner: public Role
{
public:
    Cleaner();
    void work() const override;
};


class Ant: public Norole, public Nanny, public Soldier, public Pastuh, public Builder, public Gatherer, public Cleaner
{
private:
    int health;
    int age;
    unique_ptr<Role>role;
public:
    Ant();
    void change_role();
    void change_age();
    void change_health(int current_health);
    void print() const;
};