#include "SpinachBoss.h"
#include <string>

SpinachBoss::SpinachBoss(int x)
{
	setHealth(100 * (x * 1.05));
	setDamage(30 * (x * 1.05));
	setResistance(30 * (x * 1.05));
	setSpeed(40 * (x * 1.05));
	setcurrentHealth(getHealth());
	setcurrentDamage(getDamage());
	setcurrentResistance(getResistance());
	setcurrentSpeed(getSpeed());
	setname("Spinach");
}

string SpinachBoss::getMoveName(int MoveNo)
{
	switch (MoveNo)
	{
	case 1:
		return "SPIN-ACH";
		//Basic damage ability
	case 2:
		return " Salty";
		//Decrease 1 of player's party member's attack
	case 3:
		return "Greens are good, increasing Defence";
		//increase resistance
	case 4:
		return "Popeye Special, increasing Attack";
		//Increase own attack
	default:
		return "NOTHING";
	}
}

int SpinachBoss::skill(int x)
{
	switch (x)
	{
	case 1:
		setcurrentDamage(getDamage() * 2.5);
		return 2;
	case 2:
		return 4;
	case 3:
		setcurrentResistance(getResistance() * 3);
		return 0;
	case 4:
		setcurrentDamage(getDamage() * 2.5);
		return 4;
	default:
		return 0;
	}
}

SpinachBoss::~SpinachBoss()
{
}
