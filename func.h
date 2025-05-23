#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

class IObserver 
{
public:
    virtual void notify(const string& message_) = 0;
};

class IInformer 
{
public:
    virtual void subscribe(IObserver* observer_) = 0;
    virtual void unsubscribe(IObserver* observer_) = 0;
    virtual void notifyAll(const string& message_) = 0;
};

class SoldierInformer : public IInformer 
{
private:
    vector<IObserver*> observers;
public:
    void subscribe(IObserver* observer_) override;
    void unsubscribe(IObserver* observer_) override;
    void notifyAll(const string& message_) override;
};

class BuilderInformer : public IInformer 
{
private:
    vector<IObserver*> observers;
public:
    void subscribe(IObserver* observer_) override;
    void unsubscribe(IObserver* observer_) override;
    void notifyAll(const string& message_) override;
};

class NannyInformer : public IInformer 
{
private:
    vector<IObserver*> observers;
public:
    void subscribe(IObserver* observer_) override;
    void unsubscribe(IObserver* observer_) override;
    void notifyAll(const string& message_) override;
};

class CleanerInformer : public IInformer 
{
private:
    vector<IObserver*> observers;
public:
    void subscribe(IObserver* observer_) override;
    void unsubscribe(IObserver* observer_) override;
    void notifyAll(const string& message_) override;
};

class PastuhInformer : public IInformer 
{
private:
    vector<IObserver*> observers;
public:
    void subscribe(IObserver* observer_) override;
    void unsubscribe(IObserver* observer_) override;
    void notifyAll(const string& message_) override;
};


class Role 
{
public:
    Role(string cur_role);
    virtual void work() const = 0; 
    virtual string getRoleName() const;
    virtual void notify(const string& message_) = 0; 
    virtual ~Role() = default;
protected:
    string current_role;
};


class Norole : public Role 
{
public:
    Norole();
    void work() const override;
    void notify(const string& message_) override;
};

class Nanny : public Role 
{
public:
    Nanny();
    void work() const override;
    void notify(const string& message_) override;
};

class Soldier : public Role 
{
public:
    Soldier();
    void work() const override;
    void notify(const string& message_) override;
};

class Pastuh : public Role 
{
public:
    Pastuh();
    void work() const override;
    void notify(const string& message_) override;
};

class Builder : public Role 
{
public:
    Builder();
    void work() const override;
    void notify(const string& message_) override;
};

class Cleaner : public Role 
{
public:
    Cleaner();
    void work() const override;
    void notify(const string& message_) override;
};


class Ant : public IObserver 
{
private:
    int age;
    Role* role;
    int health;
    SoldierInformer& soldierInformer; 
    BuilderInformer& builderInformer; 
    NannyInformer& nannyInformer;
    CleanerInformer& cleanerInformer; 
    PastuhInformer& pastuhInformer; 

public:
    Ant(SoldierInformer& sInformer, BuilderInformer& bInformer, NannyInformer& nInformer, CleanerInformer& cInformer, PastuhInformer& pInformer);
    ~Ant();
    void change_role();
    void change_age();
    void change_health(int current_health);
    void work() const;
    void print() const;

    string getRoleName() const;
    int getHealth() const;
    void setHealth(int h);

    void notify(const string& message_) override;
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
    SoldierInformer soldierInformer; 
    BuilderInformer builderInformer; 
    NannyInformer nannyInformer;
    CleanerInformer cleanerInformer; 
    PastuhInformer pastuhInformer; 

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
    SoldierInformer& getSoldierInformer() { return soldierInformer; } 
    BuilderInformer& getBuilderInformer() { return builderInformer; }
    NannyInformer& getNannyInformer() { return nannyInformer; }
    CleanerInformer& getCleanerInformer() { return cleanerInformer; }
    PastuhInformer& getPastuhInformer() { return pastuhInformer; }
    
};

class Enemy 
{
private:
    int strength;

public:
    Enemy(int str = 50);
    void attack(Anthill& hill);
};