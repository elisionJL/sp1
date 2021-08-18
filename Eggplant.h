#pragma once
#include "Boss.h"
class Eggplant : public Boss
{
public:
	Eggplant(int x);
	string getMoveName(int MoveNo);
	int skill(int x);
	~Eggplant();
};
