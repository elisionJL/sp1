#include "Minion.h"

Minion::Minion()
{
}

string Minion::getMoveName(int MoveNo)
{
    switch(MoveNo)
    {
    case 1:
        return "Attack";
    case 2:
        return "Defend";
    case 3:
        return "Heal";
    default:
        return "Nothing";
    }
}

double Minion::getMovePower(int MoveNo)
{
    switch (MoveNo)
    {
    case 1:
        return 20;
    case 2:
        return 25;
    case 3:
        return 0;
    default:
        return 0;
    }
}

Minion::~Minion()
{
}
