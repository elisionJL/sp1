#include "Entity.h"
Entity::Entity()
{
	Health = 0;
	Damage = 0;
	Resistance = 0;
	currentHealth = Health;
	currentDamage = Damage;
	currentResistance = Resistance;
	skillcd = 0;
}

double Entity::getHealth()
{
	return Health;
}

void Entity::setHealth(double health)
{
	this->Health = health;
}

double Entity::getDamage()
{
	return Damage;
}

void Entity::setDamage(double dmg)
{
	this->Damage = dmg;
}

double Entity::getResistance()
{
	return Resistance;
}

void Entity::setResistance(double resistance)
{
	this->Resistance = resistance;
}

double Entity::getcurrentHealth()
{
	return currentHealth;
}
void Entity::setcurrentHealth(double health)
{
	this->currentHealth = health;
}
double Entity::getcurrentDamage()
{
	return currentDamage;
}
void Entity::setcurrentDamage(double dmg)
{
	this->currentDamage = dmg;
}
double Entity::getcurrentResistance()
{
	return currentResistance;
}
void Entity::setcurrentResistance(double resistance)
{
	this->currentResistance = resistance;
}

void Entity::resetstats(int x)
{
	switch (x)
	{
	case 1:
		setatktarget(-1);
		break;
	case 2:
		currentDamage = Damage;
		break;
	case 3:
		currentResistance = Resistance;
		break;
	case 4:
		currentHealth = Health;
		currentDamage = Damage;
		currentResistance = Resistance;
		setatktarget(-1);
		setskillcd(0);
		break;
	}
}

void Entity::setname(std::string x)
{
	name = x;
}

int Entity::getskillcd()
{
	return skillcd;
}

void Entity::setskillcd(int x)
{
	skillcd = x;
}

int Entity::skill(int x)
{
	return 0;
}

int Entity::getatktarget()
{
	return atktarget;
}

void Entity::setatktarget(int x)
{
	atktarget = x;
}

std::string Entity::getname()
{
	return name;
}

double Entity::attack(double x)
{
	double dmgdone = currentDamage - (x * 0.2);
	if (dmgdone < 0)
		dmgdone = 0;
	return dmgdone;
}

void Entity::block()
{
	currentResistance += currentResistance * 0.5;
}

void Entity::takedmg(double x)
{
	currentHealth -= x;
	if (currentHealth < 0)
		currentHealth = 0;
}

Entity::~Entity()
{
}