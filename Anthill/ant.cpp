#include "ant.h"
#include <iostream>

Role::Role(std::string current_role_) :current_role(current_role_) {

}

std::string Role::getRoleName() const {
	return current_role;
}

Norole::Norole() : Role("Norole") {

}

void Norole::work() const { 
	std::cout << "There is no role at the moment." << std::endl; 
}

Nanny::Nanny() : Role("Nanny") {

}
void Nanny::work() const { 
	std::cout << "Current role is a Nanny." << std::endl; 
}

Soldier::Soldier() : Role("Soldier") {

}

void Soldier::work() const { 
	std::cout << "Current role is a Soldier." << std::endl; 
}

Pastuh::Pastuh() : Role("Pastuh") {

}

void Pastuh::work() const { std::cout << "Current role is a Pastuh." << std::endl; 

}

Builder::Builder() : Role("Builder") {

}

void Builder::work() const { 
	std::cout << "Current role is a Builder." << std::endl; 
}

Cleaner::Cleaner() : Role("Cleaner") {

}

void Cleaner::work() const { 
	std::cout << "Current role is a Cleaner." << std::endl; 
}

Ant::Ant() : age(0), role(new Norole()), health(100) {

}
Ant::~Ant() { 
    delete role; 
}

void Ant::change_role()
{
    delete role;
    if (age < 10) {
        role = new Norole();
    }
    else
        if (age < 18) {
            role = new Nanny;
        }
        else
            if (age < 30) {
                if (health >= 50) {
                    role = new Soldier;
                }
                else {
                    role = new Pastuh;
                }
            }
            else
                if (age < 45) {
                    role = new Builder();
                }
                else {
                    role = new Cleaner;
                }
}

void Ant::change_age()
{
    age += 1;
    change_role();
}

void Ant::change_health(int current_health_)
{
    health = current_health_;
    change_role();
}

void Ant::work() const
{
    role->work();
}

void Ant::print() const
{
    std::cout << "Age: " << age << ", Health: " << health << ", Role: " << role->getRoleName() << std::endl;
}

std::string Ant::getRoleName() const {
    return role->getRoleName();
}

int Ant::getHealth() const {
    return health;
}

void Ant::setHealth(int h_) {
    health = h_;
}