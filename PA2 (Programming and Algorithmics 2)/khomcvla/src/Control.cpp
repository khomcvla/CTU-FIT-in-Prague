/*!
 \file Control elements
 */

//=================================================================================================
// OpenGL libraries
#include <GL/glut.h>

// Personal libraries
#include "vars.hpp"

//=================================================================================================
/*!
    If mouse pressed and start ball
*/
void                MousePress                          ( const int button,
                                                          const int state,
                                                          const int x,
                                                          const int y )
{
    if (button == GLUT_LEFT_BUTTON && !ball.active)
    {
        ball.active = true;
        ball.dx = 4;
        ball.dy = -4;
    }
}

//=================================================================================================
/*!
    Coordinates of mouse for mouse control
*/
void                Mouse                               ( const int ax,
                                                          const int ay )
{
    //-------------------------------------------------
    r_x = ax - 100;

    //-------------------------------------------------
    // Controll borders (LEFT)
    if (r_x <= 79)
    {
        r_x = 77;
    }
    else if (r_x >= 250) // Controll borders (RIGHT)
    {
        r_x = 248;
    }

    //-------------------------------------------------
    if (!ball.active)
    {
        ball.x = r_x + r_w / 2;
        ball.y = r_y - ball.r;
    }
}

//=================================================================================================
/*!
    Keyboard
    Called when the user presses the ASCII code generator
    All letters, numbers, brackets, plus, equals
    Enter, Delete
    etc...
*/
void                Keyboard                            ( unsigned char key,
                                                          const int     x,
                                                          const int     y )
{
    key = toupper(key);

    switch (key)
    {
    //--------------------------------
    case 'A':
        // Controll borders (LEFT)
        if (r_x - 40 <= 75)
        {
            r_x = 77;
        }
        else
        {
            r_x -= 40;
        }
        break;
    //--------------------------------
    case 'D':
        // Controll borders (RIGHT)
        if (r_x + 40 >= 250)
        {
            r_x = 248;
        }
        else
        {
            r_x += 40;
        }
        break;
    //--------------------------------
    case 'R':
        if (LEVEL == 6)
        {
            SCORE = 0;
            HEALTH = MAX_HEALTH;
            LEVEL = 0;
            LoadLevel(LEVEL);
        }
    //--------------------------------
    case ' ':
        if (LEVEL == 6)
        {
            ClearAndExit();
        }
        else if (LEVEL == 0)
        {
            LEVEL++;
            LoadLevel(LEVEL);
        }
        else if (!ball.active)
        {
            ball.active = true;
            ball.dx = 4;
            ball.dy = -4;
        }
        break;
    //--------------------------------
    case '2':
        if (LEVEL == 0)
        {
            LEVEL = 1;
        }
        break;
    //--------------------------------
    case '3':
        if (LEVEL == 0)
        {
            LEVEL = 2;
        }
        break;
    //--------------------------------
    case '4':
        if (LEVEL == 0)
        {
            LEVEL = 3;
        }
        break;
    //--------------------------------
    case '5':
        if (LEVEL == 0)
        {
            LEVEL = 4;
        }
        break;
    }
}

//=================================================================================================
/*!
    SKeyboard
    Called when ASCII code is not generated
    F1 - F12, control keys (up, down, right, left)
    Insert, Home, PageUp, PageDown, End
    etc...
*/
void                SKeyboard                           ( const int key,
                                                          const int x,
                                                          const int y )
{
    switch (key)
    {
    //--------------------------------
    case GLUT_KEY_LEFT:
        if (r_x - 40 <= 75)
        {
            r_x = 77;
        }
        else
        {
            r_x -= 40;
        }
        break;
    //--------------------------------
    case GLUT_KEY_RIGHT:
        if (r_x + 40 >= 250)
        {
            r_x = 248;
        }
        else
        {
            r_x += 40;
        }
        break;
    //--------------------------------
    case GLUT_KEY_F1:
        {
            LEVEL = 0;
            LoadLevel (LEVEL);
        }
        break;
        
    //--------------------------------
    case GLUT_KEY_F12:
        if (LEVEL != 6)
        {
            ClearAndExit();
        }
        break;
    //--------------------------------
    case GLUT_KEY_F2:
        if (!Mix_PlayingMusic())
            Mix_PlayMusic(background, -1);
        else if (Mix_PausedMusic())
            Mix_ResumeMusic();
        else 
            Mix_PauseMusic();
    }
}