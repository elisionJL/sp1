#pragma once
#include "Boss.h"
class Steak :public Entity
{
public:
	Steak(int x);
	string getMoveName(int MoveNo);
	double getMovePower(int MoveNo);
	~Steak();
};
