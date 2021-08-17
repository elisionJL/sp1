#pragma once
#include "Entity.h"
class Minion :public Entity
{
public:

private:
	string getMoveName(int MoveNo);
	int getMovePower(int MoveNo);
};
