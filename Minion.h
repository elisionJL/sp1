#pragma once
#include "Entity.h"
class Minion :public Entity
{
private:

public:
	Minion();
	string getMoveName(int MoveNo);
	double getMovePower(int MoveNo);
	~Minion();
};
