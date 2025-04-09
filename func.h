#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Role
{
public:
    Role(string cur_role);
    virtual void work() const = 0;
    virtual string getRoleName() const;
    virtual ~Role() = default;
protected:
    string current_role;
};

class Norole : public Role
{
public:
    Norole();
    void work() const override;
};

class Nanny : public Role
{
public:
    Nanny();
    void work() const override;
};

class Soldier : public Role
{
public:
    Soldier();
    void work() const override;
};

class Pastuh : public Role
{
public:
    Pastuh();
    void work() const override;
};

class Builder : public Role
{
public:
    Builder();
    void work() const override;
};

class Cleaner : public Role
{
public:
    Cleaner();
    void work() const override;
};

class Ant
{
private:
    int age;
    Role* role;
    int health;

public:
    Ant();
    ~Ant();
    void change_role();
    void change_age();
    void change_health(int current_health);
    void work() const;
    void print() const;

    string getRoleName() const;
    int getHealth() const;
    void setHealth(int h);
};

class Anthill
{
private:
    int size_of_anthill;
    int branch;
    int count_of_ants;
    int maxAnts;
    int count_of_food;
    int maxFood;
    vector<Ant*> ants;

public:
    Anthill(int size, int ants, int food);
    ~Anthill();
    void createAnt(vector<Ant*>& a, int k);
    void newFood(int f);
    void newBranches(int b);
    void newAnts(int k);
    void emptyfood();
    void lowbranch();
    void showAllAnts() const;

    Ant* getAnt(int i);
    vector<Ant*>& getAllAnts();
};

class Enemy
{
private:
    int strength;

public:
    Enemy(int str = 50);
    void attack(Anthill& hill);
};
