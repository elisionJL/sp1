#pragma once
#include "Entity.h"
using namespace std;
class Boss : public Entity
{
private:
	int Move4Power;
public:
	Boss();
	int getMove4Power();
	void setMove4Power(int Power);
	~Boss();
};
