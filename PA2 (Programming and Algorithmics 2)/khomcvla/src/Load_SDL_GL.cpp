/*!
  \file Load SDL and GL libraries and create windows, game objects, music and sound effects
 */

//=================================================================================================
// SDL libraries (music)
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

// OpenGL libraries
#include <GL/glut.h>

// Personal libraries
#include "Ball.hpp"
#include "Brick.hpp"
#include "Bonus.hpp"
#include "Exceptions.hpp"
#include "vars.hpp"

//=================================================================================================
/*!
    \brief Load background music and sound effects
    \throw SDL_Exception() when error during load sound and music
 */
void                LoadMusic                           ( void )
{
    // Load sound effects
    jump = Mix_LoadWAV("src/audio/ball.wav");
    bon  = Mix_LoadWAV("src/audio/bonus.wav");
    if ( jump == NULL || bon == NULL )
    {
        throw SDL_Exception();
    }

    // Load background music
    background = Mix_LoadMUS("src/audio/back.wav");
    if ( jump == NULL )
    {
        throw SDL_Exception();
    }

    Mix_AllocateChannels(40);
}

//=================================================================================================
/*! 
    \brief Initialize matrix
*/
void                Init                                ( void )
{
    //-------------------------------------------------
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glOrtho(0, 300, 300, 0, 1, 0);

    //-------------------------------------------------
    glMatrixMode(GL_MODELVIEW);
    glTranslatef(50.0, 0.0, 0.0);
}

//=================================================================================================
/*!
    \brief \brief Load sounds effects and music
    \throw SDL_Exception() if can not initialize SDL audio system or SDL mixer
*/
void                LoadSDL                             ( void )
{
    // Initialize SDL audio system
    if ( SDL_Init(SDL_INIT_AUDIO ) < 0 )
    {   
        throw SDL_Exception();
    }

    // Initialize SDL mixer
    if ( Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {   
        throw SDL_Exception();
    }

    LoadMusic();
}

//=================================================================================================
/*! 
    \brief Load graphic
    \param argc argv gives from main.cpp
*/
void                LoadGL                              ( int argc, char **argv )
{
    // Initialization GLUT
    glutInit(&argc, argv);
    glutInitWindowSize(700, 400);
    glutInitWindowPosition(250, 100);

    // Open window
    glutCreateWindow("Arkanoid by khomcvla");

    // Turn mode
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    // Registration called functions
    glutDisplayFunc(Draw);

    // Need for animation
    glutTimerFunc(TIMEOUT, Timer, 0);

    // Activate keyboard mode
    glutKeyboardFunc(Keyboard);
    glutSpecialFunc(SKeyboard);

    // Activate mouse mode
    glutPassiveMotionFunc(Mouse);
    glutMouseFunc(MousePress);

    // Hide cursor
    glutSetCursor(GLUT_CURSOR_NONE);

    // Initialization and start
    Init();
}