#pragma once
#include "Entity.h"
using namespace std;
class Boss : public Entity
{
private:

public:
	Boss();
	string getMoveName(int MoveNo);
	double getMovePower(int MoveNo);
	~Boss();
};
