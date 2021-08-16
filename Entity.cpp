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
string Entity::getMoveName(int MoveNo)
{
	switch (MoveNo)
	{
	case 1:
		return Move1;
	case 2:
		return Move2;
	case 3:
		return Move3;
	default:
		return ;
	}
}
void Entity::setMoveName(int MoveNo,string Name)
{
	if (MoveNo == 1)
	{
		Move1 = Name;
	}
	else if (MoveNo == 2)
	{
		Move2=Name;
	}
	else if (MoveNo == 3)
	{
		Move3=Name;
	}
}

int Entity::getMovePower(int MoveNo)
{
	if (MoveNo==1)
	{
		return Move1Power;
	}
	else if (MoveNo == 2)
	{
		return Move2Power;
	}
	else if (MoveNo == 3)
	{
		return Move3Power;
	}
	else
	{
	return 0;
	}
}

void Entity::setMovePower(int MoveNo, int Power)
{
	switch (MoveNo)
	{
	case 1:
		Move1Power = Power;
	case 2:
		Move2Power = Power;
	case 3:
		Move3Power = Power;
	}
}

Entity::~Entity()
{
}
