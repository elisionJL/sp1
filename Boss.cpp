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

double Boss::getMovePower(int MoveNo)
{
	return 0;
}

Boss::~Boss()
{
}