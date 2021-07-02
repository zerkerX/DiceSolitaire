#pragma once
#include "limits.h"
#include "blackdice.h"
#include "whitedice.h"

#include <Sprites.h>
#include "Dice.hpp"

class Board
{
protected:
    Dice contents[NUMROW][NUMCOL] = {EMPTY};
    
public:
    Board()
    {
        for (int i = 0; i < 6; i++)
        {
            contents[0][i] = WHITE_1 + i;
            contents[1][i] = BLACK_1 + i;
        }
    }
    
    void draw()
    {
        Dice value;
        for (int row = 0; row < NUMROW; row++)
        {
            for (int col = 0; col < NUMCOL; col++)
            {
                value = contents[row][col];
                if (value >= WHITE_1 && value <= WHITE_6)
                    Sprites::drawOverwrite(col * 12, row * 12, 
                            whitedice, value - WHITE_1);
                else if (value >= BLACK_1 && value <= BLACK_6)
                    Sprites::drawOverwrite(col * 12, row * 12, 
                            blackdice, value - BLACK_1);
            }
        }
    }
};
