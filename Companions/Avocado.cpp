#include "Avocado.h"

Avocado::Avocado()
{
	setDamage(10);
	setHealth(10);
	setSpeed(10);
	setResistance(10);
}

string Avocado::getMoveName(int moveNo)
{
	switch (moveNo) {
	case 1:
		return "squash";
	case 2:
		return "tackle";
	case 3:
		return "shine";
	case 4:
		return "roll";
	}
}
int Avocado::getMovePower(int MoveNo)
{
	switch (MoveNo) {
	case 1:
		return 90;
	case 2:
		return 70;
	case 3://defence buff move
		return 50;
	case 4://speed up
		return 50;
	}

}
