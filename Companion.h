#pragma once
#include "Entity.h"
#include <string>
class Companion :
    public Entity
{
private:
    float MovePower;
    int companionId;
public:
    Companion();
    Companion(int companionId);
    void setMovePower(float pwr);
    ~Companion();
    string getMoveName(int MoveNo);
    double getMovePower(int MoveNo);

};

