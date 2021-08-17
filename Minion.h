#pragma once
#include "Entity.h"
class Minion :public Entity
{
public:

private:
	Minion();
	string getMoveName(int MoveNo);
	double getMovePower(int MoveNo);
	~Minion();
};
