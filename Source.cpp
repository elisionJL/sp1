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
void setparty(Companion* cptr[10],  player p,int party[3])
{
	for (int i = 0; i < 10; i++)
	{
		if (cptr[i] != nullptr)
		{
			std::cout << i + 1 << ". " << cptr[i]->getname() << std::endl;
		}
	}
	std::cout << p.getplayerinfo(3) + 1 << ". None" << std::endl;
	int createparty = 0;
	int companionchoice;
	while (createparty == 0)
	{
		for (int i = 0; i < p.getplayerinfo(3); i++)
		{
			std::cout << "Choose Companion " << i + 1 << ": ";
			std::cin >> companionchoice;
			int errorcheck = 0;
			for (int l = 0; l < 3; l++)
			{
				if ((party[l] == companionchoice)&&(companionchoice!= p.getplayerinfo(3)+1))
				{
					std::cout << "Cannot use the same party members" << std::endl;
					i--;
					errorcheck++;
				}
			}
			if ((errorcheck == 0) && (companionchoice != p.getplayerinfo(3)+1))
			{
				party[i] = companionchoice;
			}
		}
		int checkmembers=0;
		for (int i = 0; i < p.getplayerinfo(3); i++)
		{
			if (party[i] !=0)
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
			std::cout << "Enhanced Level: " << cptr[choice]->gettimespulled()-1 << std::endl;
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
	return 0;
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
								std::cout << namelist[pull - 1] << "'s Enhanced Level has increased" << std::endl;
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
	return 0;
}
void battle(int party[3], Companion* cptr[10], Boss* bptr[3], player p, int stagepicked)
{
	int result=0;
	int checkparty = 0;
	int partysize = 0;
	for (int i = 0; i < 3; i++)
	{
		if (party[i] == 0)
		{
			checkparty++;
		}
	}
	if (checkparty == 3)
	{
		std::cout << "Party cannot be empty" << std::endl;
		setparty(cptr, p, party);
		std::cout << "" << std::endl;
	}
	for (int i = 0; i < 3; i++)
	{
		if (party[i] != 0)
		{
			cptr[i]->resetstats(5);
			partysize++;
		}
	}
	int enemyno=0;
	int minionno=0;
	int bossno=0;
	Minion* mptr[2] = { nullptr,nullptr };
	switch (stagepicked)
	{
	case 1:
		bptr[0] = new SpinachBoss(5);
		enemyno = 1;
		bossno = 1;
	case 2:
		bptr[0] = new Eggplant(10);
		mptr[0] = new Minion(10,"Cabbage");
		mptr[1] = new Minion(10,"Garlic");
		enemyno = 3;
		bossno = 1;
		minionno = 2;
	case 3:
		bptr[0] = new Beet(15);
		mptr[0] = new Minion(15,"Onion");
		mptr[1] = new Minion(15,"Peas");
		enemyno = 3;
		bossno = 1;
		minionno = 2;
	case 4:
		bptr[0] = new Steak(20);
		mptr[0] = new Minion(20,"Mutton");
		mptr[1] = new Minion(20,"Venison");
		enemyno = 3;
		bossno = 1;
		minionno = 2;
	}
	for (int i = 0; i < 3; i++)
	{
		if (party[i] != 0)
		{
			for (int l = 0; l < 10; l++)
			{
				if (cptr[l] != nullptr)
				{
					if (l == party[i]-1)
					{
						int choice;
						char target;
						int checktarget=0;
						std::cout << "-------------------------" << std::endl;
						std::cout << "Companion: " << cptr[l]->getname() << std::endl;
						int targeterrorcheck = 0;
						while (targeterrorcheck == 0)
						{
							std::cout << "Target: ";
							std::cin >> target;
							for (int k = 0; k < bossno; k++)
							{
								if (toupper(target) != (bptr[k]->getname())[0])
								{
									checktarget++;
								}
							}
							for (int k = 0; k < minionno; k++)
							{
								if (toupper(target) != (mptr[k]->getname()).front())
								{
									checktarget++;
								}
							}
							if (checktarget == enemyno)
							{
								std::cout << "Invalid target" << std::endl;
							}
							else
								targeterrorcheck++;
						}
						for (int f = 1; f < 4; f++)
							std::cout << f << ". " << cptr[l]->getMoveName(f) << std::endl;
						std::cout << "Prompt: ";
						std::cin >> choice;
						std::cout << "" << std::endl;
					}
				}
			}
		}
	}
	if (result == 0)
	{
		std::cout << "You lost!" << std::endl;
		std::cout << "Tip: Upgrade your companions" << std::endl;
		std::cout << "" << std::endl;
	}
	if (result == 1)
	{
		std::cout << "You won!" << std::endl;
	}
}
int menu(Companion* cptr[10], Boss* bptr[3], player p, int party[3],std::string namelist[10])
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
			std::cout << "Player Level: " << p.getplayerinfo(1) << std::endl;
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
				std::string stages[4] = { "I'm not going to just spin around and leave!", "That went eggcellently well","No time to beet about the bush","Everything at steak" };
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
				{
					battle(party, cptr, bptr, p, choice);
				}
			}
			else if (choice == 2)
			{
				for (int i = 0; i < 3; i++)
					party[i] = 0;
				setparty(cptr, p, party);
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
	return 0;
}

int main(void)
{
	srand((unsigned int)time(NULL));
	std::string namelist[10] = { "Lolipop","Honey","Milk","Yohgurt","Rice","Pasta","Fish","Mussels","Grapes","Strawberries" };
	Companion* cptr[10] = { nullptr,nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
	Boss* bptr[3] = { nullptr,nullptr,nullptr };
	player p("Wapples", "Apple");
	cptr[p.getplayerinfo(3)] = new Companion(3,"Milk");
	p.newcompanion();
	int party[3] = { 0,0,0 };
	int running = 0;
	while (running == 0)
	{
		int stagepicked = menu(cptr, bptr, p, party, namelist);
		if (stagepicked == 0)
			return 0;
	}
}