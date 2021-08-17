#pragma once
#include "Entity.h"
class Minion :public Entity
{
public:

private:
	Minion();
	string getMoveName(int MoveNo);
	int getMovePower(int MoveNo);
	~Minion();
};
