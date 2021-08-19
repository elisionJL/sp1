#include "Eggplant.h"
#include <string>

Eggplant::Eggplant(int x)
{
	setHealth(100 * (x * 0.05 + 1));
	setDamage(30 * (x * 0.05 + 1));
	setResistance(30 * (x * 0.05 + 1));
	setSpeed(40 * (x * 0.05 + 1));
	setcurrentHealth(getHealth());
	setcurrentDamage(getDamage());
	setcurrentResistance(getResistance());
	setcurrentSpeed(getSpeed());
	setname("Eggplant");
	setskillcd(0);
	setatktarget("0");
}

string Eggplant::getMoveName(int MoveNo)
{
	switch (MoveNo)
	{
	
	case 1:
		return "Rollout, damaging all Companions";
		//Low damage on all
	case 2:
		return "SQUASH, highly damaging ";
		//Basic damage ability
	case 3:
		return "Nightshade, decreasing Defence of ";
		//Decrease 1 of player's party member's resistance
	case 4:
		return "Purple plague, decreasing a stat of all Companions";
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
		return 1;
	case 2:
		setcurrentDamage(getDamage() * 2.5);
		return 2;
	case 3:
		return 3;
	case 4:
		return 4;
	default:
		return 0;
	}
}

Eggplant::~Eggplant()
{
}
