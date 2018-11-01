/*!
  \mainpage Semestrial project Arkanoid
  \author Khomchenko Vladislav (khomcvla)
  \version 1.0
  \date June 2017
  
  \section info_sec General info
  This project is a variation of classic game Arkanoid. 
  The game consists of 5 levels on the maps and every next level is harder than previous. 
  Top 5 highscores is saved in the game. 
  Player can upload his own maps from the project_directory/src/levels. 
  For further information read "zadani.txt". 
  
  \section controls_sec Game controls
  WASD or ARROWS - move. 
  F1 -  return to menu.
  F2 - off/on music 
  F12 - quit game
  SPACE - start 
 */

//=================================================================================================
// SDL libraries (music)
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

// OpenGL libraries
#include <GL/glut.h>

// Standart libraries
#include <cmath>
#include <ctime>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

// Personal libraries
#include "Ball.hpp"
#include "Brick.hpp"
#include "Bonus.hpp"
#include "Exceptions.hpp"
#include "vars.hpp"

using namespace std;

//=================================================================================================
/*! 
Checks if two items hits 
\param Ball,Brick objects for bumps
\return true or false
 */
bool                isCollision                         ( const Ball  & b,
                                                          const Brick & br )
{
    float x = b.x, y = b.y, r = b.r, c = br.col, w = br.w, row = br.row, h = br.h; ///< racket and ball coordinates

    //----------------------------------------------------------------------------
    if (br.active)
    {
        if ( abs(x - c * w - w / 2 - 2) <= r + w / 2 &&
             abs(y - row * h - h / 2 - 2) <= r + h / 2 )
        {
            if ( sqrt ((c * w + w / 2 - x) * (c * w + w / 2 - x) + (row * h + h / 2 - y) * (row * h + h / 2 - y))
                 - (w / 2 - 1) * sqrt(2.0) - r > r * (sqrt(2.0) - 1) )
                return 0;
            else
                return 1;
        }
    }

    return 0;
}

//=================================================================================================
/*! 
Timer for animation 
 */
void                Timer                               ( const int )
{

    //-------------------------------------------------
    // Control bonus
    if (BONUS_ACTIVE)
    {
        TIMER_CNT++;
        
        if (BONUS_NUMBER != 1)
        {
            if (TIMER_CNT == 300)
            {
                BONUS_ACTIVE = false;
                TIMER_CNT = 0;
            }
        }
        else
        {
            if (TIMER_CNT == 30)
            {
                BONUS_ACTIVE = false;
                TIMER_CNT = 0;
            }
        }
    }

    //-------------------------------------------------
    // Control level
    if (LEVEL == 0 || LEVEL == 6)
    {
        ball.x = r_x + r_w / 2;
        ball.y = r_y - ball.r;
        LoadLevel(LEVEL);
    }
    else if (COUNT_BRICK <= 0) // end of level
    {
        LEVEL++;
        ball.active = false;
        LoadLevel(LEVEL);
    }
    else if (!ball.active)
    {
        ball.x = r_x + r_w / 2;
        ball.y = r_y - ball.r;
    }
    else
    {
        ball.Move();

        for (int i = 0; i < BLOCK_H; i++)
        {
            for (int j = 0; j < BLOCK_W; j++)
            {
                Brick &b = brick[i][j];

                if (isCollision(ball, b))
                {
                    if (abs(ball.x - b.col * b.w - b.w / 2) < abs(ball.y - b.row * b.h - b.h / 2))
                    {
                        ball.dy *= -1;
                    }
                    else if (abs(ball.x - b.col * b.w - b.w / 2) > abs(ball.y - b.row * b.h - b.h / 2))
                    {
                        ball.dx *= -1;
                    }
                    else
                    {
                        if (ball.dx > 0)
                        {
                            if (ball.x < b.col * b.w + 1)
                                ball.dx *= -1;
                        }
                        else
                        {
                            if (ball.x > (b.col + 1)*b.w - 1)
                                ball.dx *= -1;
                        }

                        if (ball.dy > 0)
                        {
                            if (ball.y < b.row * b.h + 1)
                                ball.dy *= -1;
                        }
                        else if (ball.y > (b.row + 1)*b.h - 1)
                        {
                            ball.dy *= -1;
                        }
                    }

                    if (--b.hit == 0 )
                    {
                        if (Mix_PlayChannel( -1, jump, 0 ) == -1) throw Music_Exception();

                        // bumps
                        b.active = false;

                        COUNT_BRICK--;

                        //-------------------------------------------------
                        if (LEVEL != 0)
                        {
                            List_Bonus[COUNT_BRICK]->GetBonus();

                            int BN = List_Bonus[COUNT_BRICK]->GetNumber();

                            if (BN == 1)
                            {
                                BONUS = "BONUS: SPEED 1.5x";
                                if (Mix_PlayChannel( -1, bon, 0 ) == -1) throw Music_Exception();
                            }
                            else if (BN == 2)
                            {
                                BONUS = "BONUS: +150 SCORE";
                                if (Mix_PlayChannel( -1, bon, 0 ) == -1) throw Music_Exception();
                            }
                            else if (BN == 3)
                            {
                                BONUS = "BONUS: +1 HEALTH";
                                if (Mix_PlayChannel( -1, bon, 0 ) == -1) throw Music_Exception();
                            }
                            else
                            {
                                BONUS = "";
                            }
                            
                            BONUS_NUMBER = BN;

                            if (SCORE < 0) SCORE = 0;
                        }

                        //-------------------------------------------------
                        if (COUNT_BRICK <= 0)
                        {
                            LEVEL++;
                            ball.active = false;
                            LoadLevel(LEVEL);
                        }
                    }

                    goto draw_goto;
                }
            }
        }
    }

    draw_goto:

    Draw();

    glutTimerFunc(TIMEOUT, Timer, 0);
}

//=================================================================================================
/*! 
Load level's random bonuses to the vector
\param R which bonus will add
 */
void                LoadBonus                           ( const int R )
{
    if (R ==  0) List_Bonus.push_back(new TimeoutBonus());
    else if (R == 10) List_Bonus.push_back(new ScoreBonus());
    else if (R == 20) List_Bonus.push_back(new HealthBonus());
    else              List_Bonus.push_back(new NeutralBonus());
}

//=================================================================================================
/*! 
Load current level
Reads from file (./levels + <number_level>)
\param number level number
 */
void                LoadLevel                           ( const int number )
{
    //-------------------------------------------------
    // Default settings
    List_Bonus.clear();

    TIMEOUT = 25;
    COUNT_BRICK = 0;
    HEALTH  = MAX_HEALTH;

    for (int i = 0; i < BLOCK_H; i++)
    {
        for (int j = 0; j < BLOCK_W; j++)
        {
            brick[i][j].active = false;
            brick[i][j].hit = 1;
        }
    }

    //-------------------------------------------------
    // Load new level from file

    ifstream fin ("src/levels/" + to_string(LEVEL) + ".lvl");

    if (LEVEL != 0 && LEVEL != 6)
    {
        if (fin.is_open())
        {
            // Cursor to begin
            fin.seekg(0, ios::beg);
            fin.clear();

            int i = 0, j = 0;
            char symbol;

            while (!fin.eof())
            {
                fin.get(symbol);

                if (symbol == 'X')
                {
                    brick[i][j].active = true;
                    brick[i][j].col = j;
                    brick[i][j].row = i;

                    // Load random bonuses
                    LoadBonus(rand() % 25);

                    j++;
                    COUNT_BRICK++;
                }
                else if (symbol == '\n')
                {
                    i++;
                    j = 0;
                }
                else
                {
                    j++;
                }
            }

            // Close file
            fin.close();
        }
        else
        {
            throw Load_Exception();
        }
    }
}

//=================================================================================================
/*! 
Clear all chunks, audio and etc...
 */
void                ClearAndExit                        ( void )
{
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);

    //Free the sound effects
    Mix_FreeChunk( bon );
    Mix_FreeChunk( jump );
    Mix_FreeMusic( background);
    
    Mix_CloseAudio();

    jump       = NULL;
    bon        = NULL;
    background = NULL;

    //Quit SDL subsystems
    Mix_Quit();
    SDL_Quit();

    exit(0);
}

//=================================================================================================
/*!
Load all sounds, create textures and launch it.
 */
int                 main                                ( int     argc,
                                                          char ** argv )
{
    srand ( time(NULL) );

    try
    {
        // Load music + graphic
        LoadSDL();
        LoadGL(argc, argv);

        // Create bricks / load level
        LoadLevel(LEVEL);

        // Load first 5 the best players
        LoadScores();

        // Start play background music
        if (Mix_PlayMusic(background, -1) == -1) throw Music_Exception();

        // Start rendering
        glutMainLoop();

    }
    catch (SDL_Exception sdlex)
    {
        cout << "SDL_Exception!" << endl;
        cout << "SDL could not initialize! SDL Error:" << SDL_GetError() << endl;
        cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;

        ClearAndExit();
    }
    catch (GL_Exception glexp)
    {
        cout << "GL_Exception!" << endl;
        ClearAndExit();
    }
    catch (Level_Exception lvlex)
    {
        cout << "Level_Exception!" << endl;
        cout << "Can not open/close files. Check sources!" <<endl;
        ClearAndExit();
    }
    catch (Load_Exception loadex)
    {
        cout << "Load_Exception!" << endl;
        cout << "Can not load source files!" << endl;
        ClearAndExit();
    }
    catch (Music_Exception musex)
    {
        cout << "Music_Exception" << endl;
        cout << "Mix_PlayChannel: " << Mix_GetError() << endl;
        ClearAndExit();
    }
    catch (...)
    {
        cout << "Unknown exception!" << endl;
        ClearAndExit();
    }

    return 0;
}
