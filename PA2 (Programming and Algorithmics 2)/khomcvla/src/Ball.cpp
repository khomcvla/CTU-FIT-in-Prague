/*!
    \file Implementation of ball actions
*/

//=================================================================================================
// Personal libraries
#include "Ball.hpp"
#include "vars.hpp"
#include "Exceptions.hpp"

//=================================================================================================
/*!
    Ball's bumps
    \throw SDL_Exception() if can not load audio
*/
void                Ball::Move                          ( void )
{
    x += dx;
    y += dy;

    if (x - r <= 75) // left
    {
        x = 80;
        dx *= -1;
        if (Mix_PlayChannel( -1, jump, 0 ) == -1) throw SDL_Exception();
    }
    else if (y - r <= 0) // right
    {
        y = r;
        dy *= -1;
        if (Mix_PlayChannel( -1, jump, 0 ) == -1) throw SDL_Exception();
    }
    else if (x + r >= 300) // raket
    {
        x = 300 - r;
        dx *= -1;
        if (Mix_PlayChannel( -1, jump, 0 ) == -1) throw SDL_Exception();
    }
    else if (y + r >= r_y && y + r <= r_y + r_h && x > r_x && x < r_x + r_w)
    {
        y = r_y - r;
        dy *= -1;
        if (Mix_PlayChannel( -1, jump, 0 ) == -1) throw SDL_Exception();
    }
    else if (y > 300) // down
    {
        if (LEVEL != 0) HEALTH--;

        if (HEALTH == 0 && LEVEL != 6 && LEVEL != 0)
        {
            WriteScores();
            LEVEL = 6;
            LoadLevel(LEVEL);
        }

        TIMEOUT = 25;
        active = false;
    }
}