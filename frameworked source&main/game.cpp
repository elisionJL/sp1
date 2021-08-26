// This is the main file for the game logic and function
//
//
#include "Beet.h"
#include "Companion.h"
#include "Eggplant.h"
#include "Entity.h"
#include "Minion.h"
#include "player.h"
#include "SpinachBoss.h"
#include "Steak.h"
#include<string>
#include<algorithm>
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <sstream>

double  g_dElapsedTime;
double  g_dDeltaTime;
//menu data members
int choice = 1;
int backloop = 1;
int gachanum = 99;
int stageP = 0;//stage picked
bool battleStart = true;
//battle data members
std::string minionnames[6] = { "Cabbage" ,"Garlic","Onion","Peas","Mutton","Venison" };
std::string enemynames[5] = { "Spinach","Eggplant","Beet","Steak","Minion" };
int speedlist[6] = { -1,-1,-1,-1,-1,-1 };
int Cmove[3] = { 0,0,0 }, Ctarget[3] = { 0,0,0 }, Emove[3] = { 0,0,0 }, Etarget[3] = { 0,0,0 };
int Cturn = 0, Eturn = 0;
int friendlyAtks = 0, enemyAtks = 0;//counts the number of time the player and enemy has attacked, reset upon reaching alive entities of respective sides
int aliveC = 3, aliveE = 3;
bool moveChosen = true, targetChosen = true;
int result = 0, checkparty = 0, partysize = 3, enemyno = 0, bossno = 0, minionno = 0, deadcompanion = 0, deadenemies = 0, difficulty = 1, sametype = 0, allgood = 0;
double dmg = 0;
std::string e1, e2, e3, c1, c2, c3;

SKeyEvent g_skKeyEvent[K_COUNT];
std::string namelist[10] = { "Lolipop","Honey","Cheese","Yohgurt","Rice","Pasta","Fish","Mussels","Grapes","Strawberries" };
Companion* cptr[10] = { nullptr,nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
Companion* party[3] = { nullptr,nullptr,nullptr };
Entity* eptr[3] = { nullptr,nullptr,nullptr };
player p("Wapples", "Apple");

bool newC = false;
float summonC = 1500;
SGameChar   g_sChar;
EGAMESTATES g_eGameState = S_SPLASHSCREEN; // initial state

// Console object
Console g_Console(175, 35, "SP1 Framework");

void init(void)
{
	// Set precision for floating point output
	g_dElapsedTime = 0.0;
	// sets the initial state for the game
	g_eGameState = S_MENU;
	cptr[2] = new Companion(3, "Cheese");
	p.newcompanion();
	//////////////////////////////////////////////////////////////////////////////
	//for debugging cause part needs to be full
	cptr[1] = new Companion(2, "Honey");
	p.newcompanion();
	cptr[4] = new Companion(5, "Rice");
	p.newcompanion();

	// /////////////////////////////////////////////////////////////////////////////
	g_sChar.m_cLocation.X = g_Console.getConsoleSize().X / 2;
	g_sChar.m_cLocation.Y = g_Console.getConsoleSize().Y / 2;
	g_sChar.m_bActive = true;
	// sets the width, height and the font name to use in the console
	g_Console.setConsoleFont(0, 16, L"Consolas");

	// remember to set your keyboard handler, so that your functions can be notified of input events
	g_Console.setKeyboardHandler(keyboardHandler);
}

void shutdown(void)
{
	// Reset to white text on black background
	colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

	g_Console.clearBuffer();
}

void getInput(void)
{
	// resets all the keyboard events
	memset(g_skKeyEvent, 0, K_COUNT * sizeof(*g_skKeyEvent));
	// then call the console to detect input from user
	g_Console.readConsoleInput();
}

void keyboardHandler(const KEY_EVENT_RECORD& keyboardEvent)
{
	switch (g_eGameState)
	{
	case S_BATTLE:
		gameplayKBHandler(keyboardEvent);
		break;
	case S_MENU:                         // get keyboard input
		gameplayKBHandler(keyboardEvent);
		break;
	}
}


void gameplayKBHandler(const KEY_EVENT_RECORD& keyboardEvent)
{
	// here, we map the key to our enums
	EKEYS key = K_COUNT;
	switch (keyboardEvent.wVirtualKeyCode)
	{
	case VK_UP: key = K_UP; break;
	case VK_DOWN: key = K_DOWN; break;
	case VK_LEFT: key = K_LEFT; break;
	case VK_RIGHT: key = K_RIGHT; break;
	case VK_SPACE: key = K_SPACE; break;
	case VK_ESCAPE: key = K_ESCAPE; break;
	case VK_RETURN: key = K_ENTER; break;
	case 0x51: key = K_Q; break;
	}
	if (key != K_COUNT)
	{
		g_skKeyEvent[key].keyDown = keyboardEvent.bKeyDown;//true
		g_skKeyEvent[key].keyReleased = !keyboardEvent.bKeyDown;//false
	}
}



void update(double dt);



void splashScreenWait()    // waits for time to pass in splash screen
{
	if (g_dElapsedTime > 3.0) // wait for 3 seconds to switch to game mode, else do nothing
		g_eGameState = S_GAME;
}

void updateGame()       // gameplay logic
{
	processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
						// sound can be played here too.
}

void processUserInput()
{
	// quits the game if player hits the escape key
	if (g_skKeyEvent[K_ESCAPE].keyReleased)
		g_bQuitGame = true;
	else if (g_skKeyEvent[K_ENTER].keyReleased) {

	}
}

void render()
{
	clearScreen();      // clears the current screen and draw from scratch 
	switch (g_eGameState)
	{
	case S_MENU: renderMenuEvents(choice, backloop);
		break;
	case S_BATTLE: RenderBattleEvents(stageP);
		break;
	}
	renderFramerate();      // renders debug information, frame rate, elapsed time, etc   // renders status of input events
	renderToScreen();       // dump the contents of the buffer to the screen, one frame worth of game
}

void clearScreen()
{
	// Clears the buffer with this colour attribute
	g_Console.clearBuffer(0x1F);
}

void renderToScreen()
{
	// Writes the buffer to the console, hence you will see what you have written
	g_Console.flushBufferToConsole();
}

void renderFramerate()
{
	COORD c;
	// displays the framerate
	std::ostringstream ss;
	ss << std::fixed << std::setprecision(3);
	ss << 1.0 / g_dDeltaTime << "fps";
	c.X = g_Console.getConsoleSize().X - 9;
	c.Y = 0;
	g_Console.writeToBuffer(c, ss.str());

	// displays the elapsed time
	ss.str("");
	ss << g_dElapsedTime << "secs";
	c.X = 0;
	c.Y = 0;
	g_Console.writeToBuffer(c, ss.str(), 0x59);
}

void renderMenuEvents(int choice, int screen) {
	COORD startPos = { 0, 1 };
	std::ostringstream ss;
	std::string key;
	ss.str("");
	std::string stages[4] = { "I'm not going to just spin around and leave!", "That went eggcellently well","No time to beet about the bush","Everything at steak" };
	g_Console.writeToBuffer(22, 0, " _______  ___      _______  __    _  ______   _______  ______      __   __  _______  __    _  _______  __   __  ______    _______ ", 91, 131);
	g_Console.writeToBuffer(22, 1, "|  _    ||   |    |       ||  |  | ||      | |       ||    _ |    |  | |  ||       ||  |  | ||       ||  | |  ||    _ |  |       |", 91, 131);
	g_Console.writeToBuffer(22, 2, "| |_|   ||   |    |    ___||   |_| ||  _    ||    ___||   | ||    |  |_|  ||    ___||   |_| ||_     _||  | |  ||   | ||  |    ___|", 91, 131);
	g_Console.writeToBuffer(22, 3, "|       ||   |    |   |___ |       || | |   ||   |___ |   |_||_   |       ||   |___ |       |  |   |  |  |_|  ||   |_||_ |   |___ ", 91, 131);
	g_Console.writeToBuffer(22, 4, "|  _   | |   |___ |    ___||  _    || |_|   ||    ___||    __  |  |       ||    ___||  _    |  |   |  |       ||    __  ||    ___|", 91, 131);
	g_Console.writeToBuffer(22, 5, "| |_|   ||       ||   |___ | | |   ||       ||   |___ |   |  | |   |     | |   |___ | | |   |  |   |  |       ||   |  | ||   |___ ", 91, 131);
	g_Console.writeToBuffer(22, 6, "|_______||_______||_______||_|  |__||______| |_______||___|  |_|    |___|  |_______||_|  |__|  |___|  |_______||___|  |_||_______|", 91, 131);
	getInput();
	switch (screen) {
	case 1://start screen

		ss << "Prompt: " << choice;
		g_Console.writeToBuffer(78, 10, "1. Start Game", 91, 14);
		g_Console.writeToBuffer(81, 13, "2. Quit", 91, 8);
		g_Console.writeToBuffer(80, 15, ss.str(), 91, 9);
		break;
	case 99:
		g_Console.writeToBuffer(78, 18, "See you next time!", 0x17);
		break;
	case 2://actual menu
		ss.str("");
		ss << "press esc to go back                                      Player Level: " << p.getplayerinfo(1);
		g_Console.writeToBuffer(22, 9, ss.str(), 91);
		g_Console.writeToBuffer(22, 10, "##################################################################################################################################", 91, 131);
		g_Console.writeToBuffer(22, 11, "#                                                              #                                                                 #", 91, 131);
		g_Console.writeToBuffer(22, 12, "#                                                              #                                                                 #", 91, 131);
		g_Console.writeToBuffer(22, 13, "#                                                              #                                                                 #", 91, 131);
		g_Console.writeToBuffer(22, 14, "#                        1. Stages                             #                                2. Party                         #", 91, 131);
		g_Console.writeToBuffer(22, 15, "#                                                              #                                                                 #", 91, 131);
		g_Console.writeToBuffer(22, 16, "#                                                              #                                                                 #", 91, 131);
		g_Console.writeToBuffer(22, 17, "#                                                                                                                                #", 91, 131);
		ss.str("");
		ss << "############################################################## " << choice << " #################################################################";
		g_Console.writeToBuffer(22, 18, ss.str(), 91, 131);
		g_Console.writeToBuffer(22, 19, "#                                                                                                                                #", 91, 131);
		g_Console.writeToBuffer(22, 20, "#                                                              #                                                                 #", 91, 131);
		g_Console.writeToBuffer(22, 21, "#                                                              #                                                                 #", 91, 131);
		g_Console.writeToBuffer(22, 22, "#                        3. Companions                         #                              4. Summon                          #", 91, 131);
		g_Console.writeToBuffer(22, 23, "#                                                              #                                                                 #", 91, 131);
		g_Console.writeToBuffer(22, 24, "#                                                              #                                                                 #", 91, 131);
		g_Console.writeToBuffer(22, 25, "#                                                              #                                                                 #", 91, 131);
		g_Console.writeToBuffer(22, 26, "##################################################################################################################################", 91, 131);
		break;
	case 3://stages
		g_Console.writeToBuffer(42, 10, "#####################################################################################", 91);
		for (int i = 10; i < 26; i++) {
			g_Console.writeToBuffer(42, 1 + i, "#                                                                                    #", 91);
		}
		g_Console.writeToBuffer(42, 26, "#####################################################################################", 91);
		g_Console.writeToBuffer(82, 12, "Stages:", 0x17);
		for (int i = 0; i <= p.getplayerinfo(5); i++)
		{
			ss.str("");
			ss << i + 1 << ". " << stages[i];
			g_Console.writeToBuffer(52, 15 + (i * 2), ss.str(), 0x17);
		}

			case 4://set up party
		{
			ss.str("");
			ss << "press esc to go back                                      Player Level: " << p.getplayerinfo(1);
			g_Console.writeToBuffer(28, 10, "                                                           ________________________ MEMEBERS ________________________", 91, 131);
			g_Console.writeToBuffer(28, 11, "######################## TEAM DECK ########################                                                         |", 91, 131);
			g_Console.writeToBuffer(28, 12, "#                                                         #                                                         |", 91, 131);
			g_Console.writeToBuffer(28, 13, "#  IN TEAM:                                               #                                                         |", 91, 131);
			ss.str("");
			ss << "#                                                         #      " << pos1 << "    " << pos2 << "    " << pos3 << "    " << pos4 << "    " << pos5 << "    " << pos6 << "    " << pos7 << "    " << pos8 << "    " << pos9 << "    " << pos10 << "     |";
			g_Console.writeToBuffer(28, 14, ss.str(), 91, 131);
			g_Console.writeToBuffer(28, 15, "#                                                         #                                                         |", 91, 131);
			g_Console.writeToBuffer(28, 16, "#           A:                                            #                                                         |", 91, 131);
			g_Console.writeToBuffer(28, 17, "#                                                         #_________ type member's alphabet to view member _________|", 91, 131);
			g_Console.writeToBuffer(28, 18, "#                                                         #                                                         |", 91, 131);
			g_Console.writeToBuffer(28, 19, "#                                                         #                                                         |", 91, 131);
			ss.str("");
			ss << "#           B:                                            #    HP: " << statHP << "                                               |";
			g_Console.writeToBuffer(28, 20, ss.str(), 91, 131);
			g_Console.writeToBuffer(28, 21, "#                                                         #                                                         |", 91, 131);
			ss.str("");
			ss << "#                                                         #    ATK: " << statATK << "                                              |";
			g_Console.writeToBuffer(28, 22, ss.str(), 91, 131);
			g_Console.writeToBuffer(28, 23, "#                                                         #                                                         |", 91, 131);
			ss.str("");
			ss << "#           C:                                            #    DEF: " << statDEF << "                                              |";
			g_Console.writeToBuffer(28, 24, ss.str(), 91, 131);
			g_Console.writeToBuffer(28, 25, "#                                                         #                                                         |", 91, 131);
			g_Console.writeToBuffer(28, 26, "#                                                         #                                                         |", 91, 131);
			g_Console.writeToBuffer(28, 27, "#                                                         #                                                         |", 91, 131);
			g_Console.writeToBuffer(28, 28, "#                                                         #                                                         |", 91, 131);
			g_Console.writeToBuffer(28, 29, "################ ...or type 'quit' to exit ################_________________________________________________________|", 91, 131);



			break;
		}
		case 5://library
		{

			g_Console.writeToBuffer(28, 10, " _______________________ LIBRARY ________________________ __________________________ INFO __________________________ ", 91, 131);
			g_Console.writeToBuffer(28, 11, "||                                                       #                                                         ||", 91, 131);
			g_Console.writeToBuffer(28, 12, "||   - Fish                                              #                                                         ||", 91, 131);
			ss.str("");
			ss << "||                                                       #    HP: " << healthUnit << "                                               ||";
			g_Console.writeToBuffer(28, 13, ss.str(), 91, 131);
			g_Console.writeToBuffer(28, 14, "||   - Grapes                                            #                                                         ||", 91, 131);
			ss.str("");
			ss << "||                                                       #    ATK: " << attackUnit << "                                               ||";
			g_Console.writeToBuffer(28, 15, ss.str(), 91, 131);
			g_Console.writeToBuffer(28, 16, "||   - Honey                                             #                                                         ||", 91, 131);
			ss.str("");
			ss << "||                                                       #    DEF: " << defenceUnit << "                                               ||";
			g_Console.writeToBuffer(28, 17, ss.str(), 91, 131);
			g_Console.writeToBuffer(28, 18, "||   - Mussels                                           #                                                         ||", 91, 131);
			ss.str("");
			ss << "||                                                       #    SPD: " << speedUnit << "                                               ||";
			g_Console.writeToBuffer(28, 19, ss.str(), 91, 131);
			g_Console.writeToBuffer(28, 20, "||   - Cheese                                            #                                                         ||", 91, 131);
			ss.str("");
			ss << "||                                                       #    BONUS: " << defenceUnit << "                                             ||";
			g_Console.writeToBuffer(28, 21, ss.str(), 91, 131);
			g_Console.writeToBuffer(28, 22, "||   - Pasta                                             #                                                         ||", 91, 131);
			g_Console.writeToBuffer(28, 23, "||                                                       #                                                         ||", 91, 131);
			g_Console.writeToBuffer(28, 24, "||   - Rice                                              #                                                         ||", 91, 131);
			g_Console.writeToBuffer(28, 25, "||                                                       #                                                         ||", 91, 131);
			g_Console.writeToBuffer(28, 26, "||   - Strawberry                                        #                                                         ||", 91, 131);
			g_Console.writeToBuffer(28, 27, "||                                                       #                                                         ||", 91, 131);
			g_Console.writeToBuffer(28, 28, "||   - Yoghurt                                           #                                                         ||", 91, 131);
			g_Console.writeToBuffer(28, 29, "||                                                       #                                                         ||", 91, 131);
			g_Console.writeToBuffer(28, 30, "||____________________________________________ ...or hit 'esc' to exit ____________________________________________||", 91, 131);
			


			break;
		}
	case 6://gacha
		g_Console.writeToBuffer(80, 9, "> SUMMON <",91);
		for (int i = 10; i < 25; i++) {
			g_Console.writeToBuffer(42, 1 + i, "#                                                                                    #", 91);
		}
		g_Console.writeToBuffer(42, 10, "#####################################################################################", 91);
		g_Console.writeToBuffer(42, 14, "############################### press q to summon ###################################", 91);
		g_Console.writeToBuffer(42, 26, "#####################################################################################", 91);
		ss << "summon cost: 1500";
		g_Console.writeToBuffer(72, 12, ss.str(), 91);
		ss.str("");
		ss << "Coins: " << p.getplayerinfo(4);
		g_Console.writeToBuffer(78, 11, ss.str(), 91);
		if (gachanum == 0) {//for when user does not have enough coins
			g_Console.writeToBuffer(58, 13, "You do not have enough coins", 91);
		}
		if (gachanum > 0 && gachanum < 11) {
			if (cptr[gachanum -  1] == nullptr) {
				cptr[gachanum - 1 ] = new Companion(gachanum, namelist[gachanum - 1]);
				p.newcompanion();
				newC = true;
				ss.str("");
				ss << "You summoned " << namelist[gachanum - 1] << "!";
				g_Console.writeToBuffer(68, 16, ss.str(), 91);
			}
			else {
				newC = false;
			}
			if (newC == false) {
				for (int i = 0; i < 10; i++)//to check for dupes
				{
					if (cptr[i] != nullptr)
					{
						if (gachanum == cptr[i]->getid())
						{
							ss.str("");
							ss << "You summoned another " << namelist[gachanum - 1] << "!";
							g_Console.writeToBuffer(68, 16, ss.str(), 91);
							ss.str("");
							ss << namelist[gachanum - 1] << "'s Enhanced Level has increased";
							g_Console.writeToBuffer(68, 18, ss.str(), 91);
							cptr[i]->summonedagain();
						}
					}
				}
			}
		}
	}
}

// this is an example of how you would use the input events

void story(int x, int y)
{

}
void setparty(Companion* cptr[10], player p, Companion* party[3])
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
				if ((party[l] == cptr[companionchoice - 1]) && (companionchoice != p.getplayerinfo(3) + 1))
				{
					std::cout << "Cannot use the same party members" << std::endl;
					i--;
					errorcheck++;
				}
			}
			if ((errorcheck == 0) && (companionchoice != p.getplayerinfo(3) + 1))
			{
				party[i] = cptr[companionchoice - 1];
			}
		}
		int checkmembers = 0;
		for (int i = 0; i < 3; i++)
		{
			if (party[i] != nullptr)
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
			std::cout << "Coins: " << p.getplayerinfo(4) << std::endl;
			std::cout << "Name: " << cptr[choice]->getname() << std::endl;
			std::cout << "Level: " << cptr[choice]->getlvl() << std::endl;
			std::cout << "Health: " << int(cptr[choice]->getHealth()) << std::endl;
			std::cout << "Attack: " << int(cptr[choice]->getDamage()) << std::endl;
			std::cout << "Defence: " << int(cptr[choice]->getResistance()) << std::endl;
			std::cout << "Speed: " << int(cptr[choice]->getSpeed()) << std::endl;
			std::cout << "Skill: " << cptr[choice]->getMoveName(3) << std::endl;
			std::cout << "Enhanced Level: " << cptr[choice]->gettimespulled() - 1 << std::endl;
			std::cout << "" << std::endl;
			std::cout << "1. Upgrade (" << cptr[choice]->getupgradecost() << " coins)" << std::endl;
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
int summon()
{
	for (int i = 0; i < 17; i++) {
		if (i != 14) {
			g_Console.writeToBuffer(42, 1 + i, "#                                                                                    #", 91);
		}
	}
	if (p.getplayerinfo(4) < summonC)
	{
		return 0;
	}
	else if (p.getplayerinfo(4) >= summonC)
	{
		p.gacha();
		std::cout << "" << std::endl;
		int pull = rand() % 10 + 1;
		return pull;
	}
	return 0;
}
void RenderBattleEvents(int stagepicked) {
	ostringstream ss;
	std::string minionnames[6] = { "Cabbage" ,"Garlic","Onion","Peas","Mutton","Venison" };
	std::string enemynames[5] = { "Spinach","Eggplant","Beet","Steak","Minion" };
	if (battleStart == true) {
		std::string difficulties[5] = { "1. Easy" ,"2. Normal","3. Hard",  "4. Extreme", "5. Death" };
		g_Console.writeToBuffer(22, 0, " _______  ___      _______  __    _  ______   _______  ______      __   __  _______  __    _  _______  __   __  ______    _______ ", 91, 131);
		g_Console.writeToBuffer(22, 1, "|  _    ||   |    |       ||  |  | ||      | |       ||    _ |    |  | |  ||       ||  |  | ||       ||  | |  ||    _ |  |       |", 91, 131);
		g_Console.writeToBuffer(22, 2, "| |_|   ||   |    |    ___||   |_| ||  _    ||    ___||   | ||    |  |_|  ||    ___||   |_| ||_     _||  | |  ||   | ||  |    ___|", 91, 131);
		g_Console.writeToBuffer(22, 3, "|       ||   |    |   |___ |       || | |   ||   |___ |   |_||_   |       ||   |___ |       |  |   |  |  |_|  ||   |_||_ |   |___ ", 91, 131);
		g_Console.writeToBuffer(22, 4, "|  _   | |   |___ |    ___||  _    || |_|   ||    ___||    __  |  |       ||    ___||  _    |  |   |  |       ||    __  ||    ___|", 91, 131);
		g_Console.writeToBuffer(22, 5, "| |_|   ||       ||   |___ | | |   ||       ||   |___ |   |  | |   |     | |   |___ | | |   |  |   |  |       ||   |  | ||   |___ ", 91, 131);
		g_Console.writeToBuffer(22, 6, "|_______||_______||_______||_|  |__||______| |_______||___|  |_|    |___|  |_______||_|  |__|  |___|  |_______||___|  |_||_______|", 91, 131);
		g_Console.writeToBuffer(42, 10, "#################################################$####################################", 91);
		for (int i = 0; i < 16; i++) {
			g_Console.writeToBuffer(42, 11+i, "#                                                                                    #", 91);
		}
		g_Console.writeToBuffer(42, 26, "######################################################################################", 91);
		g_Console.writeToBuffer(80, 12, "DIFFICULTIES", 91);
		for (int i = 0; i < 5; i++) {
			ss.str("");
			ss << difficulties[i];
			g_Console.writeToBuffer(81, 15 + (i * 2), ss.str(), 91);
		}
		ss.str("");
		ss << choice;
		g_Console.writeToBuffer(84, 25, ss.str(), 91);
	}
	else if (battleStart == false) {
		e1 = eptr[0]->getname(); c1 = namelist[party[0]->getid() - 1]; c2 = namelist[party[1]->getid() - 1]; c3 = namelist[party[2]->getid() - 1];
		if (eptr[1] != nullptr || eptr[2] != nullptr) {
			e2 = eptr[1]->getname(); e3 = eptr[2]->getname();
		}
		else {
			e2 = " "; e3 = " ";
		}
		g_Console.writeToBuffer(50, 2, c1[0], 243); g_Console.writeToBuffer(120, 2, e1[0], 192);
		g_Console.writeToBuffer(50, 4, c2[0], 243); g_Console.writeToBuffer(120, 4, e2[0], 192);
		g_Console.writeToBuffer(50, 6, c3[0], 243); g_Console.writeToBuffer(120, 6, e3[0], 192);
		g_Console.writeToBuffer(22, 10, "##################################################################################################################################", 91, 131);
		for (int i = 0; i < 19; i++) {
			g_Console.writeToBuffer(22, 11 + i, "#                                                                                                                                #", 91, 131);
		}
		ss.str("");
		ss << "############################################################### " << choice << " ################################################################";
		g_Console.writeToBuffer(22, 30, ss.str(), 91, 131);
		for (int i = 0; i < 19; i++) {
			g_Console.writeToBuffer(60, 11 + i, "#                                                  #", 91, 131);
		}
		for (int i = 0; i < 10; i++) {
			g_Console.writeToBuffer(85, 11+i, "##", 91);
		}
		g_Console.writeToBuffer(60, 20, "##################################################", 91); /*g_Console.writeToBuffer(110, 20, "########################################", 91);*/
		g_Console.writeToBuffer(63, 15, "1. Attack", 91); g_Console.writeToBuffer(89, 15, "2.defend", 91); g_Console.writeToBuffer(76, 25, "3." + party[Cturn]->getMoveName(3), 91);
		if (Cturn > 3) {
			Cturn = 0;
		}
		g_Console.writeToBuffer(49, 2 + (Cturn * 2), ">", 91);
		if (targetChosen == false && moveChosen == true) {
			g_Console.writeToBuffer(121, choice * 2, "<", 91);
		}
		//render enemies and companions
		ss.str("");
		ss << c1[0] << " hp: " << party[0]->getcurrentHealth() << " / " << party[0]->getHealth();
		g_Console.writeToBuffer(24, 12, ss.str(), 91);
		ss.str("");
		ss << c2[0] << " hp: " << party[1]->getcurrentHealth() << " / " << party[1]->getHealth();
		g_Console.writeToBuffer(24, 16, ss.str(), 91);
		ss.str("");
		ss << c3[0] << " hp: " << party[2]->getcurrentHealth() << " / " << party[2]->getHealth();
		g_Console.writeToBuffer(24, 20, ss.str(), 91);
		ss.str("");
		ss << e1[0] << " hp: " << eptr[0]->getcurrentHealth() << " / " << eptr[0]->getHealth();
		g_Console.writeToBuffer(112, 12, ss.str(), 91);
		if (stagepicked != 1) {
			ss.str("");
			ss << e2[0] << " hp: " << eptr[1]->getcurrentHealth() << " / " << eptr[1]->getHealth();
			g_Console.writeToBuffer(112, 16, ss.str(), 91);
			ss.str("");
			ss << e3[0] << " hp: " << eptr[2]->getcurrentHealth() << " / " << eptr[2]->getHealth();
			g_Console.writeToBuffer(112, 20, ss.str(), 91);
		}
		else {

		}
	}
}		
player battle(int stagepicked)
{
	for (int i = 0; i < 3; i++)
	{
		if (party[i] == nullptr)
		{
			checkparty++;
		}
	}
	if (checkparty == 3)
	{
		backloop = 4;
		g_eGameState = S_MENU;
		menu();
		return p;
	}
	else {
		checkparty = 0;
	}
	if (stagepicked != 0)//select difficulty
	{
		if (battleStart == true) {
			getInput();
			if (g_skKeyEvent[K_UP].keyReleased && choice != 1) {
				choice--;
			}
			if (g_skKeyEvent[K_DOWN].keyReleased && choice != 5) {
				choice++;
			}
			if (g_skKeyEvent[K_ENTER].keyReleased) {
				difficulty = choice;
				choice = 1;
				battleStart = false;
			}
		}
	}
	
	if (battleStart == false) {
		for (int i = 0; i < 3; i++)//resonance buff
		{
			if (party[i] != nullptr)
			{
				for (int l = 0; l < 3; l++)
				{
					if ((party[l] != nullptr) && (party[l] != party[i]))
					{
						if (party[l]->buff() == party[i]->buff())
						{
							sametype = party[l]->buff();
							l += 3; i += 3;
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
				party[i]->resetstats(5);
			}
		}
		aliveC = 0; aliveE = 0;
		for (int i = 0; i < 3; i++) {
			if (party[i]->getcurrentHealth() > 0) {
				aliveC++;
			}
			else {
				party[i]->setcurrentHealth(0);
			}
			if (eptr[i] != nullptr) {
				if (eptr[i]->getcurrentHealth() > 0) {
					aliveE++;

				}
				else {
					eptr[i]->setcurrentHealth(0);
				}
			}
		}
		if (result == 0)//result will become 1 when the battle ends
		{
			//companion move
			if (Cturn < 2)//friendly attack
			{
				if (party[Cturn]->getcurrentHealth() < 1) {
					Cmove[Cturn] = NULL;
					Ctarget[Cturn] = NULL;
					Cturn++;
				}
				//user chooses move
				if (party[Cturn]->getcurrentHealth() > 0 && moveChosen == false)
				{
					targetChosen = true;
					getInput();//choose move
					if (g_skKeyEvent[K_UP].keyReleased && choice != 1) {
						choice--;
					}
					if (g_skKeyEvent[K_DOWN].keyReleased && choice != 3) {
						choice++;
					}
					if (g_skKeyEvent[K_ENTER].keyReleased) {
						Cmove[Cturn] = choice;
						choice = 1;
						moveChosen = true;
						targetChosen = false;
						if (Cmove[Cturn] == 3) {
							if (party[Cturn]->getskillcd() == 0)
							{
								int skillused = party[Cturn]->skill();//triggers buff but returns 1 if choice 3rd move is debuff
								if (skillused == 1) {//fulfill target condition
									moveChosen = true;
									targetChosen = false;
								}
								else {
									moveChosen = false;//so that after buff, user can pick atk or defend
									targetChosen = true;
								}
								if (Cmove[Cturn] == 2) {
									moveChosen = false;
									targetChosen = true;
									party[Cturn]->block();
									Ctarget[Cturn] = NULL;
									Cturn++;
								}
							}
							party[Cturn]->setskillcd(4);
						}
					}
				}

				//user chooses target
				if (party[Cturn]->getcurrentHealth() > 0 && targetChosen == false && Cmove[Cturn] != 2)
				{
					getInput();//choose move
					if (g_skKeyEvent[K_UP].keyReleased && choice != 1) {
						choice--;
					}
					if (g_skKeyEvent[K_DOWN].keyReleased && choice != 3) {
						choice++;
					}
					if (g_skKeyEvent[K_ENTER].keyReleased && eptr[choice - 1] != nullptr && eptr[choice - 1]->getcurrentHealth() > 0) {

						if (Cmove[Cturn] == 3) {
							eptr[choice]->setcurrentDamage(eptr[choice]->getcurrentDamage() * 0.85);
							eptr[choice]->setcurrentResistance(eptr[choice]->getcurrentResistance() * 0.85);
							eptr[choice]->setcurrentSpeed(eptr[choice]->getcurrentSpeed() * 0.85);
							moveChosen = false;
							targetChosen = true;
							choice = 1;
						}
						else {
							Ctarget[Cturn] = choice;
							moveChosen = true;
							targetChosen = true;
							choice = 1;
						}
					}
				}
				//move takes effect
				if (party[Cturn]->getcurrentHealth() > 0 && targetChosen == true && moveChosen == true) {
					switch (Cmove[Cturn]) {
					case 1:
						party[Cturn]->setatktarget(Ctarget[Cturn]);
						moveChosen = false;
						targetChosen = true;
						friendlyAtks++;
						Cturn++;
						break;
					}

				}
				if (friendlyAtks == 3) {
					moveChosen = true;
					targetChosen = true;
				}
			}
			//enemy moves
			if (Eturn < 2 && Cturn == 2) {
				//for null or dead enemies
				if (party[Cturn]->getcurrentHealth() < 1 || eptr[Eturn] == nullptr) {
					Emove[Cturn] = NULL;
					Etarget[Cturn] = NULL;
					Eturn++;
				}
				if ((eptr[Eturn] != nullptr) && (result == 0))
				{
					if (eptr[Eturn]->getcurrentHealth() > 0)
					{
						//for minions
						if (Eturn > 0) {
							Emove[Eturn] = rand() % 3 + 1;
							if (Emove[Eturn] == 2) {
								eptr[Eturn]->block();
								Etarget[Eturn] = NULL;
								Eturn++;
							}
							else if (Emove[Eturn] == 3) {
								if (eptr[Eturn]->getskillcd() == 0) {
									int skillused = rand() % 4 + 1;
									eptr[Eturn]->skill(skillused);
									eptr[Eturn]->setskillcd(4);
								}
							}
							else if (Emove[Eturn] == 1) {
								eptr[Eturn]->setatktarget(Etarget[Eturn]);
								Eturn++;
							}
						}
						//for bosses
						if (Eturn == 0) {
							do {
								Etarget[0] = rand() % 2;
							} while (party[Etarget[0]] != nullptr && party[Etarget[0]]->getcurrentHealth() < 1);
							Emove[0] = rand() % 3 + 1;
							switch (Emove[0])
							{
							case 1://attack
								eptr[Eturn]->setatktarget(Etarget[0]);
								Eturn++;
								break;
							case 2://defend
								eptr[Eturn]->block();
								Eturn++;
								break;
							case 3:
								if (eptr[Eturn]->getskillcd() == 0)
								{
									int whichskill;
									int skillused;
									if (eptr[Eturn]->getname() == "Steak")
										whichskill = rand() % 5 + 1;
									else
										whichskill = rand() % 4 + 1;
									skillused = eptr[Eturn]->skill(whichskill);
									switch (skillused)
									{
									case 1:
										std::cout << eptr[Eturn]->getname() << " used " << eptr[Eturn]->getMoveName(1) << std::endl;
										for (int l = 0; l < 3; l++)
										{
											if (party[l] != nullptr)
											{
												if (party[l]->getcurrentHealth() > 0)
												{
													dmg = eptr[Eturn]->attack(party[l]->getcurrentResistance());
													party[l]->takedmg(dmg);
													if (party[l]->getcurrentHealth() < 1)
													{
														deadcompanion++;
														party[l]->setcurrentHealth(-1);
													}
												}
											}
										}
										if (deadcompanion == partysize)
										{
											result = 2;//lose
										}
										break;
									case 2:
										dmg = eptr[Eturn]->attack(party[Etarget[0]]->getcurrentResistance());
										party[Etarget[0]]->takedmg(dmg);
										if (party[Etarget[0]]->getcurrentHealth() < 0)
										{
											deadcompanion++;
											party[Etarget[0]]->setcurrentHealth(0);
										}
										if (deadcompanion == partysize)
										{
											result = 2;
										}
										break;
									case 3:
										party[Etarget[0]]->setcurrentResistance(party[Etarget[0]]->getcurrentResistance() * 0.3);
										break;
									case 4:
										for (int l = 0; l < 3; l++)
										{
											if (party[l] != 0)
											{
												int statdecrease = rand() % 3 + 1;
												if (statdecrease == 1)
													party[Etarget[0]]->setcurrentDamage(party[Etarget[0]]->getcurrentDamage() * 0.8);
												if (statdecrease == 2)
													party[Etarget[0]]->setcurrentResistance(party[Etarget[0]]->getcurrentResistance() * 0.8);
												if (statdecrease == 1)
													party[Etarget[0]]->setcurrentSpeed(party[Etarget[0]]->getcurrentSpeed() * 0.8);
											}
										}
										break;
									case 5:
										party[Etarget[0]]->setcurrentDamage(cptr[Etarget[0]]->getcurrentDamage() * 0.3);
										break;
									case 0:
										break;
									}
								}
								eptr[Eturn]->setskillcd(4);
							}
						}
					}
				}

			}
		}
		if (Cturn == 2 && Eturn == 2) {
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
				std::sort(speedlist, speedlist + 6, greater<int>());//sort array according to speed
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
											if ((f == eptr[l]->getatktarget()) && (party[f]->getcurrentHealth() > 0))
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
											if ((f == party[l]->getatktarget()) && (eptr[f]->getcurrentHealth() > 0))
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
					for (int l = 1; l < 5; l++)
						party[i]->resetstats(l);
				}
				if (eptr[i] != nullptr)
				{
					for (int l = 1; l < 5; l++)
						eptr[i]->resetstats(l);
				}
			}
			if (friendlyAtks == 3 && enemyAtks ==3)
			{
				choice = 1;
				friendlyAtks = 0; enemyAtks = 0;
				Cturn = 0;
				Eturn = 0;
				moveChosen = false;
				targetChosen = true;
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
				g_eGameState = S_BATTLEN;
				std::cout << "You won!" << std::endl;
				int exp = (bossno * 50 + minionno * 25) * difficulty;
				int coins = (bossno * 500 + minionno * 250) * difficulty;
				p.stagecleared(coins, exp);
				p.checklevelup();
				if (p.getplayerinfo(5) + 1 == stagepicked)
					p.clearednewstage();
				return p;
			}
			return p;
		}
	}
	return p;
}
int menu()
{
	cls();
	//int menuloop = 0;
	//while (menuloop == 0)
	//{
	switch (backloop)
	{
	case 1://start screen
		getInput();
		if (g_skKeyEvent[K_UP].keyReleased) {
			choice--;
		}
		else if (g_skKeyEvent[K_DOWN].keyReleased) {
			choice++;
		}
		if (choice < 1) {
			choice = 1;
		}
		if (choice > 2) {
			choice = 2;
		}
		if (g_skKeyEvent[K_ENTER].keyReleased) {
			if (choice == 2)//quit
			{
				backloop = 99;
				g_bQuitGame = true;
				return 0;
			}
			else {
				backloop++;
				choice = 1;
			}
		}
		break;
	case 2://menu choices
		getInput();
		if (g_skKeyEvent[K_UP].keyReleased) {
			choice--;
		}
		else if (g_skKeyEvent[K_DOWN].keyReleased) {
			choice++;
		}
		if (choice < 1) {
			choice = 1;
		}
		if (choice > 4) {
			choice = 4;
		}
		if (g_skKeyEvent[K_ENTER].keyReleased) {
			backloop = backloop + choice;
			choice = 1;
		}
		if (g_skKeyEvent[K_ESCAPE].keyReleased) {
			backloop = 1;
		}
		break;
	case 3:
		getInput();
		if (g_skKeyEvent[K_UP].keyReleased && choice != 1) {
			choice--;
		}
		else if (g_skKeyEvent[K_DOWN].keyReleased && choice != p.getplayerinfo(5)) {
			choice++;
		}
		if (g_skKeyEvent[K_ESCAPE].keyReleased) {
			backloop = 2;
			choice = 1;
		}
		if (g_skKeyEvent[K_ENTER].keyReleased) {
			stageP = choice;

			result = 0; checkparty = 0; partysize = 0; enemyno = 0; bossno = 0; minionno = 0; deadcompanion = 0; deadenemies = 0; difficulty = 1; sametype = 0; allgood = 0;
			dmg = 0;
			//for debugging
			party[0] = cptr[1]; party[1] = cptr[2]; party[2] = cptr[4];
			for (int i = 0; i < 3;i ++){///sets all enemy pointers to null when battle first starts
				eptr[i] = { nullptr };
				Cmove[i] = 0;
				Ctarget[i] = 0;
				Emove[i] = 0;
				Etarget[i] = 0;
				party[i]->setcurrentHealth(party[i]->getHealth());
			}
			switch (stageP)
			{
			case 1://stage 1
				eptr[0] = new SpinachBoss(5 * difficulty); enemyno++; bossno++; eptr[1] = nullptr; eptr[2] = nullptr;
				break;
			case 2://stage 2
				eptr[0] = new Eggplant(10 * difficulty); eptr[1] = new Minion(10 * difficulty, minionnames[0]); eptr[2] = new Minion(10 * difficulty, minionnames[1]); enemyno += 3; bossno++; minionno += 2;
				break;
			case 3://stage 3
				eptr[0] = new Beet(15 * difficulty); eptr[1] = new Minion(15 * difficulty, minionnames[2]); eptr[2] = new Minion(15 * difficulty, minionnames[3]); enemyno += 3; bossno++; minionno += 2;
				break;
			case 4://stage 4
				eptr[0] = new Steak(20 * difficulty); eptr[1] = new Minion(20 * difficulty, minionnames[4]); eptr[2] = new Minion(20 * difficulty, minionnames[5]); enemyno += 3; bossno++; minionno += 2;
				break;
			}
			Cturn = 0, Eturn = 0;
			friendlyAtks = 0, enemyAtks = 0;//counts the number of time the player and enemy has attacked, reset upon reaching alive entities of respective sides
			aliveC = 3, aliveE = 0;
			moveChosen = false, targetChosen = true;
			battleStart = true;
			g_eGameState = S_BATTLE;
			choice = 1;
		}
		break;
	case 4://set up party
		for (int i = 0; i < 3; i++)
			party[i] = 0;
		setparty(cptr, p, party);
		std::cout << "" << std::endl;
		getInput();
		if (g_skKeyEvent[K_ESCAPE].keyReleased) {
			backloop = 2;
			choice = 1;
		}
		break;
	case 5://library
		break;
	case 6://gacha
		getInput();
		if (g_skKeyEvent[K_ESCAPE].keyReleased) {
			backloop = 2;
			choice = 1;
		}
		if (g_skKeyEvent[K_Q].keyReleased) {
			gachanum = summon();
		}
		//if (choice == 3)
		//{
		//	int upgrademenu = enhancecompanion(p, cptr);
		//	if (upgrademenu == 0)
		//	{
		//		backloop--;
		//	}
		//}

	}
	return 0;
}

void update(double dt)
{
	// get the delta time
	g_dElapsedTime += dt;
	g_dDeltaTime = dt;

	switch (g_eGameState)
	{
	case S_BATTLE:
		p = battle(stageP);
		break;
	case S_BATTLEN:
		g_eGameState = S_MENU;
		break;
	case S_MENU:
		menu();
		break;
	}
}
