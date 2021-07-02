#pragma once

enum Dice {
    EMPTY = 0,
    WHITE_1,
    WHITE_2,
    WHITE_3,
    WHITE_4,
    WHITE_5,
    WHITE_6,
    BLACK_1,
    BLACK_2,
    BLACK_3,
    BLACK_4,
    BLACK_5,
    BLACK_6,
    INVALID
};

Dice dice_prev_stack(Dice item)
{
    switch (item)
    {
        case EMPTY:
        case WHITE_6:
        case BLACK_6:
            return INVALID;
        default:
            return item + 1;
    }
}
