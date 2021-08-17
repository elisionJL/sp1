#pragma once
#include "Boss.h"
class Eggplant :    public Boss
{
private:

public:
	Eggplant();
	string getMoveName(int MoveNo);
	double getMovePower(int MoveNo);
	~Eggplant();
};

