#pragma once
#include "ant.h"
using namespace std;
class Anthill
{
private:
    int size_of_anthill;
    int branch;
    int count_of_ants;
    int maxAnts;
    int count_of_food;
    int maxFood;
    SoldierInformer soldierInformer;
    BuilderInformer builderInformer;
    NannyInformer nannyInformer;
    CleanerInformer cleanerInformer;
    PastuhInformer pastuhInformer;

public:
    vector<Ant*> ants;
    Anthill(int size, int ants, int food);
    ~Anthill();
    void createAnt(vector<Ant*>& a, int k);
    void newFood(int f);
    void newBranches(int b); 
    void newAnts(int k);
    void emptyfood(); // если еды не хватило на всех, вызывается эта функция
    void lowbranch();
    void showAllAnts() const;
    void controlLives(); // 
    void death(int i); // убивает муравья

    Ant* getAnt(int i);
    vector<Ant*>& getAllAnts();

    SoldierInformer& getSoldierInformer() { return soldierInformer; }
    BuilderInformer& getBuilderInformer() { return builderInformer; }
    NannyInformer& getNannyInformer() { return nannyInformer; }
    CleanerInformer& getCleanerInformer() { return cleanerInformer; }
    PastuhInformer& getPastuhInformer() { return pastuhInformer; }

};