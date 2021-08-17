#pragma once
#include "Boss.h"
class Eggplant :    public Boss
{
public:

private:
	Eggplant();
	string getMoveName(int MoveNo);
	double getMovePower(int MoveNo);
	~Eggplant();
};

