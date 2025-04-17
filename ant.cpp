#include "ant.h"
#include <algorithm>

using namespace std;

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
void CleanerInformer::subscribe(IObserver* observer_) {
    observers.push_back(observer_);
}

void CleanerInformer::unsubscribe(IObserver* observer_) {
    observers.erase(remove(observers.begin(), observers.end(), observer_), observers.end());
}

void CleanerInformer::notifyAll(const string& message_) {
    for (auto* observer : observers) {
        observer->notify(message_);
    }
}

void PastuhInformer::subscribe(IObserver* observer_) {
    observers.push_back(observer_);
}

void PastuhInformer::unsubscribe(IObserver* observer_) {
    observers.erase(remove(observers.begin(), observers.end(), observer_), observers.end());
}

void PastuhInformer::notifyAll(const string& message_) {
    for (auto* observer : observers) {
        observer->notify(message_);
    }
}





Role::Role(string cur_role) : current_role(cur_role) {}
string Role::getRoleName() const { return current_role; }

Norole::Norole() : Role("Norole") {}
void Norole::work() const { cout << "Current role is a Norole." << endl; }
void Norole::notify(const string& message_) {}

Nanny::Nanny() : Role("Nanny") {}
void Nanny::work() const { cout << "Current role is a Nanny." << endl; }
void Nanny::notify(const string& message_)
{
    if (message_ == "Enemy!")
    {
        cout << "Nanny reports: Everyone who is not in combat, guard Norole!" << endl;
    }
}
Soldier::Soldier() : Role("Soldier") {}
void Soldier::work() const { cout << "Current role is a Soldier." << endl; }
void Soldier::notify(const string& message_)
{
    if (message_ == "Enemy!")
    {
        cout << "Soldier says: Get ready for battle!" << endl;
    }
}

Pastuh::Pastuh() : Role("Pastuh") {}
void Pastuh::work() const { cout << "Current role is a Pastuh." << endl; }
void Pastuh::notify(const string& message_)
{
    if (message_ == "NewAnts!")
    {
        cout << "Pastuh reports: Watch out for new ants!" << endl;
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
        cout << "Cleaner informs you: You need to clean up after eating!" << endl;
    }
}


Ant::Ant(SoldierInformer& sInformer, BuilderInformer& bInformer, NannyInformer& nInformer, CleanerInformer& cInformer, PastuhInformer& pInformer)
    : age(0), role(new Norole()), health(100), soldierInformer(sInformer), builderInformer(bInformer), nannyInformer(nInformer), cleanerInformer(cInformer), pastuhInformer(pInformer) {
}
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

void Ant::notify(const string& message_) {
    cout << "Ant (" << getRoleName() << ") received the message: " << message_ << endl;
    if (message_ == "Enemy!") {
        if (getRoleName() == "Soldier") {
            cout << "The soldier rushes into battle!" << endl;
        }
    }
    else if (message_ == "Food!") {
        if (getRoleName() == "Cleaner") {
            cout << "Cleaner starts cleaning!" << endl;
        }
    }
    else if (message_ == "NewAnts!") {
        if (getRoleName() == "Pastuh") {
            cout << "Pastuh is watching out for new ants!" << endl;
        }
    }
}