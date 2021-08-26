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
bool Qpressed;
int stageP = 0;//stage picked
bool battleStart = true;
/////////////////////////////////////////////// vv library/deck data members vv ///////////////////////////////////////////////

std::string  pos1, pos2, pos3, pos4, pos5, pos6, pos7, pos8, pos9, pos10;
int healthUnit = 42;
int attackUnit;
std::string foodChar[11] = { "L", "H", "C", "Y", "R", "P", "F", "M", "G", "S", "?" };
int defenceUnit;
int speedUnit;
std::string bonus;
int statHP, statDEF, statATK;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

bool nextstoryline;
bool gottobattle;
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
	case S_BATTLEN:
		gameplayKBHandler(keyboardEvent);
	case S_BATTLE:
		gameplayKBHandler(keyboardEvent);
		break;
	case S_MENU:                         // get keyboard input
		gameplayKBHandler(keyboardEvent);
		break;
	case S_BEFOREBATTLEN:
		gameplayKBHandler(keyboardEvent);
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

void storyafter(int stageP)
{
	switch (stageP)
	{
	case 1:
		renderstorylinestage1act2(20, 13);
		break;
	case 2:
		renderstorylinestage2act2(20, 13);
		break;
	case 3:
		renderstorylinestage3act2(20, 13);
		break;
	case 4:
		renderstorylinestage4act2(20, 13);
		break;
	}
	g_Console.writeToBuffer(50, 10, "Press enter to go back to main menu", 91);
	getInput();
	if (g_skKeyEvent[K_ENTER].keyReleased)
	{
		g_eGameState = S_MENU;
		choice = 1;
	}
}

void storypart2(int Stage)
{
	switch (Stage)
	{
	case 1:
		renderstorylinestage1act1part2(20, 10);
		break;
	case 2:
		renderstorylinestage2act1part2(20, 10);
		break;
	case 3:
		renderstorylinestage3act1part2(20, 10);
		break;
	case 4:
		renderstorylinestage4act1part2(20, 10);
		break;
	default:
		renderstorylinestage1act1part2(20, 10);
		break;
	}
}

void Renderstory(int stagepicked) {
	for (int i =5;i<40;i++)
	{
		g_Console.writeToBuffer(5, i, "#", 91);
		g_Console.writeToBuffer(145, i, "#", 91);
	}
	for (int i = 5;i < 146;i++)
	{
		g_Console.writeToBuffer(i, 5, "#", 91);
	}
	switch (stagepicked) {
	case 1:
		if (nextstoryline == true)
		{
			storypart2(1);
			gottobattle = true;
		}
		else
		{
			renderstorylinestage1act1part1(20, 10);
		}
		break;
	case 2:
		if (nextstoryline == true)
		{
			storypart2(2);
			gottobattle = true;
		}
		else
		{
			renderstorylinestage2act1part1(20, 10);
		}
		break;
	case 3:
		if (nextstoryline == true)
		{
			storypart2(3);
			gottobattle = true;
		}
		else
		{
			renderstorylinestage3act1part1(20, 10);
		}
		break;
	case 4:
		if (nextstoryline == true)
		{
			storypart2(4);
			gottobattle = true;
		}
		else
		{
			renderstorylinestage4act1part1(20, 10);
		}
		break;
	default:
		renderstorylinestage1act1part1(20,10);
		break;
	}
	getInput();
	g_Console.writeToBuffer(50, 33, "Press enter to continue", 0x06, 91);
	if (g_skKeyEvent[K_ENTER].keyReleased)
	{
		nextstoryline = true;
	}
	if ((g_skKeyEvent[K_ENTER].keyReleased) && (nextstoryline == true) && (gottobattle ==true) )
	{
		g_eGameState = S_BATTLE;
	}
}

void render()
{
	clearScreen();      // clears the current screen and draw from scratch 
	switch (g_eGameState)
	{
	case S_MENU: renderMenuEvents(choice, backloop);
		break;
	case S_BATTLEN:
		storyafter(stageP);
		break;
	case S_BATTLE: RenderBattleEvents(stageP);
		break;
	case S_BEFOREBATTLEN:
		Renderstory(stageP);
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
		ss.str("");
		ss << choice;
		g_Console.writeToBuffer(85, 24, ss.str(), 91);
		break;

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
		g_Console.writeToBuffer(80, 9, "> SUMMON <", 91);
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
			if (newC == true) {
				ss.str("");
				ss << "You summoned " << namelist[gachanum - 1] << "!";
				g_Console.writeToBuffer(68, 16, ss.str(), 91);
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
						}
					}
				}
			}
			Qpressed = false;
		}
	}
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
	if (createparty == 0)
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
	cls();
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
		g_Console.writeToBuffer(42, 10, "######################################################################################", 91);
		for (int i = 0; i < 16; i++) {
			g_Console.writeToBuffer(42, 11 + i, "#                                                                                    #", 91);
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
		g_Console.writeToBuffer(50, 2, c1[0], 14); g_Console.writeToBuffer(120, 2, e1[0], 75);
		g_Console.writeToBuffer(50, 4, c2[0], 14); g_Console.writeToBuffer(120, 4, e2[0], 75);
		g_Console.writeToBuffer(50, 6, c3[0], 14); g_Console.writeToBuffer(120, 6, e3[0], 75);
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
			g_Console.writeToBuffer(85, 11 + i, "##", 91);
		}
		g_Console.writeToBuffer(60, 20, "##################################################", 91); /*g_Console.writeToBuffer(110, 20, "########################################", 91);*/
		g_Console.writeToBuffer(63, 15, "1. Attack", 91); g_Console.writeToBuffer(89, 15, "2.defend", 91);
		if (Cturn == 3) {
			g_Console.writeToBuffer(76, 25, "3." + party[0]->getMoveName(3), 91);
		}
		else {
			g_Console.writeToBuffer(76, 25, "3." + party[Cturn]->getMoveName(3), 91);
		}
		//if (Eturn < 3) {
		//	g_Console.writeToBuffer(76, 25, "3." + party[0]->getMoveName(3), 91);
		//}
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
		g_Console.writeToBuffer(114, 12, ss.str(), 91);
		if (stagepicked != 1) {
			ss.str("");
			ss << e2[0] << " hp: " << eptr[1]->getcurrentHealth() << " / " << eptr[1]->getHealth();
			g_Console.writeToBuffer(114, 16, ss.str(), 91);
			ss.str("");
			ss << e3[0] << " hp: " << eptr[2]->getcurrentHealth() << " / " << eptr[2]->getHealth();
			g_Console.writeToBuffer(114, 20, ss.str(), 91);
		}
		if (Cturn > 0) {
			ss.str("");
			std::string partyname[3] = { c1,c2,c3 };
			ss << partyname[Cturn - 1] << " used " << party[Cturn - 1]->getMoveName(Cmove[Cturn - 1]);
			g_Console.writeToBuffer(70, 9, ss.str(), 91);
		}
	}
}
player battle(int stagepicked)
{
	for (int i = 0; i < 3; i++)
	{
		if (party[i] != nullptr)
		{
			checkparty++;
		}
	}
	if (checkparty != 3)
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
			difficulty = 0;
			getInput();
			if (g_skKeyEvent[K_UP].keyReleased && choice != 1) {
				choice--;
			}
			if (g_skKeyEvent[K_DOWN].keyReleased && choice != 5) {
				choice++;
			}
			if (g_skKeyEvent[K_ESCAPE].keyReleased) {
				g_eGameState = S_MENU;
				backloop = 1;
				return p;
			}
			if (g_skKeyEvent[K_ENTER].keyReleased) {
				difficulty = choice;
				choice = 1;
			}
			if (difficulty != 0) {
				switch (stageP)
				{
				case 1://stage 1
					battleStart = false;
					eptr[0] = new SpinachBoss(5 * difficulty); enemyno++; bossno++; eptr[1] = nullptr; eptr[2] = nullptr;
					break;
				case 2://stage 2
					battleStart = false;
					eptr[0] = new Eggplant(10 * difficulty); eptr[1] = new Minion(10 * difficulty, minionnames[0]); eptr[2] = new Minion(10 * difficulty, minionnames[1]); enemyno += 3; bossno++; minionno += 2;
					break;
				case 3://stage 3
					battleStart = false;
					eptr[0] = new Beet(15 * difficulty); eptr[1] = new Minion(15 * difficulty, minionnames[2]); eptr[2] = new Minion(15 * difficulty, minionnames[3]); enemyno += 3; bossno++; minionno += 2;
					break;
				case 4://stage 4
					battleStart = false;
					eptr[0] = new Steak(20 * difficulty); eptr[1] = new Minion(20 * difficulty, minionnames[4]); eptr[2] = new Minion(20 * difficulty, minionnames[5]); enemyno += 3; bossno++; minionno += 2;
					break;
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
			//gets alive companions and alive enemies
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
			if (aliveC == 0) {
				result = 2;//lose
			}
			else if (aliveE == 0) {
				result = 1;//win
			}
			if (result == 0)//result will become 1 or 2 when the battle ends
			{
				//companion move
				if (Cturn < 3)//friendly attack
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
								}
								party[Cturn]->setskillcd(4);
							}
							if (Cmove[Cturn] == 2) {
								moveChosen = false;
								targetChosen = true;
								party[Cturn]->block();
								Ctarget[Cturn] = NULL;
								Cturn++;
							}
						}
					}

					//user chooses target
					if (party[Cturn]->getcurrentHealth() > 0 && targetChosen == false)
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
								moveChosen = false;
								targetChosen = true;
								choice = 1;
							}
							else {//attack()
								Ctarget[Cturn] = choice - 1;
								dmg = party[Cturn]->getcurrentDamage();
								eptr[Ctarget[Cturn]]->setcurrentHealth(eptr[Ctarget[Cturn]]->getcurrentHealth() - dmg);
								moveChosen = true;
								targetChosen = true;
								choice = 1;
							}
						}
					}
					//move takes effect
					if (Cturn < 3) {
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
							choice = 1;
							for (int i = 0; i < 3; i++) {
								if (eptr[i] != nullptr) {
									eptr[i]->resetstats(1);
									eptr[i]->resetstats(2);
									eptr[i]->resetstats(3);
								}
							}
						}
					}
				}
				//enemy moves
				if (Eturn < 3 && Cturn == 3) {
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
								Emove[Eturn] = rand() % 2;
								if (Emove[Eturn] == 2) {
									eptr[Eturn]->block();
									Etarget[Eturn] = NULL;
								}
								else if (Emove[Eturn] == 3) {
									if (eptr[Eturn]->getskillcd() == 0) {
										int skillused = rand() % 4 + 1;
										eptr[Eturn]->skill(skillused);
										eptr[Eturn]->setskillcd(4);
									}
								}
								else if (Emove[Eturn] == 1) {
									dmg = eptr[Eturn]->getcurrentDamage();
									party[Etarget[Eturn]]->setcurrentHealth(party[Etarget[Eturn]]->getcurrentHealth() - dmg);
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
									dmg = eptr[Eturn]->getcurrentDamage();
									party[Etarget[Eturn]]->setcurrentHealth(party[Etarget[Eturn]]->getcurrentHealth() - dmg);
									break;
								case 2://defend
									eptr[Eturn]->block();
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
													int statdecrease = rand() % 2 + 1;
													if (statdecrease == 1)
														party[Etarget[0]]->setcurrentDamage(party[Etarget[0]]->getcurrentDamage() * 0.8);
													if (statdecrease == 2)
														party[Etarget[0]]->setcurrentResistance(party[Etarget[0]]->getcurrentResistance() * 0.8);
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
					getInput();
					if (g_skKeyEvent[K_ENTER].keyReleased) {
						Eturn++;
					}

				}
			}
			if (friendlyAtks == 3 && enemyAtks == 3)
			{
				for (int i = 0; i < 3; i++) {
					if (party[i]->getcurrentHealth() > 1 && party[i]->getskillcd() > 0) {
						party[i]->setskillcd(party[i]->getskillcd() - 1);
					}
					if (eptr[i] != nullptr) {
						if (eptr[i]->getcurrentHealth() > 1 && eptr[i]->getskillcd() > 0) {
							eptr[i]->setskillcd(party[i]->getskillcd() - 1);
						}
					}
				}
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
				g_Console.writeToBuffer(81, 4, "YOU LOST", 91);
				g_Console.writeToBuffer(77, 5, "press Enter to go back to menu", 91);
				getInput();
				if (g_skKeyEvent[K_ENTER].keyReleased) {
					g_eGameState = S_MENU;
					choice = 1;
				}
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
				getInput();
				g_Console.writeToBuffer(81, 4, "YOU WON!", 91);
				g_Console.writeToBuffer(77, 5, "press Enter to Continue", 91);
				if (g_skKeyEvent[K_ENTER].keyReleased) {
					g_eGameState = S_BATTLEN;
					int exp = (bossno * 50 + minionno * 25) * difficulty;
					int coins = (bossno * 500 + minionno * 250) * difficulty;
					p.stagecleared(coins, exp);
					p.checklevelup();
					return p;
				}
				if (p.getplayerinfo(5) + 1 == stagepicked)
					p.clearednewstage();
				return p;
			}
		}
		return p;
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
		else if (g_skKeyEvent[K_DOWN].keyReleased && choice != p.getplayerinfo(5) + 1) {
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
			for (int i = 0; i < 3; i++) {///sets all enemy pointers to null when battle first starts
				eptr[i] = { nullptr };
				Cmove[i] = 0;
				Ctarget[i] = 0;
				Emove[i] = 0;
				Etarget[i] = 0;
				party[i]->setcurrentHealth(party[i]->getHealth());
			}
			Cturn = 0, Eturn = 0;
			friendlyAtks = 0, enemyAtks = 0;//counts the number of time the player and enemy has attacked, reset upon reaching alive entities of respective sides
			aliveC = 3, aliveE = 0;
			moveChosen = false, targetChosen = true;
			battleStart = true;
			g_eGameState = S_BEFOREBATTLEN;
			nextstoryline = false;
			gottobattle = false;
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
			newC = false;
			Qpressed = true;
			gachanum = summon();
			if (gachanum == 0) {//for when user does not have enough coins
				g_Console.writeToBuffer(58, 13, "You do not have enough coins", 91);
			}
			if (gachanum > 0 && gachanum < 11) {
				if (cptr[gachanum - 1] == nullptr) {//check for new companion only if q was pressed
					cptr[gachanum - 1] = new Companion(gachanum, namelist[gachanum - 1]);
					p.newcompanion();
					newC = true;
				}
				else {
					newC = false;
					for (int i = 0; i < 10; i++)//to check for dupes
					{
						if (cptr[i] != nullptr)
						{
							if (gachanum == cptr[i]->getid())
							{
								cptr[i]->summonedagain();
							}
						}
					}
				}
			}
		}
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
		storyafter(stageP);
		break;
	case S_MENU:
		menu();
		break;
	case S_BEFOREBATTLEN:
		Renderstory(stageP);
		break;
	}
}

//Start of render storyline script

void renderstorylinetutorialact1(int X, int Y)
{
	g_Console.writeToBuffer(X, Y, "ORANGE:", 0x02, 8);
	g_Console.writeToBuffer(X, Y + 1, "Eh!? You want to turn into juice!? Why? Is staying in this mansion as a decorative fruit not better?", 0x02, 101);
	g_Console.writeToBuffer(X, Y + 2, "You won't be consumed by humans here.", 0x02, 38);
	g_Console.writeToBuffer(X, Y + 3, "PLAYER:", 0x03, 8);
	g_Console.writeToBuffer(X, Y + 4, "But I want to be consumed by humans! I'm a fruit, not some painting.", 0x03, 69);
	g_Console.writeToBuffer(X, Y + 5, "What point is there in being a fruit if your purpose is just to be a decoration until you rot ?", 0x03, 96);
	g_Console.writeToBuffer(X, Y + 6, "ORANGE:", 0x02, 8);
	g_Console.writeToBuffer(X, Y + 7, "Y-you make a point. Are you sure this is what you want?", 0x02, 56);
	g_Console.writeToBuffer(X, Y + 8, "Then, as your only friend, I'll help you achieve your goal. You have always been alone so you probably won't survive alone. ", 0x02, 190);
	g_Console.writeToBuffer(X, Y + 9, " As long as you have enough coins, you can summon new friends. I'll provide the coins to you this time.", 0x02, 104);
	g_Console.writeToBuffer(X, Y + 10, " But, it looks like someone already wants to join you.", 0x02, 55);
	g_Console.writeToBuffer(X, Y + 11, "Cheese comes out from behind Orange.", 0x05);
	g_Console.writeToBuffer(X, Y + 12, "ORANGE:", 0x02, 8);
	g_Console.writeToBuffer(X, Y + 13, "This is Cheese. He will be 1 of the many companions who will help you on your journey", 0x02, 84);
	g_Console.writeToBuffer(X, Y + 14, "PLAYER:", 0x03, 8);
	g_Console.writeToBuffer(X, Y + 15, "Hi, nice to meet you. Thank you for joining me on my journey.", 0x03, 62);
	g_Console.writeToBuffer(X, Y + 16, "Cheese nods in reply.", 0x05, 20);
}

void renderstorylinetutorialact2(int x, int y)
{
	g_Console.writeToBuffer(x, y, "ORANGE:", 0x02, 8);
	g_Console.writeToBuffer(x, y + 1, "Well,would you look at that. You've already made a new friend. Now I'll teach you why friends are important. Since you want to turn into juice, you must make sure to not damage your body.", 0x02, 205);
	g_Console.writeToBuffer(x, y + 2, "Therefore, friends are here to protect you and ensure your safety. However, you will have to lead them properly.", 0x02, 113);
	g_Console.writeToBuffer(x, y + 3, "I'm sure you'll be able to handle it yourself. Besides, you probably can’t contain your excitement to leave right now.", 0x02, 119);
	g_Console.writeToBuffer(x, y + 4, "Then, it's time for you to begin your journey. I'm afraid this will be the last time we are together.", 0x02, 102);
	g_Console.writeToBuffer(x, y + 5, "Good luck out there. I'll miss you.", 0x02, 36);
	g_Console.writeToBuffer(x, y + 5, "PLAYER:", 0x03, 8);
	g_Console.writeToBuffer(x, y + 6, "Likewise, BYE ORANGE!", 0x03, 22);
	g_Console.writeToBuffer(x, y + 7, "With his new companion, he bolted out of the mansion.", 0x06, 54);
}

void renderstorylinestage1act1part1(int x, int y)
{
	g_Console.writeToBuffer(x, y, "You and Cheese set out on your journey to turn into juice.", 0x06, 57);
	g_Console.writeToBuffer(x, y + 1, "PLAYER:", 0x03, 8);
	g_Console.writeToBuffer(x, y + 2, "A supermarket would probably be the best place to find a new owner right?", 0x03, 74);
	g_Console.writeToBuffer(x, y + 3, "Cheese shrugs in reply.", 0x05, 22);
	g_Console.writeToBuffer(x, y + 4, "PLAYER:", 0x03, 8);
	g_Console.writeToBuffer(x, y + 5, "Not the talkative type,huh?", 0x03, 28);
	g_Console.writeToBuffer(x, y + 6, "Silence...", 0x05, 11);
	g_Console.writeToBuffer(x, y + 7, "PLAYER:", 0x03, 8);
	g_Console.writeToBuffer(x, y + 8, "Well, let's go with my idea then.", 0x03, 34);
	g_Console.writeToBuffer(x, y + 9, "After wandering about for an hour...", 0x6, 37);
	g_Console.writeToBuffer(x, y + 10, "PLAYER:", 0x03, 8);
	g_Console.writeToBuffer(x, y + 11, "Ah, a supermarket. Finally.", 0x03, 28);
	g_Console.writeToBuffer(x, y + 12, "SPINACH:", 0x08, 9);
	g_Console.writeToBuffer(x, y + 13, "Hello there. I don't recognise you guys. Are you guys new around here?", 0x08, 71);
	g_Console.writeToBuffer(x, y + 14, "PLAYER:", 0x03, 8);
	g_Console.writeToBuffer(x, y + 15, "Hi. Yes, we're not from around here.", 0x03, 37);
	g_Console.writeToBuffer(x, y + 16, "SPINACH:", 0x08, 9);
	g_Console.writeToBuffer(x, y + 17, "Then,why are you here?", 0x08, 23);
}

void renderstorylinestage1act1part2(int x, int y)
{
	g_Console.writeToBuffer(x, y, "PLAYER:", 0x03, 8);
	g_Console.writeToBuffer(x, y + 1, "I'm trying to turn into juice for the humans.", 0x03, 46);
	g_Console.writeToBuffer(x, y + 2, "SPINACH:", 0x08, 9);
	g_Console.writeToBuffer(x, y + 3, "What a coincidence. I am trying to turn into juice for humans too.", 0x08, 67);
	g_Console.writeToBuffer(x, y + 4, "I feel so excited just thinking about how young humans would throw up after their parents feed me to them.", 0x08, 107);
	g_Console.writeToBuffer(x, y + 5, "PLAYER:", 0x03, 8);
	g_Console.writeToBuffer(x, y + 6, "Wait, so you are trying to turn into juice to make humans suffer?", 0x03, 66);
	g_Console.writeToBuffer(x, y + 7, "SPINACH:", 0x08, 9);
	g_Console.writeToBuffer(x, y + 8, "Are you not?", 0x08, 13);
	g_Console.writeToBuffer(x, y + 9, "PLAYER:", 0x03, 8);
	g_Console.writeToBuffer(x, y + 10, "No! I want to make humans happy after they consume me. Isn’t that our purpose? To help humanity?", 0x03, 97);
	g_Console.writeToBuffer(x, y + 11, "SPINACH:", 0x08, 9);
	g_Console.writeToBuffer(x, y + 12, "That’s what I thought too. However, the world is harsh and cruel.", 0x08, 66);
	g_Console.writeToBuffer(x, y + 13, "PLAYER:", 0x03, 8);
	g_Console.writeToBuffer(x, y + 14, "What do you mean?", 0x03, 18);
	g_Console.writeToBuffer(x, y + 15, "SPINACH:", 0x08, 9);
	g_Console.writeToBuffer(x, y + 16, "Nevermind. Your goal is different from mine so I won’t let you pass.", 0x08, 69);
	g_Console.writeToBuffer(x, y + 17, "Cheese takes a defensive stance in front of you.", 0x05, 59);
}

void renderstorylinestage1act2(int x, int y)
{
	g_Console.writeToBuffer(x, y, "SPINACH:", 0x08, 9);
	g_Console.writeToBuffer(x, y + 1, "I don't believe it. How could I have lost? The world really is terrible isn't it.", 0x08, 82);
	g_Console.writeToBuffer(x, y + 2, "PLAYER:", 0x03, 8);
	g_Console.writeToBuffer(x, y + 3, "Why do you keep calling the world cruel?", 0x03, 41);
	g_Console.writeToBuffer(x, y + 4, "SPINACH:", 0x08, 9);
	g_Console.writeToBuffer(x, y + 5, "When I was young, I was like you. I wanted to be useful to humans, as they were the ones who gave us life.", 0x08, 107);
	g_Console.writeToBuffer(x, y + 6, "So when I was brought to this supermarket, I was very happy.", 0x08, 61);
	g_Console.writeToBuffer(x, y + 7, "I believed I could finally be useful to humans. However, no one ever bought me.", 0x08, 80);
	g_Console.writeToBuffer(x, y + 8, "Eventually, I turned bad and was thrown away. Ever since then, I had always hated humans.", 0x08, 90);
	g_Console.writeToBuffer(x, y + 9, "Thus, I tried many times to get back into the supermarket. Each time, I was always thrown out right away. And here I a---", 0x08, 122);
	g_Console.writeToBuffer(x, y + 10, "--SPLAT--", 0x06, 10);
	g_Console.writeToBuffer(x, y + 11, "Before Spinach could even finish speaking, a car parked on where Spinach was, squashing him.", 0x06, 93);
	g_Console.writeToBuffer(x, y + 12, "SPINACH:", 0x08, 9);
	g_Console.writeToBuffer(x, y + 13, "I TOLD YOU!!! THE WORLD IS CRUEL!!! I may be flat so it won't kill me, but it still hurts!", 0x08, 91);
	g_Console.writeToBuffer(x, y + 14, "While Spinach was stuck under the car, Cheese and you rushed into the supermarket.", 0x06, 81);
}

void renderstorylinestage2act1part1(int x, int y)
{
	g_Console.writeToBuffer(x, y, "PLAYER:", 0x03, 8);
	g_Console.writeToBuffer(x, y + 1, "Look there!", 0x03, 12);
	g_Console.writeToBuffer(x, y + 2, "He looks at a group of fruits on sale.", 0x06, 39);
	g_Console.writeToBuffer(x, y + 3, "PLAYER:", 0x03, 8);
	g_Console.writeToBuffer(x, y + 4, "Great, I’ll blend in on top and someone will hopefully buy me soon.", 0x03, 68);
	g_Console.writeToBuffer(x, y + 5, "For now, take a break, my friends. I will call when I need you once again.", 0x03, 75);
	g_Console.writeToBuffer(x, y + 6, "A few moments later", 0x06, 20);
	g_Console.writeToBuffer(x, y + 7, "PLAYER:", 0x03, 8);
	g_Console.writeToBuffer(x, y + 8, "Why is no one buying me?", 0x03, 25);
	g_Console.writeToBuffer(x, y + 9, "UNKNOWN:", 0x07, 10);
	g_Console.writeToBuffer(x, y + 10, "Maybe you're not worth buying.", 0x07, 31);
}

void renderstorylinestage2act1part2(int x, int y)
{
	g_Console.writeToBuffer(x, y, "PLAYER:", 0x03, 8);
	g_Console.writeToBuffer(x, y + 1, "Who said that?", 0x03, 15);
	g_Console.writeToBuffer(x, y + 2, "EGGPLANT:", 0x07, 10);
	g_Console.writeToBuffer(x, y + 3, "I did,of course, an almighty eggplant in the section beside yours.", 0x07, 67);
	g_Console.writeToBuffer(x, y + 4, "PLAYER:", 0x03, 8);
	g_Console.writeToBuffer(x, y + 5, "That's a little egoistic,don't you think?", 0x03, 42);
	g_Console.writeToBuffer(x, y + 6, "EGGPLANT:", 0x07, 10);
	g_Console.writeToBuffer(x, y + 7, "No! We vegetables are superior, soon more will learn of how delicious we taste especially when juiced!", 0x07, 103);
	g_Console.writeToBuffer(x, y + 8, "PLAYER:", 0x03, 8);
	g_Console.writeToBuffer(x, y + 9, "Not another one of you guys. I will not let any of you have your way with the humans.", 0x03, 86);
	g_Console.writeToBuffer(x, y + 10, "Come, help me, my friends!", 0x03, 27);
}

void renderstorylinestage2act2(int x, int y)
{
	g_Console.writeToBuffer(x, y, "EGGPLANT:", 0x07, 10);
	g_Console.writeToBuffer(x, y + 1, "Simple, our teamwork and willpower was better than yours which allowed us to-- HEY!", 0x07, 84);
	g_Console.writeToBuffer(x, y + 2, "You are picked up.", 0x06, 19);
	g_Console.writeToBuffer(x, y + 3, "PLAYER:", 0x03, 8);
	g_Console.writeToBuffer(x, y + 4, "It's happening,I'm being bought by a new owner!", 0x03, 48);
	g_Console.writeToBuffer(x, y + 5, "EGGPLANT:", 0x07, 10);
	g_Console.writeToBuffer(x, y + 6, "HEY! WE WEREN'T DONE YET!", 0x07, 26);
	g_Console.writeToBuffer(x, y + 7, "PLAYER:", 0x03, 8);
	g_Console.writeToBuffer(x, y + 8, "See ya!", 0x03, 8);
}

void renderstorylinestage3act1part1(int x, int y)
{
	g_Console.writeToBuffer(x, y, "After you're put in a bag", 0x06, 43);
	g_Console.writeToBuffer(x, y + 1, "PLAYER:", 0x03, 8);
	g_Console.writeToBuffer(x, y + 2, "Yay, I can't believe I will soon have my chance to serve humanity!", 0x03, 67);
	g_Console.writeToBuffer(x, y + 3, "UNKNOWN:", 0x07, 9);
	g_Console.writeToBuffer(x, y + 4, "In your dreams!", 0x07, 16);
	g_Console.writeToBuffer(x, y + 5, "PLAYER:", 0x03, 8);
	g_Console.writeToBuffer(x, y + 6, "Who is it this time?", 0x03, 21);
	g_Console.writeToBuffer(x, y + 7, "BEET:", 0x07, 6);
	g_Console.writeToBuffer(x, y + 8, "I am beetroot!", 0x07, 15);
	g_Console.writeToBuffer(x, y + 9, "PLAYER:", 0x03, 8);
	g_Console.writeToBuffer(x, y + 10, "Great, another vegetable.", 0x03, 26);
	g_Console.writeToBuffer(x, y + 11, "BEET:", 0x07, 6);
}

void renderstorylinestage3act1part2(int x, int y)
{
	g_Console.writeToBuffer(x, y, "I don't know what that means but I will play a bigger part in helping my owner than you!", 0x07, 89);
	g_Console.writeToBuffer(x, y + 1, "PLAYER:", 0x03, 8);
	g_Console.writeToBuffer(x, y + 2, "Oh yeah? How would you do that?", 0x03, 32);
	g_Console.writeToBuffer(x, y + 3, "BEET:", 0x07, 6);
	g_Console.writeToBuffer(x, y + 4, "Wouldn't you like to know? Everyone knows that being juiced is the best way to please the humans.", 0x07, 98);
	g_Console.writeToBuffer(x, y + 5, "PLAYER:", 0x03, 8);
	g_Console.writeToBuffer(x, y + 6, "Of course it is.", 0x03, 17);
	g_Console.writeToBuffer(x, y + 7, "BEET:", 0x07, 6);
	g_Console.writeToBuffer(x, y + 8, "Yes, and once I'm drunk by children they will come to realise that vegetables are better than fruits or any other food.", 0x07, 120);
	g_Console.writeToBuffer(x, y + 9, "PLAYER:", 0x03, 8);
	g_Console.writeToBuffer(x, y + 10, "Again seriously? I will not let any of you stain the humans' taste buds any longer! NOW!", 0x03, 89);
}

void renderstorylinestage3act2(int x, int y)
{
	g_Console.writeToBuffer(x, y, "BEET:", 0x07, 6);
	g_Console.writeToBuffer(x, y + 1, "I've been defeated. You've proven fruits are superior.", 0x07, 55);
	g_Console.writeToBuffer(x, y + 2, "PLAYER:", 0x03, 8);
	g_Console.writeToBuffer(x, y + 3, "No, I don't see it that way. We are all equals as food.", 0x03, 56);
	g_Console.writeToBuffer(x, y + 4, "BEET:", 0x07, 6);
	g_Console.writeToBuffer(x, y + 5, "I see the error of my ways. Thank you. I will forever remember th--AHHHH!", 0x07, 74);
	g_Console.writeToBuffer(x, y + 6, "Beet was picked up and placed on the chopping board out of earshot.", 0x06, 68);
	g_Console.writeToBuffer(x, y + 7, "You were then taken out and placed on the kitchen counter.", 0x06, 59);
	g_Console.writeToBuffer(x, y + 8, "PLAYER:", 0x03, 8);
	g_Console.writeToBuffer(x, y + 9, "Time to find a blender now, I guess.", 0x03, 37);
}

void renderstorylinestage4act1part1(int x, int y)
{
	g_Console.writeToBuffer(x, y, "PLAYER:", 0x03, 8);
	g_Console.writeToBuffer(x, y + 1, "YES! A blender!", 0x03, 16);
	g_Console.writeToBuffer(x, y + 2, "You run towards the blender.", 0x06, 29);
	g_Console.writeToBuffer(x, y + 3, "UNKNOWN:", 0x07, 9);
	g_Console.writeToBuffer(x, y + 4, "HALT! Who goes there?", 0x07, 22);
	g_Console.writeToBuffer(x, y + 5, "PLAYER:", 0x03, 8);
	g_Console.writeToBuffer(x, y + 6, "A fruit?", 0x03, 9);
	g_Console.writeToBuffer(x, y + 7, "STEAK:", 0x07, 7);
	g_Console.writeToBuffer(x, y + 8, "I haven't seen you here before? Did you come with the new groceries?", 0x07, 69);
	g_Console.writeToBuffer(x, y + 9, "PLAYER:", 0x03, 8);
	g_Console.writeToBuffer(x, y + 10, "Uh,yes?", 0x03, 8);
	g_Console.writeToBuffer(x, y + 11, "STEAK:", 0x07, 7);
	g_Console.writeToBuffer(x, y + 12, "Very well. What are you doing here?", 0x07, 36);
}

void renderstorylinestage4act1part2(int x, int y)
{
	g_Console.writeToBuffer(x, y, "PLAYER:", 0x03, 8);
	g_Console.writeToBuffer(x, y + 1, "I have come a long way to be blended into juice to please the humans.", 0x03, 70);
	g_Console.writeToBuffer(x, y + 2, "STEAK:", 0x07, 7);
	g_Console.writeToBuffer(x, y + 3, "I see. Well, sorry to say, but you would have to wait. Our owner will choose which food is to be blended first.", 0x07, 113);
	g_Console.writeToBuffer(x, y + 4, "PLAYER:", 0x03, 8);
	g_Console.writeToBuffer(x, y + 5, "But, I assure you I am the most worthy to be tasted in juice.", 0x03, 62);
	g_Console.writeToBuffer(x, y + 6, "STEAK:", 0x07, 7);
	g_Console.writeToBuffer(x, y + 7, "None shall pass without my approval. Begone, and wait your turn.", 0x07, 65);
	g_Console.writeToBuffer(x, y + 8, "PLAYER:", 0x03, 8);
	g_Console.writeToBuffer(x, y + 9, "I've come a long way for this, you will not stop me now!", 0x03, 57);
	g_Console.writeToBuffer(x, y + 10, "STEAK:", 0x07, 7);
	g_Console.writeToBuffer(x, y + 11, "Very well,challenge me and prove your worth to use the blender.", 0x07, 64);
	g_Console.writeToBuffer(x, y + 12, "PLAYER:", 0x03, 8);
	g_Console.writeToBuffer(x, y + 13, "You're on! Come, my friends!", 0x03, 29);
}

void renderstorylinestage4act2(int x, int y)
{
	g_Console.writeToBuffer(x, y, "STEAK:", 0x07, 7);
	g_Console.writeToBuffer(x, y + 1, "You have proven that you are a worthy contender.You may use the blender as you wish.", 0x07, 85);
	g_Console.writeToBuffer(x, y + 2, "However, I recommend you to not be so optimistic. The process to turn into juice is not for the faint of heart.", 0x07, 112);
	g_Console.writeToBuffer(x, y + 3, "PLAYER:", 0x03, 8);
	g_Console.writeToBuffer(x, y + 4, "I understand, but I have travelled too far to stop now.", 0x03, 56);
	g_Console.writeToBuffer(x, y + 5, "STEAK:", 0x07, 7);
	g_Console.writeToBuffer(x, y + 6, "Very well. I admire your determination. You may proceed.", 0x07, 57);
}

void renderstorylineend(int x, int y)
{
	g_Console.writeToBuffer(x, y, "You stares down at the blender ready to jump in.", 0x06, 49);
	g_Console.writeToBuffer(x, y + 1, "Steak presses the on button and walks away.", 0x06, 44);
	g_Console.writeToBuffer(x, y + 2, "PLAYER:", 0x03, 8);
	g_Console.writeToBuffer(x, y + 3, "I guess this is it, my friends. You have all helped me in my journey. It is time to bid farewell. ", 0x03, 99);
	g_Console.writeToBuffer(x, y + 4, "All of your companions go their own ways.", 0x05, 42);
	g_Console.writeToBuffer(x, y + 5, "PLAYER:", 0x03, 8);
	g_Console.writeToBuffer(x, y + 6, "Now, I shall finally give myself up for the sake of humanity", 0x03, 61);
	g_Console.writeToBuffer(x, y + 7, "You fall into the blender.", 0x06, 27);
	g_Console.writeToBuffer(x, y + 8, "Silence followed by the crunching and slicing of the blender.", 0x06, 62);
	g_Console.writeToBuffer(x, y + 9, "The owner comes to the kitchen and sees the freshly made juice.", 0x06, 64);
	g_Console.writeToBuffer(x, y + 10, "He takes a sip,smiles and leaves the rest on the counter as he walks away.", 0x06, 75);
	g_Console.writeToBuffer(x, y + 11, "                                The End                                     ", 0x30, 77);
}
