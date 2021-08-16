#include "Entity.h"

Entity::Entity()
{
}

int Entity::getHealth()
{
	return Health;
}

void Entity::setHealth(int health)
{
	this->Health = health;
}


int Entity::getDamage()
{
	return Damage;
}

void Entity::setDamage(int dmg)
{
	this->Damage = dmg;
}

int Entity::getResistance()
{
	return Resistance;
}

void Entity::setResistance(int resistance)
{
	this->Resistance = resistance;
}

int Entity::getSpeed()
{
	return Speed;
}

void Entity::setSpeed(int speed)
{
	this->Speed = speed;
}

Entity::~Entity()
{
}
