#pragma once
#include "Entity.h"
class Eggplant : public Entity
{
public:
	Eggplant(int x);
	string getMoveName(int MoveNo);
	int skill(int x);
	~Eggplant();
};
