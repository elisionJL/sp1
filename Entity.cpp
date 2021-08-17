#include "Entity.h"
Entity::Entity()
{
	Health = 0;
	Damage = 0;
	Speed = 0;
	Resistance = 0;

}

float Entity::getHealth()
{
	return Health;
}

void Entity::setHealth(float health)
{
	this->Health = health;
}

float Entity::getDamage()
{
	return Damage;
}

void Entity::setDamage(float dmg)
{
	this->Damage = dmg;
}

float Entity::getResistance()
{
	return Resistance;
}

void Entity::setResistance(float resistance)
{
	this->Resistance = resistance;
}

float Entity::getSpeed()
{
	return Speed;
}

void Entity::setSpeed(float speed)
{
	this->Speed = speed;
}
string Entity::getMoveName(int MoveNo)
{
	return "EntityMoveName";
}

int Entity::getMovePower(int MoveNo)
{
	return 0;
}

Entity::~Entity()
{
}
