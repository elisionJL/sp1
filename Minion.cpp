#include "Minion.h"
Minion::Minion(int x,std::string y)
{
    setHealth(((rand() % 50) + 50.0) * (x * 0.05+1));
    setDamage(((rand() % 15) + 15.0) * (x * 0.05+1));
    setResistance(((rand() % 15) + 15.0) * (x * 0.05+1));
    setSpeed(((rand() % 20) + 20.0) * (x * 0.05+1));
    setcurrentHealth(getHealth());
    setcurrentDamage(getDamage());
    setcurrentResistance(getResistance());
    setcurrentSpeed(getSpeed());
    setname(y);
    setskillcd(0);
    setatktarget("0");
}
Minion::~Minion()
{
}
string Minion::getMoveName(int MoveNo)
{
	switch (MoveNo)
	{
	case 1:
		return "Attack Boost";
	case 2:
		return "Defence Boost";
    case 3:
        return "Speed Boost";
	case 4:
        return "Heal";
	default:
		return "error";
	}
}
int Minion::skill(int x)
{
    switch (x)
    {
    case 1:
        setcurrentDamage(getDamage() * 1.5);
        return 0;
    case 2:
        setcurrentResistance(getResistance() * 1.5);
        return 0;
    case 3:
        setcurrentSpeed(getSpeed() * 1.5);
        return 0;
    case 4:
        setcurrentHealth(getcurrentHealth() + getHealth() * 0.15);
        if (getcurrentHealth() > getHealth())
            setcurrentHealth(getHealth());
        return 0;
    default:
        return 0;
    }
}