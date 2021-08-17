#pragma once
#include "Boss.h"
class SpinachBoss : public Boss
{
private:

public: 
	SpinachBoss();
	string getMoveName(int MoveNo);
	int getMovePower(int MoveNo);
	~SpinachBoss();
};
