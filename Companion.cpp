#include "Companion.h"

Companion::Companion()
{
	companionId = 0;
	MovePower = 0;
	lvl = 0;
	upgradecost = 0;
	timespulled = 0;
	bonusHealth=0;
	bonusDamage=0;
	bonusResistance=0;
	bonusSpeed=0;
	bonushealing=0;
}

Companion::Companion(int companionsID,std::string x)
{
	companionId = companionsID;
	setHealth((rand() % 50) + 50.0);
	setDamage((rand() % 15) + 15.0);
	setResistance((rand() % 15) + 15.0);
	setSpeed((rand() % 20) + 20.0);
	setcurrentHealth(getHealth());
	setcurrentDamage(getDamage());
	setcurrentResistance(getResistance());
	setcurrentSpeed(getSpeed());
	MovePower = 0;
	setname(x);
	upgradecost = 200;
	lvl = 1;
	timespulled = 1;
	setskillcd(0);
	setatktarget("0");
}

Companion::~Companion()
{
}
int Companion::buff() 
{
	if (companionId == 1 || companionId == 2) {
		return 1;
	}
	else if (companionId == 3 || companionId == 4) {
		return 2;
	}
	else if (companionId == 5 || companionId == 6) {
		return 3;
	}
	else if (companionId == 7 || companionId == 8) {
		return 4;
	}
	else if (companionId == 9 || companionId == 10) {
		return 5;
	}
	return 0;
}

string Companion::getMoveName(int MoveNo)
{
	switch (MoveNo) 
	{
	case 1:
		return "Attack";
	case 2:
		return "Defend";
	case 3:
		switch (buff()) 
		{
		case 1:
			return "Buff Speed";
		case 2:
			return "Debuff";
		case 3:
			return "Buff Attack";
		case 4:
			return "Buff Defence";
		case 5:
			return "Heal";
		}
	default:
		return "error";
	}
}

int Companion::skill()
{
	switch (buff())
	{
	case 1:
		setcurrentSpeed(getSpeed() * 2);
		return 0;
	case 2:
		return 1;
	case 3:
		setcurrentDamage(getDamage() * 2);
		return 0;
	case 4:
		setcurrentResistance(getResistance() * 2);
		return 0;
	case 5:
		setcurrentHealth(getcurrentHealth() + getHealth() * (0.15+bonushealing));
		if (getcurrentHealth() > getHealth())
			setcurrentHealth(getHealth());
		return 0;
	default:
		return 0;
	}
}

void Companion::summonedagain()
{
	setHealth(getHealth() * 1.1);
	setDamage(getDamage() * 1.1);
	setResistance(getResistance() * 1.1);
	setSpeed(getSpeed() * 1.1);
	upgradecost += upgradecost * 1;
	timespulled++;
}

void Companion::lvlup()
{
	lvl++;
	upgradecost += upgradecost * 0.5;
	setHealth(getHealth()*1.05);
	setDamage(getDamage() * 1.05);
	setResistance(getResistance() * 1.05);
	setSpeed(getSpeed() * 1.05);
}

int Companion::getlvl()
{
	return lvl;
}

double Companion::getupgradecost()
{
	return upgradecost;
}
int Companion::getid()
{
	return companionId;
}
int Companion::gettimespulled()
{
	return timespulled;
}
void Companion::resonance(int x)
{
	switch (x)
	{
	case 1:
		bonusSpeed = getSpeed() * 0.2;
		setSpeed(getSpeed() * 1.2);
		break;
	case 2:
		bonusHealth = getHealth() * 0.2;
		setHealth(getHealth() * 1.2);
		break;
	case 3:
		bonusDamage = getDamage() * 0.2;
		setDamage(getDamage() * 1.2);
		break;
	case 4:
		bonusResistance = getResistance() * 0.2;
		setResistance(getResistance() * 1.2);
		break;
	case 5:
		bonushealing = 0.1;
		break;
	}
}
void Companion::removeresonace(int x)
{
	switch (x)
	{
	case 1:
		setSpeed(getSpeed() -bonusSpeed);
		bonusSpeed = 0;
		break;
	case 2:
		setHealth(getHealth()-bonusHealth);
		bonusHealth =0;
		break;
	case 3:
		setDamage(getDamage()-bonusDamage);
		bonusDamage = 0;
		break;
	case 4:
		setResistance(getResistance() -bonusResistance);
		bonusResistance = 0;
		break;
	case 5:
		bonushealing = 0;
		break;
	}
}