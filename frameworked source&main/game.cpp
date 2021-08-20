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
#include "game.h"
#include "Framework\console.h"
#include <iomanip>
#include <sstream>

double  g_dElapsedTime;
double  g_dDeltaTime;
//menu data members
int choice = 1;
int backloop = 1;

SKeyEvent g_skKeyEvent[K_COUNT];
std::string namelist[10] = { "Lolipop","Honey","Milk","Yohgurt","Rice","Pasta","Fish","Mussels","Grapes","Strawberries" };
Companion* cptr[10] = { nullptr,nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
player p("Wapples", "Apple");
Companion* party[3] = { nullptr,nullptr,nullptr };
SGameChar   g_sChar;
EGAMESTATES g_eGameState = S_SPLASHSCREEN; // initial state

// Console object
Console g_Console(80, 25, "SP1 Framework");

void init( void )
{
    // Set precision for floating point output
    g_dElapsedTime = 0.0;    
    // sets the initial state for the game
    g_eGameState = S_MENU;
	cptr[p.getplayerinfo(3)] = new Companion(3, "Milk");
	p.newcompanion();

    //g_sChar.m_cLocation.X = g_Console.getConsoleSize().X / 2;
    //g_sChar.m_cLocation.Y = g_Console.getConsoleSize().Y / 2;
    //g_sChar.m_bActive = true;
    //// sets the width, height and the font name to use in the console
    //g_Console.setConsoleFont(0, 16, L"Consolas");

    // remember to set your keyboard handler, so that your functions can be notified of input events
    g_Console.setKeyboardHandler(keyboardHandler);
}

void shutdown( void )
{
    // Reset to white text on black background
    colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

    g_Console.clearBuffer();
}

void getInput( void )
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
    case S_SPLASHSCREEN: // don't handle anything for the splash screen
        break;
	case S_MENU:
		gameplayKBHandler(keyboardEvent);
		break;
    case S_GAME: gameplayKBHandler(keyboardEvent); // handle gameplay keyboard event 
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
    moveCharacter();    // moves the character, collision detection, physics, etc
                        // sound can be played here too.
}

void moveCharacter()
{    
    // Updating the location of the character based on the key release
    // providing a beep sound whenver we shift the character
    if (g_skKeyEvent[K_UP].keyReleased && g_sChar.m_cLocation.Y > 0)
    {
        //Beep(1440, 30);
        g_sChar.m_cLocation.Y--;       
    }
    if (g_skKeyEvent[K_LEFT].keyReleased && g_sChar.m_cLocation.X > 0)
    {
        //Beep(1440, 30);
        g_sChar.m_cLocation.X--;        
    }
    if (g_skKeyEvent[K_DOWN].keyReleased && g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 1)
    {
        //Beep(1440, 30);
        g_sChar.m_cLocation.Y++;        
    }
    if (g_skKeyEvent[K_RIGHT].keyReleased && g_sChar.m_cLocation.X < g_Console.getConsoleSize().X - 1)
    {
        //Beep(1440, 30);
        g_sChar.m_cLocation.X++;        
    }
    if (g_skKeyEvent[K_SPACE].keyReleased)
    {
        g_sChar.m_bActive = !g_sChar.m_bActive;        
    }

   
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
    case S_SPLASHSCREEN: renderSplashScreen();
        break;
	case S_MENU: renderMenuEvents(choice, backloop);
		break;

    case S_GAME: renderGame();
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

void renderSplashScreen()  // renders the splash screen
{
    COORD c = g_Console.getConsoleSize();
    c.Y /= 3;
    c.X = c.X / 2 - 9;
    g_Console.writeToBuffer(c, "A game in 3 seconds", 0x03);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 20;
    g_Console.writeToBuffer(c, "Press <Space> to change character colour", 0x09);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 9;
    g_Console.writeToBuffer(c, "Press 'Esc' to quit", 0x09);
}

void renderGame()
{
    renderMap();        // renders the map to the buffer first
    renderCharacter();  // renders the character into the buffer
}

void renderMap()
{
    // Set up sample colours, and output shadings
    const WORD colors[] = {
        0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
        0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
    };

    COORD c;
    for (int i = 0; i < 12; ++i)
    {
        c.X = 5 * i;
        c.Y = i + 1;
        colour(colors[i]);
        g_Console.writeToBuffer(c, " °±²Û", colors[i]);
    }
}

void renderCharacter()
{
    // Draw the location of the character
    WORD charColor = 0x0C;
    if (g_sChar.m_bActive)
    {
        charColor = 0x0A;
    }
    g_Console.writeToBuffer(g_sChar.m_cLocation, (char)1, charColor);
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
	switch (screen) {
	case 1:
		ss << "Prompt: " << choice;
		g_Console.writeToBuffer(0, 1, "-------------------------", 0x17, 26);
		g_Console.writeToBuffer(0, 2, "1. Start Game", 0x17, 14);
		g_Console.writeToBuffer(0, 3, "2. Quit", 0x17, 8);
		g_Console.writeToBuffer(0, 4, ss.str(), 0x17);
		break;
	case 99:
		g_Console.writeToBuffer(0, 5, "See you next time!", 0x17);
		break;
	case 2:
		g_Console.writeToBuffer(0, 1, "-------------------------", 0x17, 26);
		ss << "Player Level" << p.getplayerinfo(1);
		g_Console.writeToBuffer(0, 2, ss.str(), 0x17);
		g_Console.writeToBuffer(0, 3, "1. Stages", 0x17);
		g_Console.writeToBuffer(0, 4, "2. Party", 0x17);
		g_Console.writeToBuffer(0, 5, "3. Companions", 0x17);
		g_Console.writeToBuffer(0, 6, "4. Summon", 0x17);
		g_Console.writeToBuffer(0, 7, "5. Back", 0x17);
		ss.str("");
		ss << "Prompt: " << choice;
		g_Console.writeToBuffer(0, 8, ss.str(), 0x17);
		break;
	case 3:
		std::string stages[4] = { "I'm not going to just spin around and leave!", "That went eggcellently well","No time to beet about the bush","Everything at steak" };
		g_Console.writeToBuffer(0, 1, "-------------------------", 0x17, 26);
		g_Console.writeToBuffer(0, 2, "Stages:", 0x17);
		for (int i = 0; i <= p.getplayerinfo(5); i++)
		{
			ss.str("");
			ss << i + 1 << ". " << stages[i];
			g_Console.writeToBuffer(0, 2+i, ss.str(), 0x17);
		}
		ss.str("");
		ss << p.getplayerinfo(5) + 2 << ". Back";
		ss.str("");
		ss << "Prompt: " << choice;
		g_Console.writeToBuffer(0, 8, ss.str(), 0x17);

	}
		//COORD c = { startPos.X, startPos.Y + i };
		//g_Console.writeToBuffer(0,0, "-------------------------", 0x17);

}

// this is an example of how you would use the input events

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
int summon(player p, Companion* cptr[10], std::string namelist[10])
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
	int speedlist[6] = { 0,0,0,0,0,0 };
	int result = 0;
	int checkparty = 0;
	int partysize = 0;
	int enemyno = 0;
	int bossno = 0;
	int minionno = 0;
	int deadcompanion = 0;
	int deadenemies = 0;
	double dmg;
	for (int i = 0; i < 3; i++)
	{
		if (party[i] == nullptr)
		{
			checkparty++;
		}
	}
	int difficulty = 1;
	if (stagepicked != 0)
	{
		std::cout << "1. Easy" << std::endl;
		std::cout << "2. Normal" << std::endl;
		std::cout << "3. Hard" << std::endl;
		std::cout << "4. Extreme" << std::endl;
		std::cout << "5. Death" << std::endl;
		std::cout << "Prompt: ";
		std::cin >> difficulty;
	}
	if (checkparty == 3)
	{
		std::cout << "-------------------------" << std::endl;
		std::cout << "Party cannot be empty" << std::endl;
		setparty(cptr, p, party);
		std::cout << "" << std::endl;
	}
	int sametype = 0;
	for (int i = 0; i < 3; i++)
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
	int allgood = 0;
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
		while (allgood == 0)
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
					eptr[i] = new SpinachBoss(enemylvl);
					bossno++;
					enemyno++;
					break;
				case 2:
					eptr[i] = new Eggplant(enemylvl);
					bossno++;
					enemyno++;
					break;
				case 3:
					eptr[i] = new Beet(enemylvl);
					bossno++;
					enemyno++;
					break;
				case 4:
					eptr[i] = new Steak(enemylvl);
					bossno++;
					enemyno++;
					break;
				case 5:
					eptr[i] = new Minion(enemylvl, minionnames[rand() % 6]);
					bossno++;
					enemyno++;
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
		eptr[0] = new SpinachBoss(5 * difficulty);
		enemyno++;
		bossno++;
		break;
	case 2:
		eptr[0] = new Eggplant(10 * difficulty);
		eptr[1] = new Minion(10 * difficulty, minionnames[0]);
		eptr[2] = new Minion(10 * difficulty, minionnames[1]);
		enemyno += 3;
		bossno++;
		minionno += 2;
		break;
	case 3:
		eptr[0] = new Beet(15 * difficulty);
		eptr[1] = new Minion(15 * difficulty, minionnames[2]);
		eptr[2] = new Minion(15 * difficulty, minionnames[3]);
		enemyno += 3;
		bossno++;
		minionno += 2;
		break;
	case 4:
		eptr[0] = new Steak(20 * difficulty);
		eptr[1] = new Minion(20 * difficulty, minionnames[4]);
		eptr[2] = new Minion(20 * difficulty, minionnames[5]);
		enemyno += 3;
		bossno++;
		minionno += 2;
		break;
	}
	while (result == 0)
	{
		for (int i = 0; i < 3; i++)
		{
			if (party[i] != nullptr)
			{
				if (party[i]->getcurrentHealth() > 0)
				{
					int choice;
					int target;
					std::cout << "-------------------------" << std::endl;
					std::cout << "Enemies: " << std::endl;
					for (int f = 0; f < 3; f++)
					{
						if (eptr[f] != nullptr)
							std::cout << f + 1 << ". " << eptr[f]->getname() << "    Health: " << int(eptr[f]->getcurrentHealth()) << std::endl;
					}
					std::cout << "" << std::endl;
					std::cout << "Companion: " << party[i]->getname() << "    Health: " << int(party[i]->getcurrentHealth()) << std::endl;
					std::cout << "Target: ";
					std::cin >> target;
					target--;
					for (int f = 1; f < 4; f++)
						std::cout << f << ". " << party[i]->getMoveName(f) << std::endl;
					int choosemove = 0;
					while (choosemove == 0)
					{
						std::cout << "Prompt: ";
						std::cin >> choice;
						if (choice == 1)
						{
							party[i]->setatktarget(eptr[target]->getname());
							choosemove++;
						}
						else if (choice == 2)
						{
							party[i]->block();
							std::cout << party[i]->getname() << " used Block, increasing Defence" << std::endl;
							choosemove++;
						}
						else if ((choice == 3) && (party[i]->getskillcd() == 0))
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
						else if ((choice == 3) && (party[i]->getskillcd() != 0))
						{
							std::cout << "Skill is on " << party[i]->getskillcd() << " turn cooldown" << std::endl;
						}
					}
					if (party[i]->getskillcd() > 0)
					{
						party[i]->setskillcd(party[i]->getskillcd() - 1);
					}
				}
			}
		}
		for (int i = 0; i < 3; i++)
		{
			if (eptr[i] != nullptr)
			{
				int targetcheck = 0;
				int target = 0;
				while (targetcheck == 0)
				{
					target = rand() % 3;
					if ((party[target] != nullptr) && (party[target]->getcurrentHealth() > 0))
					{
						targetcheck++;
					}
				}
				std::cout << "" << std::endl;
				int choosemove = 0;
				while (choosemove == 0)
				{
					int choice = rand() % 3 + 1;
					if (choice == 1)
					{
						eptr[i]->setatktarget(party[target]->getname());
						choosemove++;
					}
					if (choice == 2)
					{
						eptr[i]->block();
						std::cout << eptr[i]->getname() << " used Block, increasing Defence" << std::endl;
						choosemove++;
					}
					else if ((choice == 3) && (eptr[i]->getskillcd() == 0))
					{
						int whichskill;
						int skillused;
						if (eptr[i]->getname() == "Steak")
						{
							whichskill = rand() % 5 + 1;
							skillused = eptr[i]->skill(whichskill);
						}
						else
						{
							whichskill = rand() % 4 + 1;
							skillused = eptr[i]->skill(whichskill);
						}
						if (skillused == 1)
						{
							for (int l = 0; l < 3; l++)
							{
								if (party[l] != nullptr)
								{
									dmg = eptr[i]->attack(party[l]->getcurrentResistance());
									party[l]->takedmg(dmg);
								}
							}
							std::cout << eptr[i]->getname() << " used " << eptr[i]->getMoveName(1) << int(dmg) << std::endl;
							for (int f = 0; f < 3; f++)
							{
								if (party[f] != nullptr)
								{
									if (party[f]->getcurrentHealth() <= 0)
									{
										deadcompanion++;
										std::cout << party[f]->getname() << " has died" << std::endl;
									}
								}
							}
							if (deadcompanion == partysize)
							{
								result = 2;
								break;
							}
						}
						else if (skillused == 2)
						{
							dmg = eptr[i]->attack(party[target]->getcurrentResistance());
							party[target]->takedmg(dmg);
							std::cout << eptr[i]->getname() << " used " << eptr[i]->getMoveName(2) << int(dmg) << " damage to " << party[target]->getname() << std::endl;
							for (int f = 0; f < 3; f++)
							{
								if (party[f] != nullptr)
								{
									if (party[f]->getcurrentHealth() <= 0)
									{
										deadcompanion++;
										std::cout << party[f]->getname() << " has died" << std::endl;
									}
								}
							}
							if (deadcompanion == partysize)
							{
								result = 2;
								break;
							}
						}
						else if (skillused == 3)
						{
							party[target]->setcurrentResistance(party[target]->getcurrentResistance() * 0.3);
							std::cout << eptr[i]->getname() << " used " << eptr[i]->getMoveName(3) << party[target]->getname() << std::endl;
						}
						else if (skillused == 4)
						{
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
						}
						else if (skillused == 5)
						{
							party[target]->setcurrentDamage(cptr[target]->getcurrentDamage() * 0.3);
							std::cout << eptr[i]->getname() << " used " << eptr[i]->getMoveName(1) << party[target]->getname() << std::endl;
						}
						else
						{
							std::cout << eptr[i]->getname() << " used " << eptr[i]->getMoveName(whichskill) << std::endl;
						}
						eptr[i]->setskillcd(4);
					}
				}
				if (eptr[i]->getskillcd() > 0)
				{
					eptr[i]->setskillcd(eptr[i]->getskillcd() - 1);
				}
			}
		}
		if (result == 0)
		{
			for (int i = 0; i < 3; i++)
			{
				if (party[i] != nullptr)
				{
					if (party[i]->getatktarget() != "0")
					{
						speedlist[i] = int(party[i]->getcurrentSpeed());
					}
				}
				if (eptr[i] != nullptr)
				{
					if (eptr[i]->getatktarget() != "0")
					{
						speedlist[i + 3] = int(eptr[i]->getcurrentSpeed());
					}
				}

			}
			std::sort(speedlist, speedlist + 6, greater<int>());
			for (int i = 0; i < 6; i++)
			{
				if (speedlist[i] != 0)
				{
					for (int l = 0; l < 3; l++)
					{
						if ((eptr[l] != nullptr) && (result == 0))
						{
							if ((speedlist[i] == int(eptr[l]->getcurrentSpeed())) && (eptr[l]->getatktarget() != "0") && (eptr[l]->getcurrentHealth() > 0))
							{
								for (int f = 0; f < 3; f++)
								{
									if (party[f] != nullptr)
									{
										if ((party[f]->getname() == eptr[l]->getatktarget()) && (party[f]->getcurrentHealth()))
										{
											dmg = eptr[l]->attack(party[f]->getcurrentResistance());
											party[f]->takedmg(dmg);
											std::cout << eptr[l]->getname() << " attacked " << party[f]->getname() << " for " << int(dmg) << std::endl;
											eptr[l]->setatktarget("0");
											if (party[f]->getcurrentHealth() == 0)
											{
												deadcompanion++;
												std::cout << party[f]->getname() << " has died" << std::endl;
											}
										}
										else if ((party[f]->getname() == eptr[l]->getatktarget()) && (party[f]->getcurrentHealth() <= 0))
										{
											int difftarget = 0;
											while (difftarget == 0)
											{
												int newtarget = rand() % 3;
												if ((newtarget != f) && (party[newtarget] != nullptr))
												{
													eptr[l]->setatktarget(party[newtarget]->getname());
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
							if ((speedlist[i] == int(party[l]->getcurrentSpeed())) && (party[l]->getatktarget() != "0") && (party[l]->getcurrentHealth() > 0))
							{
								for (int f = 0; f < 3; f++)
								{
									if (eptr[f] != nullptr)
									{
										if ((eptr[f]->getname() == party[l]->getatktarget()) && (eptr[f]->getcurrentHealth()))
										{
											dmg = party[l]->attack(eptr[f]->getcurrentResistance());
											eptr[f]->takedmg(dmg);
											std::cout << party[l]->getname() << " attacked " << eptr[f]->getname() << " for " << int(dmg) << std::endl;
											party[l]->setatktarget("0");
											if (eptr[f]->getcurrentHealth() == 0)
											{
												deadenemies++;
												std::cout << eptr[f]->getname() << " has died" << std::endl;
											}
										}
										else if ((eptr[f]->getname() == party[l]->getatktarget()) && (eptr[f]->getcurrentHealth() <= 0))
										{
											int difftarget = 0;
											while (difftarget == 0)
											{
												int newtarget = rand() % 3;
												if ((newtarget != f) && (eptr[newtarget] != nullptr))
												{
													party[l]->setatktarget(eptr[newtarget]->getname());
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
			int exp = (bossno * 50 * +minionno * 25) * difficulty;
			int coins = (bossno * 500 + minionno * 250) * difficulty;
			p.stagecleared(coins, exp);
			p.checklevelup();
			if (p.getplayerinfo(5) + 1 == stagepicked)
				p.clearednewstage();
			return p;
		}
	}
	return p;
}
int menu(Companion* cptr[10], player p, Companion* party[3], std::string namelist[10])
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
				return 0;
			}
			else {
				backloop++;
				choice = 1;
			}
		}
		break;
	case 2://menu choices
		std::cout << "-------------------------" << std::endl;
		std::cout << "Player Level: " << p.getplayerinfo(1) << std::endl;
		std::cout << "1. Stages" << std::endl;
		std::cout << "2. Party" << std::endl;
		std::cout << "3. Companions" << std::endl;
		std::cout << "4. Summon" << std::endl;
		std::cout << "5. Back" << std::endl;
		std::cout << "Prompt: ";
		getInput();
		if (g_skKeyEvent[K_UP].keyReleased)
			choice--;
		else if (g_skKeyEvent[K_DOWN].keyReleased)
			choice++;
		if (choice < 1) {
			choice = 1;
		}
		if (choice > 5) {
			choice = 5;
		}
		if (g_skKeyEvent[K_ENTER].keyReleased) {
			if (choice == 5)
				backloop = 1;
			else
				backloop = backloop + choice + 1;
		}
		break;
	case 3:
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
				p = battle(party, cptr, p, choice);
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

void update(double dt)
{
	// get the delta time
	g_dElapsedTime += dt;
	g_dDeltaTime = dt;

	switch (g_eGameState)
	{
	case S_SPLASHSCREEN: splashScreenWait(); // game logic for the splash screen
		break;
	case S_MENU:
		menu(cptr, p, party, namelist);
		break;
	case S_GAME: updateGame(); // gameplay logic when we are in the game
		break;
	}
}



