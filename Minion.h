#pragma once
#include "Entity.h"
class Minion :public Entity
{
public:
	Minion(int x);
	~Minion();
	string getMoveName(int MoveNo);
	double getMovePower(int MoveNo);
};

