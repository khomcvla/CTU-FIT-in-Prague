/*!
 \file Implementation of bonuses actions
 */

//=================================================================================================
// Game libraries
#include "Bonus.hpp"
#include "vars.hpp"

//=================================================================================================
/*!
	Return type of bonus
	\return m_Number bonus type
*/
int                 Bonus::GetNumber                    ( void ) const
{
    return m_Number;
}

//=================================================================================================
/*!
	\brief Activate TimeoutBonus
	\details speed 1.5x
*/
void                TimeoutBonus::GetBonus              ( void ) const
{
    TIMEOUT = 15;
    BONUS_ACTIVE = true;
}

//=================================================================================================
/*!
	\brief Activate ScoreBonus
	\details +150 scores
*/
void                ScoreBonus::GetBonus                ( void ) const
{
    SCORE += 150;
    BONUS_ACTIVE = true;
}

//=================================================================================================
/*!
	\brief Activate HealthBonus
	\details +1 health
*/
void                HealthBonus::GetBonus               ( void ) const
{
    HEALTH += 1;
    BONUS_ACTIVE = true;
}

//=================================================================================================
/*!
	\brief Activate NeutralBonus
	\details +25 scores
*/
void                NeutralBonus::GetBonus              ( void ) const
{
    SCORE += 25;
}

