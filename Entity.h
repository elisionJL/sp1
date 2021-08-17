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
	float getHealth();
	void setHealth(float health);
	float getDamage();
	void setDamage(float dmg);
	float getResistance();
	void setResistance(float resistance);
	float getSpeed();
	void setSpeed(float speed);

	//Move powers get/set func
	virtual string getMoveName(int MoveNo) = 0;
	virtual float getMovePower(int MoveNo) = 0;
	~Entity();
};
