#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"
#include "player.h"
#include "Companion.h"
#include <string>
extern CStopWatch g_swTimer;
extern bool g_bQuitGame;

// struct to store keyboard events
// a small subset of KEY_EVENT_RECORD
struct SKeyEvent
{
    bool keyDown;
    bool keyReleased;
};

// Enumeration to store the control keys that your game will have
enum EKEYS
{
    K_UP,
    K_DOWN,
    K_LEFT,
    K_RIGHT,
    K_ESCAPE,
    K_SPACE,
    K_ENTER,
    K_Q,
    K_COUNT
};

// Enumeration for the different screen states
enum EGAMESTATES
{
    S_SPLASHSCREEN,
    S_MENU,
    S_BATTLE,
    S_BATTLEN,
    S_GAME,
    S_COUNT,
    S_BEFOREBATTLEN
};

// struct for the game character
struct SGameChar
{
    COORD m_cLocation;
    bool  m_bActive;
};

void init(void);      // initialize your variables, allocate memory, etc
void getInput(void);      // get input from player
void update(double dt); // update the game and the state of the game
void render(void);      // renders the current state of the game to the console
void shutdown(void);      // do clean up, free memory

void splashScreenWait();    // waits for time to pass in splash screen
void updateGame();          // gameplay logic      // moves the character, collision detection, physics, etc
void processUserInput();    // checks if you should change states or do something else with the game, e.g. pause, exit
void clearScreen();         // clears the current screen and draw from scratch ;
void renderFramerate();     // renders debug information, frame rate, elapsed time, etc
void renderToScreen();      // dump the contents of the buffer to the screen, one frame worth of game
void renderMenuEvents(int choice, int screen);
void RenderBattleEvents(int stagepicked);
// renders the status of input events
int menu();
// keyboard and mouse input event managers
void keyboardHandler(const KEY_EVENT_RECORD& keyboardEvent);  // define this function for the console to call when there are keyboard events

void gameplayKBHandler(const KEY_EVENT_RECORD& keyboardEvent);   // handles keyboard events for gameplay 

//render storyline narration

void renderstorylinestage1act1part1(int x, int y);
void renderstorylinestage1act1part2(int x, int y);
void renderstorylinestage1act2(int x, int y);
void renderstorylinestage2act1part1(int x, int y);
void renderstorylinestage2act1part2(int x, int y);
void renderstorylinestage2act2(int x, int y);
void renderstorylinestage3act1part1(int x, int y);
void renderstorylinestage3act1part2(int x, int y);
void renderstorylinestage3act2(int x, int y);
void renderstorylinestage4act1part1(int x, int y);
void renderstorylinestage4act1part2(int x, int y);
void renderstorylinestage4act2(int x, int y);
void renderstorylineend(int x, int y);
void renderstorylinetutorialact1(int x, int y);
void renderstorylinetutorialact2(int x, int y);
#endif // _GAME_H
