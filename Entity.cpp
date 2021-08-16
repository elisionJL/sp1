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
	if (MoveNo == 1)
	{
		return Move1Name;
	}
	else if (MoveNo == 2)
	{
		return Move2Name;
	}
	else if (MoveNo == 3)
	{
		return Move3Name;
	}
	else if (MoveNo == 4)
	{
		return Move4Name;
	}
	else
	{
		return 0;
	}

}

void Entity::setMove1Name(std::string name)
{
	Move1Name = name;
}

void Entity::setMove2Name(std::string name)
{
	Move2Name = name;
}

void Entity::setMove3Name(std::string name)
{
	Move3Name = name;
}

void Entity::setMove4Name(std::string name)
{
	Move4Name = name;
}

Entity::~Entity()
{
}
