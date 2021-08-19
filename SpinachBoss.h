#pragma once
#include "Entity.h"
class SpinachBoss : public Entity
{
public:
	SpinachBoss(int x);
	string getMoveName(int MoveNo);
	int skill(int x);
	~SpinachBoss();
};
