#include "Eggplant.h"
#include <string>

Eggplant::Eggplant()
{
}

string Eggplant::getMoveName(int MoveNo)
{
	switch (MoveNo)
	{
	case 1:
		return "SQUASH";
		//Basic damage ability
	case 2:
		return " Rollout";
		//Low damage,hits 2 members
	case 3:
		return "Nightshade";
		//Decrease 1 of player's party member's resistance
	case 4:
		return "Purple plague";
		//Decrease a stat of all player's party members by a little
	default:
		return "NOTHING";
	}
}

int Eggplant::getMovePower(int MoveNo)
{
	switch (MoveNo)
	{
	case 1:
		return 1;
	case 2:
		return 1;
	case 3:
		return 0;
	case 4:
		return 0;
	default:
		return 0;
	}
}

Eggplant::~Eggplant()
{
}
