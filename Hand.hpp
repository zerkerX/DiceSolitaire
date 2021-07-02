#pragma once
#include "Dice.hpp"

#include "cursor.h"
#include "limits.h"

#include <Sprites.h>

class Hand
{
protected:
    int x = 0, y = 0;
    Dice holding[10];
    
public:
    Hand() {}
    
    void draw()
    {
        Sprites::drawPlusMask(x * 12, y * 12, cursor, 0);
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
};
