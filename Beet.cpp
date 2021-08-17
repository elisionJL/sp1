#include "Beet.h"

string Beet::getMoveName(int MoveNo)
{
	switch (MoveNo)
	{
	case 1:
		return "Beetbox";
		//Low dmg affects all player's party members
	case 2:
		return "Grounded";
		//Lowers speed,raise resistance
	case 3:
		return "Beauty and a beet";
		//Raise player's speed,raises own attack
	case 4:
		return "Can you beet this?";
		//Raise attack a lot for next attack
	default:
		return "NOTHING";
	}
}

double Beet::getMovePower(int MoveNo)
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


