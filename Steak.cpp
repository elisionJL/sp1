
#include "Steak.h"

Steak::Steak(int x)
{
	setHealth(100 * (x * 1.05));
	setDamage(30 * (x * 1.05));
	setResistance(30 * (x * 1.05));
	setSpeed(40 * (x * 1.05));
	setcurrentHealth(getHealth());
	setcurrentDamage(getDamage());
	setcurrentResistance(getResistance());
	setcurrentSpeed(getSpeed());
	setname("Steak");
}

string Steak::getMoveName(int MoveNo)
{
	switch (MoveNo)
	{
	case 1:
		return "Well Done, slightly increasing all stats";
		//raises all stats a little
	case 2:
		return "Misteak, healing slightly";
		//Heal a little
	case 3:
		return "Beef Up";
		//Deals moderate damage to 1 
	case 4:
		return "Tender Loving Care";
		//Deals slight damage to all
	case 5:
		return "Steak Out, sacrificing Defence for Attack and Speed";
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
		setcurrentHealth( getcurrentHealth()+getHealth() * 0.05);
		if (getcurrentHealth() > getHealth())
			setcurrentHealth(getHealth());
		setcurrentDamage(getDamage() * 1.5);
		setcurrentResistance(getResistance()* 1.5);
		setcurrentSpeed(getSpeed() * 1.5);
		return 0;
	case 2:
		setcurrentHealth(getcurrentHealth() + getHealth() * 0.15);
		if (getcurrentHealth() > getHealth())
			setcurrentHealth(getHealth());
		return 0;
	case 3:
		setcurrentDamage(getDamage() * 1.75);
		return 2;
	case 4:
		return 1;
	case 5:
		setcurrentDamage(getDamage() * 2);
		setcurrentResistance(getResistance() * 0.25);
		setcurrentSpeed(getSpeed() * 2);
		return 0;
	default:
		return 0;
	}
}

Steak::~Steak()
{
}