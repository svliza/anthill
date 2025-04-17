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
    void newFood(int f); // добавляет ебу в запасы
    void newBranches(int b); // эта ф-я вызывается когда принесли новые ветки, рассчет такой: каждые новые пять веток добавляют в местимость плюс 1 муравей и 1 значение еды 
    void newAnts(int k); // рождает новых муравьев в количестве к
    void emptyfood(int i); //вызывается если еды не хватило на всех, тогда эта ф-я отнимает 10 здоровья у всех, кому не хватило
    void lowbranch(); // ф-я вызывается если не принесли веток в течение опр колва дней, прописанного в life, уменьшает количество муравьев на 5 и размер муравейника на 5 и макс запас еды
    void showAllAnts() const;
    void controlLives(); // вызывается в конце дня, проверяет всем ли меньше 10 дней, кормит муравьев, кому не хватило еды вызывается empty food
    void death(int i); // убивает муравья

    Ant* getAnt(int i);
    void getAllAnts(vector<Ant*> antsinhill);

    SoldierInformer& getSoldierInformer() { return soldierInformer; }
    BuilderInformer& getBuilderInformer() { return builderInformer; }
    NannyInformer& getNannyInformer() { return nannyInformer; }
    CleanerInformer& getCleanerInformer() { return cleanerInformer; }
    PastuhInformer& getPastuhInformer() { return pastuhInformer; }

};