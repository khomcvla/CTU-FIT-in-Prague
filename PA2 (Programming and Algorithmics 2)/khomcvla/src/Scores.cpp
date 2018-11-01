/*!
 \file Load and write scores
 */

//=================================================================================================
// Standart libraries
#include <fstream>
#include <sstream>

// Personal libraries
#include "Exceptions.hpp"
#include "vars.hpp"

//=================================================================================================
/*!
    Loading first 5 the best players
    \throw Load_Exception() if can not open files
*/
void                LoadScores                          ( void )
{
    ifstream fin ("src/scores/scores.txt");

    if (fin.is_open())
    {
        // Cursor to begin
        fin.seekg(0, ios::beg);
        fin.clear();

        int i = 0;
        char symbol;
        string sc;

        while (!fin.eof())
        {

            fin.get(symbol);

            if (symbol != '\n')
            {
                sc += symbol;
            }
            else
            {
                sc += '\0';
                istringstream ( sc ) >> PLAYERS[i];
                i++;
                sc = "";
            }
        }

        fin.close();
    }
    else
    {
        throw Load_Exception();
    }
}

//=================================================================================================
/*!
    Write score
    \throw Load_Exception() if can not open files
*/
void                WriteScores                         ( void )
{
    for (int i = 0; i < 5; i++)
    {
        if (SCORE > PLAYERS[i])
        {
            PLAYERS[i] = SCORE;
            break;
        }
    }

    // Open out file
    ofstream fout ("src/scores/scores.txt");

    if (fout.is_open()) 
    {
        for (int i = 0; i < 5; i++)
        {
            fout << PLAYERS[i] << endl;
        }

        fout.close();
    }
    else
    {
        throw Write_Exception();
    }
}