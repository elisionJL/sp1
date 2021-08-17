#include "Minion.h"
Minion::Minion(int x)
{
    setHealth(((rand() % 50) + 50.0)*x*0.05);
    setDamage(((rand() % 15) + 15.0)* x * 0.05);
    setResistance(((rand() % 15) + 15.0)* x * 0.05);
    setSpeed(((rand() % 20) + 20.0)* x * 0.05);
}
Minion::~Minion()
{
}
string Minion::getMoveName(int MoveNo)
{
    switch (MoveNo)
    {
    case 1:
        return "Attack";
    case 2:
        return "Defend";
    case 3:
        return "Heal";
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
    }
}
