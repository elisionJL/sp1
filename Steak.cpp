#include "Steak.h"

string Steak::getMoveName(int MoveNo)
{
	switch (MoveNo)
	{
	case 1:
		return "Well Done";
		//raises all stats a little
	case 2:
		return "Misteak";
		//Heal a little
	case 3:
		return "Beef Up";
		//Raise attack a little,deals a bit of damage to 1
	case 4:
		return "Tender Loving Care";
		//Deals moderate damage to 1 
	case 5:
		return "Steak Out";
		//Decrease resistance,increase speed and attack,skips next turn
	}
}

int Steak::getMovePower(int MoveNo)
{
	switch (MoveNo)
	{
	case 1:
		return 0;
	case 2:
		return 1;
	case 3:
		return 1;
	case 4:
		return 0;
	}
}
