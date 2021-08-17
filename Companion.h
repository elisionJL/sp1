#pragma once
#include "Entity.h"
#include <string>
class Companion :
    public Entity
{
private:
    std::string type;
    int companionId;
public:
    Companion();
    Companion(int companionId);
    int getStat();
    int getType();
    ~Companion();
    string getMoveName(int MoveNo);
    float getMovePower(int MoveNo);

};

