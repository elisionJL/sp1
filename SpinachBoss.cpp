#include "SpinachBoss.h"
#include <string>

SpinachBoss::SpinachBoss(int x)
{
	setHealth(100 * (x * 0.05+1));
	setDamage(30 * (x * 0.05 + 1));
	setResistance(30 * (x * 0.05 + 1));
	setSpeed(40 * (x * 0.05 + 1));
	setcurrentHealth(getHealth());
	setcurrentDamage(getDamage());
	setcurrentResistance(getResistance());
	setcurrentSpeed(getSpeed());
	setname("Spinach");
	setskillcd(0);
	setatktarget("0");
}

string SpinachBoss::getMoveName(int MoveNo)
{
	switch (MoveNo)
	{
	case 1:
		return " Salty, decreasing Attack of ";
		//Decrease 1 of player's party member's attack
	case 2:
		return "SPIN-ACH, highly damaging ";
		//Basic damage ability
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
		return 5;
	case 2:
		setcurrentDamage(getDamage() * 2.5);
		return 2;
	case 3:
		setcurrentResistance(getResistance() * 3);
		return 0;
	case 4:
		setcurrentDamage(getDamage() * 3);
		return 0;
	default:
		return 0;
	}
}

SpinachBoss::~SpinachBoss()
{
}
