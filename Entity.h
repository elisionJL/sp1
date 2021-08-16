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
	int Move2Power;
	int Move3Power;

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

	void setMove1Power(int Power);
	int getMove1Power();
	void setMove2Power(int Power);
	int getMove2Power();
	void setMove3Power(int Power);
	int getMove3Power();
	~Entity();
};
