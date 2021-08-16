#include "player.h"
player::player(std::string a,std::string b)
{
	exp = 0;
	name = a;
	type = b;
	level = 1;
	charactersowned=0;
	coins=10000;
	gems=300;
	characterlvlupmat=10;
}
player::~player()
{
}
void player::checklevelup()
{
	if (exp >= 100 * level)
	{
		exp -= 100 * level;
		level++;
	}
}
void player::gacha(int x)
{
	coins -= 1500;
	gems -= 150;
	if (x == 1)
		charactersowned += 1;
}
void player::buycoins(int x)
{
	coins += 1000;
	gems -= 150;
}
void player::stagecleared(int x, int y, int z, int a)
{
	coins += x;
	gems += y;
	characterlvlupmat += z;
	exp += a;
}
void player::uselvlupmat(int x)
{
	coins -= x*500;
	characterlvlupmat -= x;
}
int player::getplayerinfo(int x)
{
	if (x == 1)
		return level;
	if (x==2)
		return exp;
	if (x==3)
		return charactersowned;
	if (x==4)
		return coins;
	if (x==5)
		return gems;
	if (x==6)
		return characterlvlupmat;
}
std::string player::getplayerstrinfo(int x)
{
	if (x == 1)
		return name;
	if (x == 2)
		return type;
}