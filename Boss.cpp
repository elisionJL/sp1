#include "Boss.h"

Boss::Boss()
{
	//Base boss stats
	setHealth(200);
	setDamage(50);
	setResistance(20);
	setSpeed(30);
}

string Boss::getMoveName(int MoveNo)
{
	return "BossGETNAME";
}

int Boss::getMovePower(int MoveNo)
{
	return 0;
}

Boss::~Boss()
{
}
