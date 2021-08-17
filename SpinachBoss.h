#pragma once
#include "Boss.h"
class SpinachBoss : public Boss
{
private:

public: 
	string getMoveName(int MoveNo);
	int getMovePower(int MoveNo);
};

