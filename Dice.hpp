#pragma once

enum Dice {
    EMPTY = 0,
    WHITE_1,
    WHITE_2,
    WHITE_3,
    WHITE_4,
    WHITE_5,
    WHITE_6,
    WHITE_COL_2,
    WHITE_COL_3,
    WHITE_COL_4,
    WHITE_COL_5,
    WHITE_COL_6,
    BLACK_1,
    BLACK_2,
    BLACK_3,
    BLACK_4,
    BLACK_5,
    BLACK_6,
    BLACK_COL_2,
    BLACK_COL_3,
    BLACK_COL_4,
    BLACK_COL_5,
    BLACK_COL_6,
    INVALID
};

Dice dice_prev_stack(Dice item)
{
    switch (item)
    {
        case EMPTY:
        case WHITE_6:
        case BLACK_6:
        case WHITE_COL_2:
        case WHITE_COL_3:
        case WHITE_COL_4:
        case WHITE_COL_5:
        case WHITE_COL_6:
        case BLACK_COL_2:
        case BLACK_COL_3:
        case BLACK_COL_4:
        case BLACK_COL_5:
        case BLACK_COL_6:
            return INVALID;
        default:
            return item + 1;
    }
}

Dice dice_end_stack(Dice item)
{
    switch (item)
    {
        case WHITE_COL_2:
        case WHITE_COL_3:
        case WHITE_COL_4:
        case WHITE_COL_5:
        case WHITE_COL_6:
        case BLACK_COL_2:
        case BLACK_COL_3:
        case BLACK_COL_4:
        case BLACK_COL_5:
        case BLACK_COL_6:
            return item - 4;
        case WHITE_1:
        case BLACK_1:
            return item + 1;
        default:
            return INVALID;
    }
}

/* Somewhat unsafe operation; confirm with dice_end_stack first */
Dice dice_get_end_version(Dice item)
{
    return item + 5;
}
