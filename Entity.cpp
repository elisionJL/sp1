#include "Entity.h"
Entity::Entity()
{
	Health = 0;
	Damage = 0;
	Speed = 0;
	Resistance = 0;

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

Entity::~Entity()
{
}
