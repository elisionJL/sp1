#include "Boss.h"

Boss::Boss()
{
	//Base boss stats
	setHealth(200);
	setDamage(25);
	setResistance(50);
	setSpeed(30);
}

int Boss::getMove4Power()
{
	return Move4Power;
}

void Boss::setMove4Power(int Power)
{
	Move4Power = Power;
}

Boss::~Boss()
{
}

