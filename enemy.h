#ifndef ENEMY_H
#define ENEMY_H
#include "anthill.h"
using namespace std;

class Enemy 
{
private:
    int strength;

public:
    Enemy(int str = 50);
    void attack(Anthill& hill);
};
#endif