#pragma once
#include "Boss.h"
class SpinachBoss : public Boss
{
public:
	SpinachBoss(int x);
	string getMoveName(int MoveNo);
	int skill(int x);
	~SpinachBoss();
};
