#pragma once
#include "Boss.h"
class Beet : public Boss
{
public:
	Beet(int x);
	string getMoveName(int MoveNo);
	int skill(int x);
	~Beet();
};
