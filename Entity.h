#pragma once
#include <string>
using namespace std;
class Entity
{
private:
	int Health;
	int Damage;
	int Resistance;
	int Speed;
	int Move1Power;
	string Move1;
	int Move2Power;
	string Move2;
	int Move3Power;
	string Move3;

public:
	Entity();

	//stats accessor/mutator
	int getHealth();
	void setHealth(int health);
	int getDamage();
	void setDamage(int dmg);
	int getResistance();
	void setResistance(int resistance);
	int getSpeed();
	void setSpeed(int speed);

	//Move powers get/set func
	string getMoveName(int MoveNo);
	void setMoveName(int MoveNo,string Name);
	int getMovePower(int MoveNo);
	void setMovePower(int MoveNo,int Power);
	~Entity();
};


