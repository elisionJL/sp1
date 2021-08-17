#pragma once
#include "Boss.h"
class Steak :public Boss
{
public:
	Steak();
	string getMoveName(int MoveNo);
	double getMovePower(int MoveNo);
	~Steak();
};
