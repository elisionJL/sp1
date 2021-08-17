#include "Companion.h"

Companion::Companion()
{
	companionId = 0;
	MovePower = 0;
}

Companion::Companion(int companionsID)
{
	companionId = companionsID;
	setHealth((rand() % 50) + 50.0);
	setDamage((rand() % 15) + 15.0);
	setResistance((rand() % 15) + 15.0);
	setSpeed((rand() % 20) + 20.0);
	MovePower = 0;
}

void Companion::setMovePower(float pwr)
{
	MovePower = pwr;
}


Companion::~Companion()
{
}
int buff(int id) {
	if (id == 1 || id == 2) {
		return 1;
	}
	else if (id == 3 || id == 4) {
		return 2;
	}
	else if (id == 5 || id == 6) {
		return 3;
	}
	else if (id == 7 || id == 8) {
		return 4;
	}
	else if (id == 9 || id == 10) {
		return 5;
	}
	return 0;
}

string Companion::getMoveName(int MoveNo)
{
	switch (MoveNo){
	case 1:
		return "Attack";
	case 2:
		return "Defend";
	case 3:
		switch (buff(companionId)) {
		case 1:
			return "Buff Speed";
		case 2:
			return "Shield";
		case 3:
			return "Buff Attack";
		case 4:
			return "Buff Shield";
		case 5:
			return "heal";
		}
	default:
		return "error";
	}

}

double Companion::getMovePower(int MoveNo)
{
	switch (MoveNo) {
	case 1:
		return 1;
	case 2:
		return 1;
	case 3:
		switch (buff(companionId)) {
		case 1:
			return MovePower*1.5;
		case 2:
			return 0.25;
		case 3:
			return MovePower * 1.5;
		case 4:
			return MovePower * 1.5;
		case 5:
			return 1;
		default:
			return 1;
		}
	default:
		return 1;
	}
}
