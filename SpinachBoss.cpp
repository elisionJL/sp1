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
		//No idea
	case 4:
		return "Popeye Special";
		//Increase own attack
	}
}

int SpinachBoss::getMovePower(int MoveNo)
{

}
