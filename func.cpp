#include "func.h"

Role::Role(string cur_role) : current_role(cur_role) {}
string Role::getRoleName() const { return current_role; }

Norole::Norole() : Role("Norole") {}
void Norole::work() const { cout << "There is no role at the moment." << endl; }

Nanny::Nanny() : Role("Nanny") {}
void Nanny::work() const { cout << "Current role is a Nanny." << endl; }

Soldier::Soldier() : Role("Soldier") {}
void Soldier::work() const { cout << "Current role is a Soldier." << endl; }

Pastuh::Pastuh() : Role("Pastuh") {}
void Pastuh::work() const { cout << "Current role is a Pastuh." << endl; }

Builder::Builder() : Role("Builder") {}
void Builder::work() const { cout << "Current role is a Builder." << endl; }

Cleaner::Cleaner() : Role("Cleaner") {}
void Cleaner::work() const { cout << "Current role is a Cleaner." << endl; }

Ant::Ant() : age(0), role(new Norole()), health(100) {}
Ant::~Ant() { delete role; }

void Ant::change_role()
{
    delete role;
    if (age < 10)
        role = new Norole();
    else if (age < 18)
        role = new Nanny();
    else if (age < 30)
        role = (health >= 50) ? static_cast<Role*>(new Soldier()) : static_cast<Role*>(new Pastuh());
    else if (age < 45)
        role = new Builder();
    else
        role = new Cleaner();
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

string Ant::getRoleName() const {
    return role->getRoleName();
}

int Ant::getHealth() const {
    return health;
}

void Ant::setHealth(int h) {
    health = h;
}

Anthill::Anthill(int size, int cant, int food)
    : size_of_anthill(size), count_of_ants(cant), count_of_food(food), branch(0),
      maxAnts(1000), maxFood(1000)
{
    createAnt(ants, count_of_ants);
}

Anthill::~Anthill()
{
    for (auto a : ants) delete a;
}

void Anthill::createAnt(vector<Ant*>& a, int k)
{
    for (int i = 0; i < k; i++) {
        Ant* temp = new Ant();
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
    if (b >= 10) {
        size_of_anthill += b / 10;
        maxAnts += b / 4;
    }
}

void Anthill::newAnts(int k)
{
    if (count_of_ants < maxAnts) {
        int toCreate = min(k, maxAnts - count_of_ants);
        createAnt(ants, toCreate);
        count_of_ants += toCreate;
    }
}

void Anthill::emptyfood()
{
    for (size_t i = 0; i < ants.size(); ++i) {
        ants[i]->setHealth(ants[i]->getHealth() - 15);
        if (ants[i]->getHealth() <= 0) {
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
    if (count_of_ants > maxAnts) {
        for (size_t i = maxAnts; i < ants.size(); ++i) {
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

Ant* Anthill::getAnt(int i) {
    return ants[i];
}

vector<Ant*>& Anthill::getAllAnts() {
    return ants;
}

Enemy::Enemy(int str) : strength(str) {}

void Enemy::attack(Anthill& hill)
{
    cout << "\n⚠️ Враг напал на муравейник!" << endl;

    bool soldier_found = false;
    for (auto ant : hill.getAllAnts())
    {
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
