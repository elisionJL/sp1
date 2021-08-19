#pragma once
#include "Entity.h"
class Beet : public Entity
{
public:
	Beet(int x);
	string getMoveName(int MoveNo);
	int skill(int x);
	~Beet();
};
