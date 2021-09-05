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
    int grab_x = 0, grab_y = 0;
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
        if (y > NUMROW - 1) y = NUMROW - 1;
    }
    
    void left()
    {
        x--;
        if (x < MINCOL) x = MINCOL;
    }
    
    void right()
    {
        x++;
        if (x > NUMCOL - 1) x = NUMCOL - 1;
    }
    
    void grab(Board & board)
    {
        if (empty)
        {
            board.grab(x, y, holding);
            if (holding[0] != EMPTY)
            {
                grab_x = x;
                grab_y = y;
                empty = false;
            }
        }
        else
        {
            if (board.place(x, y, holding))
            {
                empty = true;
                grab_x = 0;
                grab_y = 0;
            }
        }
    }
    
    void put_back(Board & board)
    {
        /* We can only put back if we are holding anything */
        if (!empty)
        {
            board.put_back(grab_x, grab_y, holding);
            empty = true;
            grab_x = 0;
            grab_y = 0;
        }
    }
    
    /** Restricts the cursor position based on board conents so we don't
     * need to cursor in and out of blank spaces */
    void gravity(const Board & board)
    {
        if (empty)
        {
            x = board.gravity_grab(x, y);
        }
        else
        {
            x = board.gravity_place(x, y);
        }
    }
};
