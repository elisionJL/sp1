#pragma once
#include "Boss.h"
class Eggplant :    public Boss
{
public:

private:
	Eggplant();
	string getMoveName(int MoveNo);
	int getMovePower(int MoveNo);
	~Eggplant();
};

