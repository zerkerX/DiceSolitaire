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
    
    /** Copies the data from the indicated position and to the right
     * of it into the outarr.
     * Assumes outarray is at least NUMCOL in size, and that it is
     * initially filled with EMPTY prior to calling this function.
     * */
    void grab(int col, int row, Dice * outarr)
    {
        for (int pos = 0; pos < NUMCOL && pos + col < NUMCOL; pos++)
        {
            outarr[pos] = contents[row][col + pos];
            contents[row][col + pos] = EMPTY;
        }
    }

    /** Copies the data from the input array to the indicated position
     * on the board.
     * Assumes inarray is at least NUMCOL in size.
     * 
     * Returns true if the placement is valid, false otherwise */
    bool place(int col, int row, Dice * inarr)
    {
        /* Count the number of items in the hand */
        int handsize = NUMCOL;
        for (int pos = 0; pos < NUMCOL; pos++)
        {
            if (inarr[pos] == EMPTY)
            {
                handsize = pos;
                break;
            }
        }
        
        /* Copy the data into the board, if the placement is valid */
        if (   contents[row][col] == EMPTY
            && handsize > 0
            && handsize + col < NUMCOL
            && (   col == 0 
                || contents[row][col - 1] == dice_prev_stack(inarr[0])))
        {
            for (int pos = 0; pos <= handsize; pos++)
            {
                contents[row][col + pos] = inarr[pos];
                inarr[pos] = EMPTY;
            }
            
            return true;
        }
        else
        {
            return false;
        }
    }
};
