#include "Boss.h"

Boss::Boss()
{
	setHealth(0);
	setDamage(0);
	setResistance(0);
	setSpeed(0);
}

string Boss::getMoveName(int MoveNo)
{
	return "BossGETNAME";
}

void Boss::skill(int x)
{
}

Boss::~Boss()
{
}