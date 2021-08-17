#pragma once
#include "Boss.h"
class Beet : public Boss
{
public:

private:
	Beet();
	string getMoveName(int MoveNo);
	int getMovePower(int MoveNo);
	~Beet();
};
