#pragma once
#include "Boss.h"
class Steak :public Boss
{
public:

private:
	Steak();
	string getMoveName(int MoveNo);
	int getMovePower(int MoveNo);
	~Steak();
};
