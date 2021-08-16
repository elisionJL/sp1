#pragma once
class Entity
{
private:
	int Health;
	int Damage;
	int Resistance;
	int Speed;

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
	~Entity();
};
