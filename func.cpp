#include "func.h"
#include <iostream>
#include <algorithm>
#include <memory>
using namespace std;

Role::Role(string cur_role) : current_role(cur_role) {}
string Role::getRoleName() const { return current_role; }

Norole::Norole() : Role("Norole") {}
void Norole::work() const { cout << "There is no role at the moment." << endl; }
void Norole::notify(const string& message_) 
{
    if (message_ == "Food!") 
    {
        cout << "Norole сообщает: Нужно собирать еду!" << endl;
    }
}

Nanny::Nanny() : Role("Nanny") {}
void Nanny::work() const { cout << "Current role is a Nanny." << endl; }
void Nanny::notify(const string& message_) 
{
    if (message_ == "Enemy!") 
    {
        cout << "Nanny сообщает: Все, кто не в бою, охраняйте Norole!" << endl;
    }
}

Soldier::Soldier() : Role("Soldier") {}
void Soldier::work() const { cout << "Current role is a Soldier." << endl; }
void Soldier::notify(const string& message_) 
{
    if (message_ == "Enemy!") 
    {
        cout << "Soldier сообщает: Готовьтесь к бою!" << endl;
    }
}

Pastuh::Pastuh() : Role("Pastuh") {}
void Pastuh::work() const { cout << "Current role is a Pastuh." << endl; }
void Pastuh::notify(const string& message_) 
{
    if (message_ == "NewAnts!") 
    {
        cout << "Pastuh сообщает: Следите за новыми муравьями!" << endl;
    }
}

Builder::Builder() : Role("Builder") {}
void Builder::work() const { cout << "Current role is a Builder." << endl; }
void Builder::notify(const string& message_) 
{
    if (message_ == "Branches!") 
    {
        cout << "Builder сообщает: Подъехали стройматериалы!" << endl;
    }
}


Cleaner::Cleaner() : Role("Cleaner") {}
void Cleaner::work() const { cout << "Current role is a Cleaner." << endl; }
void Cleaner::notify(const string& message_) 
{
    if (message_ == "Food!") 
    {
        cout << "Cleaner сообщает: Нужно убрать после еды!" << endl;
    }
}


Ant::Ant(SoldierInformer& informer, BuilderInformer& bInformer, NannyInformer& nInformer)
    : age(0), role(new Norole()), health(100), soldierInformer(informer), builderInformer(bInformer), nannyInformer(nInformer) {}

Ant::~Ant() { delete role; }

void Ant::change_role() {
    if (role->getRoleName() == "Soldier") 
    {
        soldierInformer.unsubscribe(this);
    } 
    else if (role->getRoleName() == "Builder") 
    {
        builderInformer.unsubscribe(this);
    } 
    else if (role->getRoleName() == "Nanny") 
    {
        nannyInformer.unsubscribe(this);
    }

    delete role;

    if (age < 10) 
    {
        role = new Norole();
    } 
    else if (age < 18) 
    {
        role = new Nanny();
        nannyInformer.subscribe(this);
    } 
    else if (age < 30) 
    {
        if (health >= 50) 
        {
            role = new Soldier();
            soldierInformer.subscribe(this);
        } 
        else 
        {
            role = new Pastuh();
        }
    } 
    else if (age < 45) 
    {
        role = new Builder();
        builderInformer.subscribe(this);
    } 
    else 
    {
        role = new Cleaner();
    }
}

void Ant::change_age() 
{
    age += 1;
    change_role();
}

void Ant::change_health(int current_health) 
{
    health = current_health;
    change_role();
}

void Ant::work() const 
{
    role->work();
}

void Ant::print() const 
{
    cout << "Age: " << age << ", Health: " << health << ", Role: " << role->getRoleName() << endl;
}

string Ant::getRoleName() const 
{
    return role->getRoleName();
}

int Ant::getHealth() const 
{
    return health;
}

void Ant::setHealth(int h) 
{
    health = h;
}

void Ant::notify(const string& message_) 
{
    cout << "Ant (" << getRoleName() << ") получил сообщение: " << message_ << endl;
    if (message_ == "Enemy!")
    {
        if (getRoleName() == "Soldier") 
        {
            cout << "A soldier rushes into action!" << endl;
        }
    }
}

void SoldierInformer::subscribe(IObserver* observer_) 
{
    observers.push_back(observer_);
}

void SoldierInformer::unsubscribe(IObserver* observer_) 
{
    observers.erase(remove(observers.begin(), observers.end(), observer_), observers.end());
}

void SoldierInformer::notifyAll(const string& message_) 
{
    for (auto* observer : observers) 
    {
        observer->notify(message_);
    }
}


void BuilderInformer::subscribe(IObserver* observer_) 
{
    observers.push_back(observer_);
}

void BuilderInformer::unsubscribe(IObserver* observer_) 
{
    observers.erase(remove(observers.begin(), observers.end(), observer_), observers.end());
}

void BuilderInformer::notifyAll(const string& message_) 
{
    for (auto* observer : observers) 
    {
        observer->notify(message_);
    }
}


void NannyInformer::subscribe(IObserver* observer_) 
{
    observers.push_back(observer_);
}

void NannyInformer::unsubscribe(IObserver* observer_) 
{
    observers.erase(remove(observers.begin(), observers.end(), observer_), observers.end());
}

void NannyInformer::notifyAll(const string& message_) 
{
    for (auto* observer : observers) 
    {
        observer->notify(message_);
    }
}

Anthill::Anthill(int size, int cant, int food)
    : size_of_anthill(size), count_of_ants(cant), count_of_food(food), branch(0),
      maxAnts(1000), maxFood(1000), soldierInformer(), builderInformer(), nannyInformer() 
      {
    createAnt(ants, count_of_ants);
}

Anthill::~Anthill() 
{
    for (auto a : ants) delete a;
}

void Anthill::createAnt(vector<Ant*>& a, int k) 
{
    for (int i = 0; i < k; i++) 
    {
        Ant* temp = new Ant(soldierInformer, builderInformer, nannyInformer);
        a.push_back(temp);
    }
}

void Anthill::newFood(int f) 
{
    count_of_food += f;
    if (count_of_food < 0) count_of_food = 0;
    if (count_of_food > maxFood) count_of_food = maxFood;
}

void Anthill::newBranches(int b) 
{
    if (b >= 10) 
    {
        size_of_anthill += b / 10;
        maxAnts += b / 4;
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

void Anthill::emptyfood() 
{
    for (size_t i = 0; i < ants.size(); ++i) 
    {
        ants[i]->setHealth(ants[i]->getHealth() - 15);
        if (ants[i]->getHealth() <= 0) 
        {
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
    if (count_of_ants > maxAnts) 
    {
        for (size_t i = maxAnts; i < ants.size(); ++i) 
        {
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

Ant* Anthill::getAnt(int i) 
{
    return ants[i];
}

vector<Ant*>& Anthill::getAllAnts() 
{
    return ants;
}


Enemy::Enemy(int str) : strength(str) {}

void Enemy::attack(Anthill& hill) 
{
    cout << "\n⚠️ Враг напал на муравейник!" << endl;
    hill.getSoldierInformer().notifyAll("Enemy!"); 

    bool soldier_found = false;
    for (auto ant : hill.getAllAnts()) 
    {
        ant->notify("Enemy!");
        if (ant->getHealth() > 0 && ant->getRoleName() == "Soldier") 
        {
            soldier_found = true;
            int result = rand() % 100;
            if (result < 40) 
            {
                cout << "Солдат отразил нападение!" << endl;
            } 
            else if (result < 70) 
            {
                cout << "Солдат и враг оба погибли." << endl;
                ant->setHealth(0);
            } 
            else 
            {
                cout << "Враг победил, муравейник потерял еду!" << endl;
                hill.newFood(-30);
            }
            return;
        }
    }

    if (!soldier_found) 
    {
        cout << "Солдат не найден. Враг забрал еду и убил одного муравья." << endl;
        auto& ants = hill.getAllAnts();
        if (!ants.empty()) 
        {
            ants[0]->setHealth(0);
            hill.newFood(-30);
        }
    }
}