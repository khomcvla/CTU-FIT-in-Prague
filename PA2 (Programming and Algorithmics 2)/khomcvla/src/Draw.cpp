/*!
  \file Drawing what is happening on the screen
 */

//=================================================================================================
// SDL libraries (music)
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

// OpenGL libraries
#include <GL/glut.h>

// Standart libraries
#include <cmath>
#include <string>

// Personal libraries
#include "Ball.hpp"
#include "Brick.hpp"
#include "Bonus.hpp"
#include "Exceptions.hpp"
#include "vars.hpp"

//=================================================================================================
/*!
    Drawing HP, LVL and etc....
    \param text,length
    \param x,y position
    \param mode style
*/
void                DrawText                            ( const char * text, 
                                                          const int    length, 
                                                          const int    x, 
                                                          const int    y, 
                                                          const int    mode )
{
    double *matrix = new double[50];

    glMatrixMode(GL_PROJECTION);
    glGetDoublev(GL_PROJECTION_MATRIX, matrix);
    glLoadIdentity();
    glOrtho(0, 800, 0, 600, -5, 5);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glLoadIdentity();
    glRasterPos2i(x, y);


    for (int i = 0; i < length; i++)
    {
        if (mode == 0)
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, (int)text[i]);
        else if (mode == 1)
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)text[i]);
        else
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)text[i]);
    }

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixd(matrix);
    glMatrixMode(GL_MODELVIEW);

    delete [] matrix;
}

//=================================================================================================
/*!
    Draws what is happening at the moment / Render
*/
void                Draw                                ( void )
{
    //-------------------------------------------------
    // Drawing raket
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3ub(80, 160, 160);
    glRectf(r_x, r_y, r_x + r_w, r_y + r_h);

    //-------------------------------------------------
    // Drawing info line
    glBegin(GL_LINES);

    glVertex2f(75, 0);
    glVertex2f(75, 500);
    
    glEnd();

    glColor3f(1.0, 0.0, 0.0);

    //-------------------------------------------------
    // Drawing ball
    glBegin(GL_POLYGON);

    for (float i = 0; i < 2 * 3.14; i += 3.14 / 4)
        glVertex2f(ball.x + ball.r * sin(i), ball.y + ball.r * cos(i));

    glEnd();

    //-------------------------------------------------
    // Drawing blocks
    glBegin(GL_QUADS);
    
    for ( int i = 0; i < BLOCK_H; i++)
    {
        glColor3ub(i * 10, i * 20, 160);

        for (int j = 0; j < BLOCK_W; j++)
        {
            Brick &b = brick[i][j];

            if (b.active)
            {
                glVertex2f(b.col * b.w + 1, b.row * b.h + 1);
                glVertex2f(b.col * b.w + b.w - 1, b.row * b.h + 1);
                glVertex2f(b.col * b.w + b.w - 1, b.row * b.h + b.h - 1);
                glVertex2f(b.col * b.w + 1, b.row * b.h + b.h - 1);
            }
        }
    }
    
    glEnd();

    //-------------------------------------------------
    // LEGEND
    string HP;
    string LVL;
    string SCR;
    string BLOCKS;

    //-------------------------------------------------
    // TITLES
    if (LEVEL == 0)
    {
        LVL     = "LEVEL  :";
        HP      = "HEALTH :";
        BLOCKS  = "BLOCKS :";
        SCR     = "SCORE  :";
    }
    else if (LEVEL == 6)
    {
        LVL     = "LEVEL  :";
        HP      = "HEALTH :";
        BLOCKS  = "BLOCKS :";
        SCR     = "SCORE  : " + to_string(SCORE);
    }
    else
    {
        LVL     = "LEVEL  : " + to_string(LEVEL);
        SCR     = "SCORE  : " + to_string(SCORE);
        HP      = "HEALTH : " + to_string(HEALTH);
        BLOCKS  = "BLOCKS : " + to_string(COUNT_BRICK);
    }

    //-------------------------------------------------
    // START
    if (LEVEL == 0)
    {
        DrawText(TITLE.data(),  TITLE.size(),  430, 400, 2);
        DrawText(START.data(),  START.size(),  365, 300, 2);
        DrawText(SELECT.data(), SELECT.size(), 365, 250, 2);
    }

    //-------------------------------------------------
    // STATUS
    DrawText(STATUS.data(),  STATUS.size(),  65, 580, 1);
    DrawText(LVL.data(),     LVL.size(),     15, 550, 0);
    DrawText(HP.data(),      HP.size(),      15, 520, 0);
    DrawText(BLOCKS.data(),  BLOCKS.size(),  15, 490, 0);
    DrawText(SCR.data(),     SCR.size(),     15, 460, 0);

    //-------------------------------------------------
    // BEST PLAYERS
    DrawText(BEST.data(),    BEST.size(),    30, 420, 1);
    for (int i = 0; i < 5; i++)
    {
        if (PLAYERS[i] != -1)
            DrawText(to_string(PLAYERS[i]).data(), to_string(PLAYERS[i]).size(), 15, 420 - (i + 1) * 40, 0);
        else
            DrawText(ERROR.data(), ERROR.size(), 15, 420 - (i + 1) * 40, 0);
    }

    //-------------------------------------------------
    // LEGEND
    DrawText(LEGEND.data(), LEGEND.size(), 65, 190, 1);
    DrawText(MOVE.data(),   MOVE.size(),   15, 160, 1);
    DrawText(SPACE.data(),  SPACE.size(),  15, 130, 1);
    DrawText(F1.data(),     F1.size(),     15, 100, 1);
    DrawText(F2.data(),     F2.size(),     15, 70,  1);
    DrawText(F12.data(),    F12.size(),    15, 40,  1);

    //-------------------------------------------------
    // BONUS
    if (BONUS_ACTIVE) 
        DrawText(BONUS.data(),   BONUS.size(), 455, 70, 1);

    //-------------------------------------------------
    // LEVEL
    if (LEVEL == 6)
    {
        DrawText(WIN.data(),     WIN.size(),     390, 390, 2);
        DrawText(SCR.data(),     SCR.size(),     450, 320, 2);
        DrawText(EXIT.data(),    EXIT.size(),    380, 250, 2);
        DrawText(RESTART.data(), RESTART.size(), 385, 200, 2);
    }

    glutSwapBuffers();
}