/*!
 \file Contains declaration part of external variables that are used during the program
 */

//=================================================================================================
#pragma once

// SDL libraries (music)
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

// Standart libraries
#include <string>
#include <vector>

// Personal libraries
#include "Ball.hpp"
#include "Bonus.hpp"
#include "Brick.hpp"

using namespace std;

#define BLOCK_W     20 ///< Number of blocks down
#define BLOCK_H     15 ///< Number of blocks right
#define MAX_HEALTH  3  ///< max health

//=================================================================================================
// Extern vars
extern float r_x; ///< coordinates
extern float r_y; ///< coordinates
extern float r_w; ///< coordinates
extern float r_h; ///< coordinates
extern int HEALTH; ///<HEALTH
extern int TIMEOUT; ///<TIMEOUT
extern int LEVEL; ///<LEVEL
extern int SCORE; ///<LEVEL
extern int BONUS_ACTIVE;///<BONUS_ACTIVE
extern int COUNT_BRICK;///<COUNT_BRICK
extern int TIMER_CNT;///<TIMER_CNT
extern int BONUS_NUMBER;///<BONUS_NUMBER

extern Mix_Chunk *jump;///<jump sound
extern Mix_Chunk *bon;///<bonus sound
extern Mix_Music *background;///<background music

extern Ball    ball; 
extern Brick   brick[15][20];

extern int     PLAYERS[5];///<count of the best players
extern vector <Bonus*>  List_Bonus;///<vector to the bonuses

//=================================================================================================
// Legend declaration
extern string TITLE;
extern string STATUS;
extern string LEGEND;
extern string TRANING;
extern string BEST;
extern string MOVE;
extern string SPACE;
extern string SELECT;
extern string MODE;
extern string ERROR;
extern string WIN;
extern string EXIT;
extern string START;
extern string RESTART;
extern string F12;
extern string F1;
extern string F2;
extern string BONUS;

//=================================================================================================
// Declaration of used functions
extern void    Init            ( void );
extern void    Draw            ( void );
extern void    LoadSDL         ( void );
extern void    LoadMusic       ( void );
extern void    LoadScores      ( void );
extern void    WriteScores     ( void );
extern void    ClearAndExit    ( void );
extern void    Timer           ( const int );
extern void    LoadLevel       ( const int );
extern void    LoadBonus       ( const int );
extern void    LoadGL          ( int , char **);
extern void    Mouse           ( const int , const int );
extern bool    isCollision     ( const Ball  &, const Brick &);
extern void    SKeyboard       ( const int, const int, const int );
extern void    Keyboard        ( unsigned char, const int, const int );
extern void    MousePress      ( const int, const int, const int, const int );
extern void    DrawText        ( const char *, const int, const int, const int, const int );
