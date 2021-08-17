#pragma once
#include <string>
using namespace std;
class Entity
{
private:
	float Health;
	float Damage;
	float Resistance;
	float Speed;

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
	virtual string getMoveName(int MoveNo) = 0;
	virtual int getMovePower(int MoveNo) = 0;
	~Entity();
};
