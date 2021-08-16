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

void Entity::setMove1Power(int Power)
{
	this->Move1Power = Power;
}

int Entity::getMove1Power()
{
	return Move1Power;
}

void Entity::setMove2Power(int Power)
{
	this->Move2Power = Power;
}

int Entity::getMove2Power()
{
	return Move2Power;
}

void Entity::setMove3Power(int Power)
{
	this->Move3Power = Power;
}

int Entity::getMove3Power()
{
	return Move3Power;
}

Entity::~Entity()
{
}
