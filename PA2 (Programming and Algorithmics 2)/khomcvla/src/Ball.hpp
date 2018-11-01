/*!
 \file Contains declaration part of classes Ball
 */

//=================================================================================================
#pragma once

//=================================================================================================
class Ball
{
    public:
    //---------------------------------------------------------------
                    Ball                                ( float _r )
                    : x(), 
                      y(), 
                      r(_r),
                      dx(), 
                      dy(), 
                      active(false) {}
    
    //---------------------------------------------------------------
    void            Move                                ( void );
    
    //---------------------------------------------------------------
    float           x;///< Coordinates of the ball
    float           y;///< Coordinates of the ball
    float           r;///< Radious of the ball
    float           dx;///<Size of the ball
    float           dy;///<Size of the ball
    bool            active; ///< Moving or not
};