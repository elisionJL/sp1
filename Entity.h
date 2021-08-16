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
	string Move1Name;
	string Move2Name;
	string Move3Name;
	string Move4Name;

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
	//Move names get/set
	string getMoveName(int MoveNo);
	virtual void setMove1Name(string name);
	virtual void setMove2Name(string name);
	void setMove3Name(string name);
	void setMove4Name(string name);
	~Entity();
};
