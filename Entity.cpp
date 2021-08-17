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
	case 2:
		currentDamage = Damage;
	case 3:
		currentResistance = Resistance;
	case 4:
		currentSpeed = Speed;
	case 5:
		currentHealth = Health;
		currentDamage = Damage;
		currentResistance = Resistance;
		currentSpeed = Speed;
	}
}

Entity::~Entity()
{
}