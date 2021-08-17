#include "player.h"
player::player(std::string a, std::string b)
{
	exp = 0;
	name = a;
	type = b;
	level = 1;
	charactersowned = 0;
	coins = 3000;
	highestclearedstage = 0;
}
player::~player()
{
}
void player::checklevelup()
{
	while (exp >= 100 * level)
	{
		exp -= 100 * level;
		level++;
	}
}
void player::gacha()
{
	coins -= 1500;
}
void player::stagecleared(int x, int y)
{
	coins += x;
	exp += y;
}
int player::getplayerinfo(int x)
{
	switch (x)
	{
	case 1:
		return level;
	case 2:
		return exp;
	case 3:
		return charactersowned;
	case 4:
		return coins;
	case 5:
		return highestclearedstage;
	}
	return 0;
}
std::string player::getplayerstrinfo(int x)
{
	switch (x)
	{
	case 1:
		return name;
	case 2:
		return type;
	}
	return "0";
}
void player::clearednewstage()
{
	highestclearedstage++;
}
void player::companionupgrade(int x)
{
	coins -= x;
}
void player::newcompanion()
{
	charactersowned++;
}
void player::setcompanionno(int x)
{
	charactersowned = x;
}