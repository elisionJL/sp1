#pragma once
#include<string>
class player
{
private:
	int level;
	int exp;
	std::string name;
	int charactersowned;
	int coins;
	std::string type;
	int highestclearedstage;
public:
	player(std::string a, std::string b);
	~player();
	void checklevelup();
	void gacha();
	void stagecleared(int x, int y);
	int getplayerinfo(int x);
	std::string getplayerstrinfo(int x);
	void clearednewstage();
	void companionupgrade(int x);
	void newcompanion();
	void setcompanionno(int x);
};

