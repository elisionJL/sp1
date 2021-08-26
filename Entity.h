#pragma once
#include <string>
using namespace std;
class Entity
{
private:
	double Health;
	double Damage;
	double Resistance;
	double currentHealth;
	double currentDamage;
	double currentResistance;
	std::string name;
	int skillcd;
	int atktarget;

public:
	Entity();

	//stats accessor/mutator
	double getHealth();
	void setHealth(double health);
	double getDamage();
	void setDamage(double dmg);
	double getResistance();
	void setResistance(double resistance);
	double getcurrentHealth();
	void setcurrentHealth(double health);
	double getcurrentDamage();
	void setcurrentDamage(double dmg);
	double getcurrentResistance();
	void setcurrentResistance(double resistance);
	void resetstats(int x);
	void setname(std::string x);
	int getskillcd();
	void setskillcd(int x);
	int getatktarget();
	void setatktarget(int x);
	std::string getname();
	virtual string getMoveName(int MoveNo) = 0;
	virtual int skill(int x);
	double attack(double x);
	void block();
	void takedmg(double x);
	~Entity();
};