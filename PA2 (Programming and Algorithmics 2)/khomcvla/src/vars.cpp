/*!
 \file Initializing variables
 */

//=================================================================================================
// SDL libraries (music)
#include <SDL2/SDL_mixer.h>

#include <vector>
#include <string>

// Personal libraries
#include "Ball.hpp"
#include "Brick.hpp"
#include "Bonus.hpp"
#include "Exceptions.hpp"

using namespace std;

#define BLOCK_W     20
#define BLOCK_H     15
#define MAX_HEALTH  3

//=================================================================================================
// External variables
float   r_x             = 110.0;        // raket's coordinate X
float   r_y             = 290.0;        // raket's coordinate Y
float   r_w             = 50;           // raket's width
float   r_h             = 8.0;          // raket's height

int     LEVEL           = 0;            // level for the start
int     SCORE           = 0;
int     TIMEOUT         = 25;           // ball's speed
int     HEALTH          = MAX_HEALTH;   // HEALTH

bool    BONUS_ACTIVE    = false;
int     BONUS_NUMBER    = 0;

//=================================================================================================
// Local variables
int     TIMER_CNT       = 0;
int     PLAYERS[5];                     // 5 the best players
int     COUNT_BRICK;                    // counter of bricks

//=================================================================================================
// Create new loading items
Ball    ball(5);
Brick   brick[15][20];

vector <Bonus*>  List_Bonus;

//=================================================================================================
// Music variables
Mix_Chunk *jump       = NULL;
Mix_Chunk *bon        = NULL;
Mix_Music *background = NULL;

//=================================================================================================
// Legend declaration
string TITLE   = "ARKANOID 1.0";
string STATUS  = "STATUS";
string LEGEND  = "LEGEND";
string TRANING = "TRANING";
string BEST    = "BEST PLAYERS";
string MOVE    = "MOVE : A/D/LE/RA";
string SPACE   = "START: 'SPACE'";
string SELECT  = "OR SELECT LEVEL: 2/3/4/5";
string MODE    = "FASTER: 'F' ";
string ERROR   = "ERROR LOAD SCORE";
string WIN     = "CONGRATULATIONS!";
string EXIT    = "PRESS 'SPACE' TO EXIT";
string START   = "PRESS 'SPACE' TO START";
string RESTART = "PRESS 'R' TO RESTART";
string F12     = "EXIT : F12";
string F1      = "MENU : F1";
string F2      = "SOUND: F2";
string BONUS;