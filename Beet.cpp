#include "Beet.h"
Beet::Beet(int x)
{
	setHealth(100*(x * 0.05 + 1));
	setDamage(30 * (x * 0.05 + 1));
	setResistance(30 * (x * 0.05 + 1));
	setSpeed(40 * (x * 0.05 + 1));
	setcurrentHealth(getHealth());
	setcurrentDamage(getDamage());
	setcurrentResistance(getResistance());
	setcurrentSpeed(getSpeed());
	setname("Beet");
	setskillcd(0);
	setatktarget("0");
}

string Beet::getMoveName(int MoveNo)
{
	switch (MoveNo)
	{
	case 1:
		return "Beetbox, damaging all Companions";
		//Low dmg affects all player's party members
	case 2:
		return "Can you beet this, highly damaging ";
		//Big dmg
	case 3:
		return "Beauty and a beet, sacrificing Speed for Attack";
		//Lowers speed,raises own attack
	case 4:
		return "Grounded, lowering Speed while increasing Defence";
		//Lowers speed,raise resistance
	default:
		return "NOTHING";
	}
}

int Beet::skill(int x)
{
	switch (x)
	{
	case 1:
		return 1;
	case 2:
		setcurrentSpeed(getSpeed()*0.5);
		setcurrentResistance(getResistance() * 2.75);
		return 0;
	case 3:
		setcurrentSpeed(getSpeed() * 0.5);
		setcurrentDamage(getDamage() * 1.75);
		return 0;
	case 4:
		setcurrentDamage(getDamage() * 2.5);
		return 2;
	default:
		return 0;
	}
}

Beet::~Beet()
{
}