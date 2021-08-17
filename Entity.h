#pragma once
#include <string>
using namespace std;
class Entity
{
private:
	double Health;
	double Damage;
	double Resistance;
	double Speed;
	double currentHealth;
	double currentDamage;
	double currentResistance;
	double currentSpeed;

public:
	Entity();

	//stats accessor/mutator
	double getHealth();
	void setHealth(double health);
	double getDamage();
	void setDamage(double dmg);
	double getResistance();
	void setResistance(double resistance);
	double getSpeed();
	void setSpeed(double speed);
	double getcurrentHealth();
	void setcurrentHealth(double health);
	double getcurrentDamage();
	void setcurrentDamage(double dmg);
	double getcurrentResistance();
	void setcurrentResistance(double resistance);
	double getcurrentSpeed();
	void setcurrentSpeed(double speed);
	void resetstats(int x);

	//Move powers get/set func
	virtual string getMoveName(int MoveNo) = 0;
	virtual double getMovePower(int MoveNo) = 0;
	~Entity();
};