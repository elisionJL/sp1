#include "Eggplant.h"
#include <string>

Eggplant::Eggplant(int x)
{
	setHealth(100 * (x * 1.05));
	setDamage(30 * (x * 1.05));
	setResistance(30 * (x * 1.05));
	setSpeed(40 * (x * 1.05));
	setcurrentHealth(getHealth());
	setcurrentDamage(getDamage());
	setcurrentResistance(getResistance());
	setcurrentSpeed(getSpeed());
	setname("Eggplant");
}

string Eggplant::getMoveName(int MoveNo)
{
	switch (MoveNo)
	{
	case 1:
		return "SQUASH";
		//Basic damage ability
	case 2:
		return " Rollout";
		//Low damage on all
	case 3:
		return "Nightshade";
		//Decrease 1 of player's party member's resistance
	case 4:
		return "Purple plague";
		//Decrease a stat of all player's party members by a little
	default:
		return "NOTHING";
	}
}

int Eggplant::skill(int x)
{
	switch (x)
	{
	case 1:
		setcurrentDamage(getDamage() * 2.5);
		return 2;
	case 2:
		return 1;
	case 3:
		return 5;
	case 4:
		return 7;
	default:
		return 0;
	}
}

Eggplant::~Eggplant()
{
}
