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

public:
    Companion();
    Companion(int companionId,std::string x);
    void setMovePower(float pwr);
    ~Companion();
    string getMoveName(int MoveNo);
    double getMovePower(int MoveNo);
    void summonedagain();
    void lvlup();
    int getlvl();
    double getupgradecost();
    int getid();
    int gettimespulled();
};

