#pragma once
#include "ant.h"
#include <vector>

class Anthill
{
private:
    int size_of_anthill;
    int branch;
    int count_of_ants;
    int maxAnts;
    int count_of_food;
    int maxFood;
    std::vector<Ant*> ants;
public:
    //Anthill(int size_, int ant_, int food_);
    Anthill();
    ~Anthill();

    void createAnt(std::vector<Ant*>& ants_, int k_);
    void newFood(int f_);
    void newBranches(int b_);
    void newAnts(int k_);
    void emptyfood();
    void lowbranch();
    void showAllAnts() const;

    Ant* getAnt(int i_);
    std::vector<Ant*>& getAllAnts();
};