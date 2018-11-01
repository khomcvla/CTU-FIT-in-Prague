/*!
 \file Contains declaration part of classes Brick
 */

//=================================================================================================
#pragma once

//=================================================================================================
/*!
  \brief Represents one brick on the level
*/
class Brick
{
    public:
    //---------------------------------------------------------------
                    Brick                               ( short _r, 
                                                          short _c, 
                                                          float _w, 
                                                          float _h, 
                                                          short _hit )

                    : row(_r), 
                      col(_c), 
                      hit(_hit), 
                      w(_w), 
                      h(_h), 
                      active(false) {};
                      
    //---------------------------------------------------------------
                    Brick                               ( void )
                    : row(), 
                      col(), 
                      hit(1), 
                      w(15), 
                      h(15), 
                      active(false) {};                        

    //---------------------------------------------------------------
    short           row; ///< coordinates
    short           col; ///< coordinates
    short           hit; ///< hits
    float           w, h;  ///< Width, length and health
    bool            active;
};