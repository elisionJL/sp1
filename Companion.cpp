#include "Companion.h"

Companion::Companion()
{
}

Companion::Companion(int companionsID)
{
	companionId = companionsID;
	setHealth(rand() % 50 + 50);
	setDamage(rand() % 15 + 15);
	setResistance(rand() % 15 + 15);
	setSpeed(rand() % 20 + 20);
}


int Companion::getStat()
{
	return 0;
}

int Companion::getType()
{
	return 0;
}

Companion::~Companion()
{
}
int buff(int id) {
	int typeId = 0;
	if (id == 1 || 2) {
		return 1;
	}
	else if (id == 3 || 4) {
		return 2;
	}
	else if (id == 5 || 6) {
		return 3;
	}
	else if (id == 7 || 8) {
		return 4;
	}
	switch (id == 9 || 10) {
		return 5;
	default:
		return 1;
	}
	
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

	}

}

float Companion::getMovePower(int MoveNo)
{
	switch (MoveNo) {
	case 1:
		return 1;
	case 2:
		return 1;
	case 3:
		switch (buff(companionId)) {
		case 1:
			return 1.5;
		case 2:
			return 1.5;
		case 3:
			return 1.5;
		case 4:
			return 1.5;
		case 5:
			return 1;
		}

	}
}
