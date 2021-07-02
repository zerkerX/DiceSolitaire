#pragma once
#include "Dice.hpp"
#include "Board.hpp"

#include "cursor.h"
#include "limits.h"

#include <Sprites.h>

class Hand
{
protected:
    int x = 0, y = 0;
    bool empty = true;
    Dice holding[NUMCOL] = {EMPTY};
    
public:
    Hand() {}
    
    void draw()
    {
        if (empty)
        {
            Sprites::drawPlusMask(x * 12, y * 12, cursor, 0);
        }
        else
        {
            Dice value;
            for (int pos = 0; pos < NUMCOL; pos++)
            {
                value = holding[pos];
                if (value >= WHITE_1 && value <= WHITE_6)
                    Sprites::drawOverwrite((x + pos) * 12 + 4, y * 12, 
                            whitedice, value - WHITE_1);
                else if (value >= BLACK_1 && value <= BLACK_6)
                    Sprites::drawOverwrite((x + pos) * 12 + 4, y * 12, 
                            blackdice, value - BLACK_1);
            }
            Sprites::drawPlusMask(x * 12 + 4, y * 12, cursor, 0);
        }
    }
    
    void up()
    {
        y--;
        if (y < MINROW) y = MINROW;
    }
    
    void down()
    {
        y++;
        if (y > NUMROW) y = NUMROW;
    }
    
    void left()
    {
        x--;
        if (x < MINCOL) x = MINCOL;
    }
    
    void right()
    {
        x++;
        if (x > NUMCOL) x = NUMCOL;
    }
    
    void grab(Board & board)
    {
        if (empty)
        {
            board.grab(x, y, holding);
            if (holding[0] != EMPTY) empty = false;
        }
        else
        {
            if (board.place(x, y, holding)) empty = true;
        }
    }
};
