#pragma once
#include "Entity.h"
using namespace std;
class Boss : public Entity
{
private:
	string Move4;
	int Move4Power;
public:
	Boss();
	string getMove4Name();
	void setMove4Name(string Name);
	int getMove4Power();
	void setMove4Power(int Power);
	void ExecuteMove(int move);
	~Boss();

	
};
