#include "Beet.h"
#include "Companion.h"
#include "Eggplant.h"
#include "Entity.h"
#include "Minion.h"
#include "player.h"
#include "SpinachBoss.h"
#include "Steak.h"
#include<string>
#include<iostream>
#include<algorithm>
void story(int x, int y)
{

}
void setparty(Companion* cptr[10],  player p,Companion*party[3])
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
				if ((party[l] == cptr[companionchoice-1])&&(companionchoice!= p.getplayerinfo(3)+1))
				{
					std::cout << "Cannot use the same party members" << std::endl;
					i--;
					errorcheck++;
				}
			}
			if ((errorcheck == 0) && (companionchoice != p.getplayerinfo(3)+1))
			{
				party[i] = cptr[companionchoice-1];
			}
		}
		int checkmembers=0;
		for (int i = 0; i < 3; i++)
		{
			if (party[i] !=nullptr)
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
player battle(Companion* party[3], Companion* cptr[10], player p, int stagepicked)
{
	std::string minionnames[6] = { "Cabbage" ,"Garlic","Onion","Peas","Mutton","Venison" };
	std::string enemynames[5] = { "Spinach","Eggplant","Beet","Steak","Minion" };
	Entity* eptr[3] = { nullptr,nullptr,nullptr };
	int speedlist[6] = { -1,-1,-1,-1,-1,-1 };
	int result=0,checkparty = 0,partysize = 0,enemyno = 0,bossno = 0,minionno = 0,deadcompanion = 0,deadenemies = 0,difficulty= 1,sametype=0, allgood = 0;
	double dmg;
	for (int i = 0; i < 3; i++)
	{
		if (party[i] == nullptr)
		{
			checkparty++;
		}
	}
	if (checkparty == 3)
	{
		std::cout << "-------------------------" << std::endl;
		std::cout << "Party cannot be empty" << std::endl;
		setparty(cptr, p, party);
		std::cout << "" << std::endl;
	}
	if (stagepicked != 0)
	{
		std::cout << "1. Easy" << std::endl;std::cout << "2. Normal" << std::endl;std::cout << "3. Hard" << std::endl;std::cout << "4. Extreme" << std::endl;std::cout << "5. Death" << std::endl;std::cout << "Prompt: ";
		std::cin >> difficulty;
	}
	for (int i = 0; i < 3; i++)
	{
		if (party[i] != nullptr)
		{
			for (int l = 0; l < 3; l++)
			{
				if ((party[l] != nullptr)&&(party[l]!=party[i]))
				{
					if (party[l]->buff() == party[i]->buff())
					{
						sametype = party[l]->buff();
						l+=3; i += 3;
					}
				}
			}
		}
	}
	for (int i = 0; i < 3; i++)
	{
		if (party[i] != nullptr)
		{
			if (sametype != 0)
			{
				party[i]->resonance(sametype);
			}
			partysize++;
			cptr[i]->resetstats(5);
		}
	}
	switch (stagepicked)
	{
	case 0:
		std::cout << "Enemies:" << std::endl;
		int enemychoice;
		int enemylvl;
		for (int i = 0; i < 5; i++)
		{
			std::cout << i + 1 << ". " << enemynames[i] << std::endl;
		}
		std::cout << "6. None" << std::endl;
		while (allgood==0)
		{
			int error = 0;
			for (int i = 0; i < 3; i++)
			{
				std::cout << "Enemy " << i + 1 << ": ";
				std::cin >> enemychoice;
				if (enemychoice != 6)
				{
					std::cout << "Level (1-9999): ";
					std::cin >> enemylvl;
				}
				switch (enemychoice)
				{
				case 1:
					eptr[i] = new SpinachBoss(enemylvl);bossno++;enemyno++;
					break;
				case 2:
					eptr[i] = new Eggplant(enemylvl);bossno++;enemyno++;
					break;
				case 3:
					eptr[i] = new Beet(enemylvl);bossno++;enemyno++;
					break;
				case 4:
					eptr[i] = new Steak(enemylvl);bossno++;enemyno++;
					break;
				case 5:
					eptr[i] = new Minion(enemylvl, minionnames[rand() % 6]);bossno++;enemyno++;
					break;
				case 6:
					error++;
					break;
				}
			}
			if (error == 3)
			{
				std::cout << "Requires at least 1 enemy" << std::endl;
			}
			else
				allgood++;
		}
		break;
	case 1:
		eptr[0] = new SpinachBoss(5*difficulty);enemyno++;bossno++;
		break;
	case 2:
		eptr[0] = new Eggplant(10 * difficulty);eptr[1] = new Minion(10 * difficulty, minionnames[0]);eptr[2] = new Minion(10 * difficulty, minionnames[1]);enemyno += 3;bossno++;minionno += 2;
		break;
	case 3:
		eptr[0] = new Beet(15 * difficulty);eptr[1] = new Minion(15 * difficulty, minionnames[2]);eptr[2] = new Minion(15 * difficulty, minionnames[3]);enemyno += 3;bossno++;minionno += 2;
		break;
	case 4:
		eptr[0] = new Steak(20 * difficulty);eptr[1] = new Minion(20 * difficulty, minionnames[4]);eptr[2] = new Minion(20 * difficulty, minionnames[5]);enemyno += 3;bossno++;minionno += 2;
		break;
	}
	while (result == 0)
	{
		for (int i = 0; i < 3; i++)
		{
			if ((party[i] != nullptr) && (result == 0))
			{
				if (party[i]->getcurrentHealth() > 0)
				{
					int choice, target, choosemove = 0;
					std::cout << "-------------------------" << std::endl; std::cout << "Enemies: " << std::endl;
					for (int f = 0; f < 3; f++)
					{
						if (eptr[f] != nullptr)
						{
							if (eptr[f]->getcurrentHealth() > 0)
								std::cout << f + 1 << ". " << eptr[f]->getname() << "    Health: " << int(eptr[f]->getcurrentHealth()) << std::endl;
						}
					}
					std::cout << "" << std::endl;
					std::cout << "Companion: " << party[i]->getname() << "    Health: " << int(party[i]->getcurrentHealth()) << std::endl;
					std::cout << "Target: ";
					std::cin >> target;
					target--;
					for (int f = 1; f < 4; f++)
						std::cout << f << ". " << party[i]->getMoveName(f) << std::endl;
					while (choosemove == 0)
					{
						std::cout << "Prompt: ";
						std::cin >> choice;
						switch (choice)
						{
						case 1:
							party[i]->setatktarget(target);
							choosemove++;
							break;
						case 2:
							party[i]->block();
							std::cout << party[i]->getname() << " used Block, increasing Defence" << std::endl;
							choosemove++;
							break;
						case 3:
							if (party[i]->getskillcd() == 0)
							{
								int skillused = party[i]->skill();
								if (skillused == 1)
								{
									eptr[target]->setcurrentDamage(eptr[target]->getcurrentDamage() * 0.85);
									eptr[target]->setcurrentResistance(eptr[target]->getcurrentResistance() * 0.85);
									eptr[target]->setcurrentSpeed(eptr[target]->getcurrentSpeed() * 0.85);
									std::cout << party[i]->getname() << " used Debuff on " << eptr[target]->getname() << std::endl;
								}
								else
									std::cout << party[i]->getname() << " used " << party[i]->getMoveName(3) << std::endl;
								party[i]->setskillcd(4);
							}
							else if (party[i]->getskillcd() != 0)
							{
								std::cout << "Skill is on " << party[i]->getskillcd() << " turn cooldown" << std::endl;
							}
						}
					}
					if (party[i]->getskillcd() > 0)
						party[i]->setskillcd(party[i]->getskillcd() - 1);
				}
			}
		}
		for (int i = 0; i < 3; i++)
		{
			if ((eptr[i] != nullptr)&&(result==0))
			{
				if (eptr[i]->getcurrentHealth() > 0)
				{
					int targetcheck = 0, target, choosemove = 0;
					while (targetcheck == 0)
					{
						target = rand() % 3;
						if ((party[target] != nullptr) && (party[target]->getcurrentHealth() > 0))
						{
							targetcheck++;
						}
					}
					while (choosemove == 0)
					{
						int choice = rand() % 3 + 1;
						switch (choice)
						{
						case 1:
							eptr[i]->setatktarget(target);
							choosemove++;
							break;
						case 2:
							eptr[i]->block();
							std::cout << eptr[i]->getname() << " used Block, increasing Defence" << std::endl;
							choosemove++;
							break;
						case 3:
							if (eptr[i]->getskillcd() == 0)
							{
								int whichskill;
								int skillused;
								if (eptr[i]->getname() == "Steak")
									whichskill = rand() % 5 + 1;
								else
									whichskill = rand() % 4 + 1;
								skillused = eptr[i]->skill(whichskill);
								switch (skillused)
								{
								case 1:
									std::cout << eptr[i]->getname() << " used " << eptr[i]->getMoveName(1)<< std::endl;
									for (int l = 0; l < 3; l++)
									{
										if (party[l] != nullptr)
										{
											if (party[l]->getcurrentHealth() > 0)
											{
												dmg = eptr[i]->attack(party[l]->getcurrentResistance());
												party[l]->takedmg(dmg);
												if (party[l]->getcurrentHealth() == 0)
												{
													deadcompanion++;
													std::cout << party[l]->getname() << " has died" << std::endl;
													party[l]->setcurrentHealth(-1);
												}
											}
										}
									}
									if (deadcompanion == partysize)
									{
										result = 2;
										choosemove++;
									}
									if (eptr[i]->getskillcd() > 0)
									{
										eptr[i]->setskillcd(eptr[i]->getskillcd() - 1);
									}
									break;
								case 2:
									dmg = eptr[i]->attack(party[target]->getcurrentResistance());
									party[target]->takedmg(dmg);
									std::cout << eptr[i]->getname() << " used " << eptr[i]->getMoveName(2) << int(dmg) << " damage to " << party[target]->getname() << std::endl;
									if (party[target]->getcurrentHealth() == 0)
									{
										deadcompanion++;
										std::cout << party[target]->getname() << " has died" << std::endl;
										party[target]->setcurrentHealth(-1);
									}
									if (deadcompanion == partysize)
									{
										result = 2;
										choosemove++;
									}
									if (eptr[i]->getskillcd() > 0)
									{
										eptr[i]->setskillcd(eptr[i]->getskillcd() - 1);
									}
									break;
								case 3:
									party[target]->setcurrentResistance(party[target]->getcurrentResistance() * 0.3);
									std::cout << eptr[i]->getname() << " used " << eptr[i]->getMoveName(3) << party[target]->getname() << std::endl;
									break;
								case 4:
									for (int l = 0; l < 3; l++)
									{
										if (party[l] != 0)
										{
											int statdecrease = rand() % 3 + 1;
											if (statdecrease == 1)
												party[target]->setcurrentDamage(party[target]->getcurrentDamage() * 0.8);
											if (statdecrease == 2)
												party[target]->setcurrentResistance(party[target]->getcurrentResistance() * 0.8);
											if (statdecrease == 1)
												party[target]->setcurrentSpeed(party[target]->getcurrentSpeed() * 0.8);
										}
									}
									std::cout << eptr[i]->getname() << " used " << eptr[i]->getMoveName(4) << std::endl;
									break;
								case 5:
									party[target]->setcurrentDamage(cptr[target]->getcurrentDamage() * 0.3);
									std::cout << eptr[i]->getname() << " used " << eptr[i]->getMoveName(1) << party[target]->getname() << std::endl;
									break;
								case 0:
									std::cout << eptr[i]->getname() << " used " << eptr[i]->getMoveName(whichskill) << std::endl;
									break;
								}
							}
							eptr[i]->setskillcd(4);
						}
						if (eptr[i]->getskillcd() > 0)
							eptr[i]->setskillcd(eptr[i]->getskillcd() - 1);
					}
				}
			}
		}
		if (result == 0)
		{
			for (int i = 0; i < 3; i++)
			{
				if (party[i] != nullptr)
				{
					if (party[i]->getatktarget() != -1)
					{
						speedlist[i] = int(party[i]->getcurrentSpeed());
					}
				}
				if (eptr[i] != nullptr)
				{
					if (eptr[i]->getatktarget() != -1)
					{
						speedlist[i + 3] = int(eptr[i]->getcurrentSpeed());
					}
				}

			}
			std::sort(speedlist, speedlist + 6, greater<int>());
			for (int i = 0; i < 6; i++)
			{
				if (speedlist[i] != -1)
				{
					for (int l = 0; l < 3; l++)
					{
						if ((eptr[l] != nullptr) && (result == 0))
						{
							if ((speedlist[i] == int(eptr[l]->getcurrentSpeed())) && (eptr[l]->getatktarget() != -1) && (eptr[l]->getcurrentHealth() > 0))
							{
								for (int f = 0; f < 3; f++)
								{
									if (party[f] != nullptr)
									{
										if ((f == eptr[l]->getatktarget()) && (party[f]->getcurrentHealth()>0))
										{
											dmg = eptr[l]->attack(party[f]->getcurrentResistance());
											party[f]->takedmg(dmg);
											std::cout << eptr[l]->getname() << " attacked " << party[f]->getname() << " for " << int(dmg) << std::endl;
											eptr[l]->setatktarget(-1);
											if (party[f]->getcurrentHealth() == 0)
											{
												deadcompanion++;
												std::cout << party[f]->getname() << " has died" << std::endl;
											}
										}
										else if ((f == eptr[l]->getatktarget()) && (party[f]->getcurrentHealth() <= 0))
										{
											int difftarget = 0;
											while (difftarget == 0)
											{
												int newtarget = rand() % 3;
												if ((newtarget != f) && (party[newtarget] != nullptr))
												{
													eptr[l]->setatktarget(newtarget);
													difftarget++;
												}
												f--;
											}
										}
									}
								}
								if (deadcompanion == partysize)
								{
									result = 2;
								}
							}
						}
						if ((party[l] != nullptr) && (result == 0))
						{
							if ((speedlist[i] == int(party[l]->getcurrentSpeed())) && (party[l]->getatktarget() != -1) && (party[l]->getcurrentHealth() > 0))
							{
								for (int f = 0; f < 3; f++)
								{
									if (eptr[f] != nullptr)
									{
										if ((f == party[l]->getatktarget()) && (eptr[f]->getcurrentHealth()>0))
										{
											dmg = party[l]->attack(eptr[f]->getcurrentResistance());
											eptr[f]->takedmg(dmg);
											std::cout << party[l]->getname() << " attacked " << eptr[f]->getname() << " for " << int(dmg) << std::endl;
											party[l]->setatktarget(-1);
											if (eptr[f]->getcurrentHealth() == 0)
											{
												deadenemies++;
												std::cout << eptr[f]->getname() << " has died" << std::endl;
											}
										}
										else if ((f == party[l]->getatktarget()) && (eptr[f]->getcurrentHealth() <= 0))
										{
											int difftarget = 0;
											while (difftarget == 0)
											{
												int newtarget = rand() % 3;
												if ((newtarget != f) && (eptr[newtarget] != nullptr))
												{
													party[l]->setatktarget(newtarget);
													difftarget++;
												}
												f--;
											}
										}
									}
								}
								if (deadenemies == enemyno)
								{
									result = 1;
								}
							}
						}
					}
				}
			}
		}
		for (int i = 0; i < 3; i++)
		{
			if (party[i] != nullptr)
			{
				for (int l = 1; l < 5;l++)
					party[i]->resetstats(l);
			}
			if (eptr[i] != nullptr)
			{
				for (int l = 1; l < 5; l++)
					eptr[i]->resetstats(l);
			}
		}
		if (result == 2)
		{
			for (int i = 0; i < 3; i++)
			{
				if (sametype != 0)
				{
					if (party[i] != nullptr)
					{
						party[i]->removeresonace(sametype);
						party[i]->resetstats(5);
					}
				}	
			}
			std::cout << "You lost!" << std::endl;
			std::cout << "Tip: Upgrade your companions" << std::endl;
			std::cout << "" << std::endl;
			return p;
		}
		if (result == 1)
		{
			for (int i = 0; i < 3; i++)
			{
				if (sametype != 0)
				{
					if (party[i] != nullptr)
					{
						party[i]->removeresonace(sametype);
						party[i]->resetstats(5);
					}
				}
			}
			std::cout << "You won!" << std::endl;
			int exp = (bossno * 50 + minionno * 25)*difficulty;
			int coins = (bossno * 500 + minionno * 250)*difficulty;
			p.stagecleared(coins,exp);
			p.checklevelup();
			if (p.getplayerinfo(5) + 1 == stagepicked)
				p.clearednewstage();
			return p;
		}
	}
	return p;
}
int menu(Companion* cptr[10], player p, Companion*party[3],std::string namelist[10])
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
				std::cout << "0. Custom Stage" << std::endl;
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
					p=battle(party, cptr, p, choice);
					choice = 1;
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
	std::string fruits[3] = { "Apple","Banana","Watermelon" };
	std::string name;
	std::cout << "Enter your name: ";
	std::cin >> name;
	int fruit;
	for (int i = 0; i < 3; i++)
	{
		std::cout << i + 1 << ". " << fruits[i] << std::endl;
	}
	std::cout << "Choose your fruit: ";
	std::cin >> fruit;
	player p(name, fruits[fruit - 1]);
	srand((unsigned int)time(NULL));
	std::string namelist[10] = { "Lolipop","Honey","Cheese","Yogurt","Rice","Pasta","Fish","Mussels","Grapes","Strawberries" };
	Companion* cptr[10] = { nullptr,nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
	cptr[p.getplayerinfo(3)] = new Companion(3,namelist[2]);
	p.newcompanion();
	Companion* party[3] = { nullptr,nullptr,nullptr };
	int running = 0;
	while (running == 0)
	{
		int done = menu(cptr, p, party, namelist);
		if (done == 0)
			return 0;
	}
}