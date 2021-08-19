#pragma once
#include "Entity.h"
#include <string>
class Companion : public Entity
{
private:
    float MovePower;
    int companionId;
    int lvl;
    double upgradecost;
    int timespulled;
    double bonusHealth;
    double bonusDamage;
    double bonusResistance;
    double bonusSpeed;
    double bonushealing;

public:
    Companion();
    Companion(int companionId,std::string x);
    ~Companion();
    string getMoveName(int x);
    int buff();
    void summonedagain();
    void lvlup();
    int getlvl();
    double getupgradecost();
    int getid();
    int gettimespulled();
    int skill();
    void resonance(int x);
    void removeresonace(int x);
};

