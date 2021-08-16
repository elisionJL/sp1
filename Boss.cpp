#include "Boss.h"

Boss::Boss()
{
	//Base boss stats
	setHealth(200);
	setDamage(25);
	setResistance(50);
	setSpeed(30);
}

string Boss::getMove4Name()
{
	return Move4;
}

void Boss::setMove4Name(string Name)
{
	Move4 = Name;
}

int Boss::getMove4Power()
{
	return Move4Power;
}

void Boss::setMove4Power(int Power)
{
	Move4Power = Power;
}

void Boss::ExecuteMove(int move)
{
	switch (move)
	{
	case 1:

	case 2:

	case 3:

	case 4:

	}
}

Boss::~Boss()
{
}

