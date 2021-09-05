#pragma once
#include "limits.h"
#include "blackdice.h"
#include "whitedice.h"
#include "blackcollapsed.h"
#include "whitecollapsed.h"

#include <Sprites.h>
#include "Dice.hpp"

class Board
{
protected:
    Dice contents[NUMROW][NUMCOL] = {EMPTY};

    /* Utility function to determine how many pieces are stored in 
     * the hand. */
    int count_hand(Dice * inarr)
    {
        int handsize = NUMCOL;
        for (int pos = 0; pos < NUMCOL; pos++)
        {
            if (inarr[pos] == EMPTY)
            {
                handsize = pos;
                break;
            }
        }
        return handsize;
    }
    
    /* Fully deletes the die at a given position, shifting all others
     * to the left */
    void delete_pos(int delpos, int row)
    {
        for (int pos = delpos; pos < NUMCOL - 1; pos++)
        {
            contents[row][pos] = contents[row][pos + 1];
        }
        contents[row][NUMCOL - 1] = EMPTY;
    }
    
    /* TODO InsertPos function too */
    
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
                else if (value >= BLACK_COL_2 && value <= BLACK_COL_6)
                    Sprites::drawOverwrite(col * 12, row * 12, 
                            blackcollapsed, 0);
                else if (value >= WHITE_COL_2 && value <= WHITE_COL_6)
                    Sprites::drawOverwrite(col * 12, row * 12, 
                            whitecollapsed, 0);
            }
        }
    }
    
    /** Copies the data from the indicated position and to the right
     * of it into the outarr.
     * Assumes outarray is at least NUMCOL in size, and that it is
     * initially filled with EMPTY prior to calling this function.
     * TODO: Do not permit grabs including completed sets!
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
        int handsize = count_hand(inarr);
        
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
    
    /* Unconditional version of place which is used to undo an unwanted
     * grab. Be careful with use of this function! */
    void put_back(int col, int row, Dice * inarr)
    {
        int handsize = count_hand(inarr);
        
        for (int pos = 0; pos <= handsize; pos++)
        {
            contents[row][col + pos] = inarr[pos];
            inarr[pos] = EMPTY;
        }
    }
    
    /** Gravity function in grabbing mode. Force the cursor to stay
     * within the populated region, unless the column is fully empty.
     * In that case, it should be on the first column. */
    int gravity_grab(int col, int row)
    {
        if (contents[row][col] == EMPTY)
        {
            for (int pos = col; pos >= 0; pos--)
            {
                if (contents[row][pos] != EMPTY)
                {
                    return pos;
                }
            }
                
            /* If the search failed, all columns are empty, so 
             * return zero. */
            return 0;
        }
        else return col; /* Position still valid */
    }
    
    /** Gravity function for placement mode. Always select the next
     * blank cell in the current row */
    int gravity_place(int col, int row)
    {
        for (int pos = 0; pos < NUMCOL; pos++)
        {
            if (contents[row][pos] == EMPTY)
            {
                return pos;
            }
        }
        
        /* If somehow fully filled (shouldn't be possible?), just
         * return the last column. */
         return NUMCOL - 1;
    }
    
    /* Checks and completes matches, with a brief animation to collapse
     * then down to a single square */
    void check_matches()
    {
        Dice value;
        for (int row = 0; row < NUMROW; row++)
        {
            for (int col = 0; col < NUMCOL; col++)
            {
                value = contents[row][col];
                if ((value == WHITE_6 || value == BLACK_6) && col < NUMCOL - 6)
                {
                    next_matches(row, col + 1, value);
                }
            }
        }
    }
    
    void next_matches(int row, int col, Dice prev_value)
    {
        Dice value;
        value = contents[row][col];
        if (dice_end_stack(value) == prev_value)
        {
            delete_pos(row, col);
            contents[row][col - 1] = dice_get_end_version(prev_value);
        }
        else if (dice_prev_stack(value) == prev_value)
        {
            next_matches(row, col + 1, value);
        }
    }
};
