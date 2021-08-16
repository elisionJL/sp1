#pragma once
#include <string>
class Entity
{
private:
	int Health;
	int Damage;
	int Resistance;
	int Speed;
	std::string Move1Name;
	std::string Move2Name;
	std::string Move3name;
	std::string Move4name;

public:
	Entity();
	int getHealth();
	void setHealth(int health);
	int getDamage();
	void setDamage(int dmg);
	int getResistance();
	void setResistance(int resistance);
	int getSpeed();
	void setSpeed(int speed);
	virtual void setMove1Name(std::string name);
	virtual void setMove2Name(std::string name);
	void setMove3Name(std::string name);
	void setMove4Name(std::string name);
	~Entity();
};
