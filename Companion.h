#pragma once
#include "Entity.h"
#include <string>
class Companion : public Entity
{
private:
    float MovePower;
    int companionId;
    std::string name;
    int lvl;
    double upgradecost;

public:
    Companion();
    Companion(int companionId,std::string x);
    void setMovePower(float pwr);
    ~Companion();
    string getMoveName(int MoveNo);
    double getMovePower(int MoveNo);
    std::string getname();
    void summonedagain();
    void lvlup();
    int getlvl();
    double getupgradecost();
    int getid();
};

