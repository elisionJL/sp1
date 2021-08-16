#pragma once
#include "Companion.h"
class Avocado :
    public Companion
{
public:
    Avocado();
    string getMoveName(int moveN);
    int getMovePower(int MoveNo);
    ~Avocado();
private:
};
