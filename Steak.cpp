
#include "Steak.h"

Steak::Steak(int x)
{
	setHealth(100 * (x * 0.05 + 1));
	setDamage(30 * (x * 0.05 + 1));
	setResistance(30 * (x * 0.05 + 1));
	setcurrentHealth(getHealth());
	setcurrentDamage(getDamage());
	setcurrentResistance(getResistance());
	setname("Steak");
	setskillcd(0);
	setatktarget(-1);
}

string Steak::getMoveName(int MoveNo)
{
	switch (MoveNo)
	{
	case 1:
		return "Tender Loving Care, damaging all Companions";
		//Deals slight damage to all
	case 2:
		return "Beef Up, dealing ";
		//Deals moderate damage to 1 
	case 3:
		return "Well Done, slightly increasing all stats";
		//raises all stats a little
	case 4:
		return "Misteak, healing slightly";
		//Heal a little
	case 5:
		return "Steak Out, sacrificing Defence for Attack";
		//Decrease resistance,increase speed and attack
	default:
		return "NOTHING";
	}
}

double Steak::getMovePower(int MoveNo)
{
	switch (MoveNo)
	{
	case 1:
		return 1;
	case 2:
		setcurrentDamage(getDamage() * 1.75);
		return 2;
	case 3:
		setcurrentHealth(getcurrentHealth() + getHealth() * 0.05);
		if (getcurrentHealth() > getHealth())
			setcurrentHealth(getHealth());
		setcurrentDamage(getDamage() * 1.5);
		setcurrentResistance(getResistance() * 1.5);
		return 0;
	case 4:
		setcurrentHealth(getcurrentHealth() + getHealth() * 0.15);
		if (getcurrentHealth() > getHealth())
			setcurrentHealth(getHealth());
		return 0;
	case 5:
		setcurrentDamage(getDamage() * 3);
		setcurrentResistance(getResistance() * 0.25);
		return 0;
	default:
		return 0;
	}
}

Steak::~Steak()
{
}