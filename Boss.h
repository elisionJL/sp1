#pragma once
#include "Entity.h"
using namespace std;
class Boss : public Entity
{
public:
	Boss();
	string getMoveName(int MoveNo);
	virtual int skill(int x);
	~Boss();
};