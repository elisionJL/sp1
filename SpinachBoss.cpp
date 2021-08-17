#include "SpinachBoss.h"
#include <string>

string SpinachBoss::getMoveName(int MoveNo)
{
	switch (MoveNo)
	{
	case 1:
		return "SPIN-ACH";
		//Basic damage ability
	case 2:
		return " Saltyyy";
		//Decrease 1 of player's party member's attack
	case 3:
		return "Greens are good!";
		//increase resistance
	case 4:
		return "Popeye Special";
		//Increase own attack
	default:
		return "NOTHING";
	}
}

int SpinachBoss::getMovePower(int MoveNo)
{
	switch (MoveNo)
	{
	case 1:
		return 1;
	case 2:
		return 0;
	case 3:
		return 0;
	case 4:
		return 0;
	default:
		return 0;
	}
}
