#pragma once
#include "Boss.h"
class Beet : public Boss
{
public:
	Beet();
	string getMoveName(int MoveNo);
	double getMovePower(int MoveNo);
	~Beet();
};
