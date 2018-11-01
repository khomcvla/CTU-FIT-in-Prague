/*!
 \file Contains declaration part of classes Bonus
 */

//=================================================================================================
#pragma once

//=================================================================================================
/*!
 \brief Represents one brick's bonus
*/
class Bonus
{
    public:

                    Bonus                               ( int N )
                    :m_Number(N){}

                   ~Bonus                               ( void ){}

    int             GetNumber                           ( void ) const;
    virtual void    GetBonus                            ( void ) const = 0;

    protected:

    int             m_Number;
};

//=================================================================================================
/*!
 \brief Represents one TimeoutBonus
*/
class TimeoutBonus : public Bonus
{
    public:
                    TimeoutBonus                        ( void )
                    : Bonus(1){}

                   ~TimeoutBonus                        ( void ){}

    /*!
        \brief Activate TimeoutBonus
        \details speed 1.5x
    */
    void            GetBonus                            ( void ) const;
};

//=================================================================================================
/*!
 \brief Represents one ScoreBonus
*/
class ScoreBonus : public Bonus
{
    public:

                    ScoreBonus                          ( void )
                    : Bonus(2){}

                   ~ScoreBonus                          ( void ){}
                    
    /*!
        \brief Activate ScoreBonus
        \details +150 scores
    */
    void            GetBonus                            ( void ) const;
};

//=================================================================================================
/*!
 \brief Represents one HealthBonus
*/
class HealthBonus : public Bonus
{
    public:

                    HealthBonus                         ( void )
                    : Bonus(3){}

                   ~HealthBonus                         ( void ){}
          
    /*!
        \brief Activate HealthBonus
        \details +1 health
    */
    void            GetBonus                            ( void ) const;
};

//=================================================================================================
/*!
 \brief Represents one NeutralBonus
*/
class NeutralBonus : public Bonus
{
    public:

                    NeutralBonus                        ( void )
                    : Bonus(4){}

                   ~NeutralBonus                        ( void ){}

    /*!
        \brief Activate NeutralBonus
        \details +25 scores
    */
    void            GetBonus                            ( void ) const;
};