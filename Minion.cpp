#include "Minion.h"

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
    }
}

int Minion::getMovePower(int MoveNo)
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
