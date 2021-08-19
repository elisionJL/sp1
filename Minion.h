#pragma once
#include "Entity.h"
#include<string>
class Minion :public Entity
{
public:
	Minion(int x,std::string y);
	~Minion();
	string getMoveName(int MoveNo);
	int skill(int x);
};

