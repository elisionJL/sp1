#include "Entity.h"
Entity::Entity()
{
	Health = 0;
	Damage = 0;
	Speed = 0;
	Resistance = 0;
	currentHealth = Health;
	currentDamage = Damage;
	currentResistance = Resistance;
	currentSpeed = Speed;
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

double Entity::getSpeed()
{
	return Speed;
}

void Entity::setSpeed(double speed)
{
	this->Speed = speed;
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
double Entity::getcurrentSpeed()
{
	return currentSpeed;
}
void Entity::setcurrentSpeed(double speed)
{
	this->currentSpeed = speed;
}
void Entity::resetstats(int x)
{
	switch (x)
	{
	case 1:
		currentHealth = Health;
		break;
	case 2:
		currentDamage = Damage;
		break;
	case 3:
		currentResistance = Resistance;
		break;
	case 4:
		currentSpeed = Speed;
		break;
	case 5:
		currentHealth = Health;
		currentDamage = Damage;
		currentResistance = Resistance;
		currentSpeed = Speed;
		break;
	}
}

void Entity::setname(std::string x)
{
	name = x;
}

std::string Entity::getname()
{
	return name;
}

int Entity::attack(int x)
{
	return currentDamage - x * 0.5;
}

void Entity::block()
{
	currentResistance += currentResistance * 2;
}

int Entity::skill(int x)
{
}

void Entity::takedmg(int x)
{
	currentHealth -= x;
	if (currentHealth > 0)
		currentHealth == 0;
}

Entity::~Entity()
{
}
