#include "player.h"
player::player(std::string a, std::string b)
{
	exp = 0;
	name = a;
	type = b;
	level = 1;
	charactersowned = 1;
	coins = 10000;
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
void player::gacha(int x)
{
	coins -= 1500;
	if (x == 1)
		charactersowned += 1;
}
void player::stagecleared(int x, int y)
{
	coins += x;
	exp += y;
}
int player::getplayerinfo(int x)
{
	if (x == 1)
		return level;
	if (x == 2)
		return exp;
	if (x == 3)
		return charactersowned;
	if (x == 4)
		return coins;
	return 0;
}
std::string player::getplayerstrinfo(int x)
{
	if (x == 1)
		return name;
	if (x == 2)
		return type;
	return "0";
}
