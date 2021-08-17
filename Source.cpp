#include "Beet.h"
#include "Boss.h"
#include "Companion.h"
#include "Eggplant.h"
#include "Entity.h"
#include "Minion.h"
#include "player.h"
#include "SpinachBoss.h"
#include "Steak.h"
#include<string>
#include<iostream>
void setparty(Companion* cptr[10], Boss* bptr[4], player p,int party[3])
{
	for (int i = 0; i < 10; i++)
	{
		if (cptr[i] != nullptr)
		{
			cptr[i]->resetstats(5);
			std::cout << i + 1 << ". " << cptr[i]->getname() << std::endl;
		}
	}
	std::cout << p.getplayerinfo(3) + 1 << ". None" << std::endl;
	int createparty = 0;
	int companionid;
	while (createparty == 0)
	{
		for (int i = 0; i < p.getplayerinfo(3); i++)
		{
			std::cout << "Choose Companion " << i + 1 << ": ";
			std::cin >> companionid;
			int errorcheck = 0;
			for (int l = 0; l < 3; l++)
			{
				if (party[l] == companionid)
				{
					std::cout << "Cannot use the same party members" << std::endl;
					i--;
					errorcheck++;
				}
			}
			if (errorcheck == 0)
			{
				party[i] = companionid;
			}
		}
		int checkmembers=0;
		for (int i = 0; i < p.getplayerinfo(3); i++)
		{
			if (party[i] != p.getplayerinfo(3) + 1)
				checkmembers++;
		}
		if (checkmembers != 0)
			createparty = 1;
		else
			std::cout << "Party cannot be empty" << std::endl;
	}
}
int enhancecompanion(player p, Companion* cptr[10])
{
	int backloop = 0;
	int done = 0;
	int choice;
	while (done == 0)
	{
		while (backloop == 0)
		{
			for (int i = 0; i < 10; i++)
			{
				if (cptr[i] != nullptr)
				{
					cptr[i]->resetstats(5);
					std::cout << i + 1 << ". " << cptr[i]->getname() << std::endl;
				}
			}
			std::cout << p.getplayerinfo(3) + 1 << ". Back" << std::endl;
			std::cout << "Prompt: ";
			std::cin >> choice;
			std::cout << "" << std::endl;
			if (choice == p.getplayerinfo(3) + 1)
				return 0;
			backloop++;
			choice--;
		}
		while (backloop == 1)
		{
			std::cout <<"Coins: " <<p.getplayerinfo(4) << std::endl;
			std::cout << "Name: " << cptr[choice]->getname() << std::endl;
			std::cout << "Level: " << cptr[choice]->getlvl() << std::endl;
			std::cout << "Health: " << int(cptr[choice]->getHealth()) << std::endl;
			std::cout << "Attack: " << int(cptr[choice]->getDamage()) << std::endl;
			std::cout << "Defence: " << int(cptr[choice]->getResistance()) << std::endl;
			std::cout << "Speed: " << int(cptr[choice]->getSpeed()) << std::endl;
			std::cout << "Skill: " << cptr[choice]->getMoveName(3) << std::endl;
			std::cout << "" << std::endl;
			std::cout << "1. Upgrade (" << cptr[choice]->getupgradecost()<<" coins)" << std::endl;
			std::cout << "2. Back" << std::endl;
			int choice2;
			int errorcheck = 0;
			while (errorcheck == 0)
			{
				std::cout << "Prompt: ";
				std::cin >> choice2;
				if (choice2 == 2)
				{
					backloop--;
					errorcheck++;
				}
				if (choice2 == 1)
				{
					if (p.getplayerinfo(4) < cptr[choice]->getupgradecost())
						std::cout << "You do not have enough coins" << std::endl;
					else if (p.getplayerinfo(1) == cptr[choice]->getlvl())
						std::cout << "Companion level cannot exceed your level" << std::endl;
					else
					{
						p.companionupgrade(int(cptr[choice]->getupgradecost()));
						cptr[choice]->lvlup();
						errorcheck++;
					}
				}
			}
			std::cout << "" << std::endl;
		}
	}
}
int summon(player p, Companion* cptr[10],std::string namelist[10])
{
	int choice;
	int summoned = 0;
	while (summoned == 0)
	{	
		std::cout << "Coins: " << p.getplayerinfo(4) << std::endl;
		std::cout << "1. Summon a friend (1500 coins)" << std::endl;
		std::cout << "2. Back" << std::endl;
		int errorcheck = 0;
		while (errorcheck == 0)
		{
			std::cout << "Prompt: ";
			std::cin >> choice;
			if (choice == 2)
			{
				std::cout << "" << std::endl;
				return p.getplayerinfo(3);
			}
			if (choice == 1)
			{
				if (p.getplayerinfo(4) < 1500)
				{
					std::cout << "You do not have enough coins" << std::endl;
				}
				else if (p.getplayerinfo(4) >= 1500)
				{
					std::cout << "" << std::endl;
					int repeat = 0;
					int pull = rand() % 10 + 1;
					for (int i = 0; i < 10; i++)
					{
						if (cptr[i] != nullptr)
						{
							if (pull == cptr[i]->getid())
							{
								std::cout << "You summoned another " << namelist[pull - 1] << "!" << std::endl;
								std::cout << namelist[pull - 1] << " has gained a 10% boost in stats" << std::endl;
								cptr[i]->summonedagain();
								p.gacha();
								repeat++;
							}
						}
					}
					if (repeat == 0)
					{
						cptr[p.getplayerinfo(3)] = new Companion(pull, namelist[pull - 1]);
						p.gacha();
						p.newcompanion();
						std::cout << "You summoned " << namelist[pull - 1] << "!" << std::endl;
					}
					errorcheck++;
					std::cout << "" << std::endl;
				}
			}
		}
	}
}
int menu(Companion* cptr[10], Boss* bptr[4], player p, int party[3],std::string namelist[10])
{
	int choice;
	int backloop = 0;
	int menuloop = 0;
	while (menuloop == 0)
	{
		while (backloop == 0)
		{
			std::cout << "-------------------------" << std::endl;
			std::cout << "1. Start Game" << std::endl;
			std::cout << "2. Quit" << std::endl;
			std::cout << "Prompt: ";
			std::cin >> choice;
			std::cout << "" << std::endl;
			if (choice == 2)
			{
				std::cout << "See you next time!" << std::endl;
				return 0;
			}
			backloop++;
		}
		while (backloop == 1)
		{
			std::cout << "-------------------------" << std::endl;
			std::cout << "1. Stages" << std::endl;
			std::cout << "2. Party" << std::endl;
			std::cout << "3. Companions" << std::endl;
			std::cout << "4. Summon" << std::endl;
			std::cout << "5. Back" << std::endl;
			std::cout << "Prompt: ";
			std::cin >> choice;
			std::cout << "" << std::endl;
			if (choice == 5)
				backloop--;
			else
				backloop++;
		}
		while (backloop == 2)
		{
			std::cout << "-------------------------" << std::endl;
			if (choice == 1)
			{
				std::string stages[4] = { "I'm not going to just spin around and leave!", "That went eggcellently well","We are unbeetable","Everything at steak" };
				std::cout << "Stages:" << std::endl;
				for (int i = 0; i <= p.getplayerinfo(5); i++)
				{
					std::cout << i + 1 << ". " << stages[i] << std::endl;
				}
				std::cout << p.getplayerinfo(5) + 2 << ". Back" << std::endl;
				std::cout << "Prompt: ";
				std::cin >> choice;
				std::cout << "" << std::endl;
				if (choice == p.getplayerinfo(5) + 2)
				{
					backloop--;
				}
				else
					return choice;
			}
			else if (choice == 2)
			{
				setparty(cptr, bptr, p, party);
				std::cout << "" << std::endl;
				backloop--;
			}
			else if (choice == 3)
			{
				int upgrademenu = enhancecompanion(p, cptr);
				if (upgrademenu == 0)
				{
					backloop--;
				}
			}
			else if (choice == 4)
			{
				int newcompanionno = summon(p, cptr, namelist);
				p.setcompanionno(newcompanionno);
				backloop--;
			}
		}
	}
}
int main(void)
{
	srand(time(NULL));
	std::string namelist[10] = { "Lolipop","Honey","Milk","Yohgurt","Rice","Pasta","Fish","Mussels","Grapes","Strawberries" };
	Companion* cptr[10] = { nullptr,nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
	Boss* bptr[4] = { nullptr,nullptr,nullptr,nullptr };
	bptr[0] = new SpinachBoss();
	bptr[1] = new Eggplant();
	bptr[2] = new Beet();
	bptr[3] = new Steak();
	player p("Wapples", "Apple");
	cptr[p.getplayerinfo(3)] = new Companion(3,"Milk");
	p.newcompanion();
	int party[3] = { 0,0,0 };
	int stagepicked = menu(cptr, bptr, p, party,namelist);
	if (stagepicked == 0)
		return 0;
}