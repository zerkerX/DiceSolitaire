/*
This file is part of DiceSolitaire.

DiceSolitaire is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

DiceSolitaire is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with DiceSolitaire.  If not, see <https://www.gnu.org/licenses/>.
*/
#include "Hand.hpp"
#include "Board.hpp"

#include <Arduboy2.h>
#include <Sprites.h>
#include <string.h>
#include "title.h"

Arduboy2 arduboy;
Hand hand;
Board board;

/* Primary TODO list:
 * - A main menu
 * - In-game options to quit, restart or new puzzle
 * - Recognize when puzzle is complete.
 * >> Minimum viable game!
 * - Fixed set of puzzles? Or maybe just choose number of dice sets?
 * - There will be a bug if two collapsed sets end up in the same column
 *   (and aren't the same color themselves). Try to reproduce, then consider
 *   if it's worth fixing. Can probably simplify to only check for two; a third
 *   is VERY unlikely.
 *
 * Maybe list?
 * - Consider allowing placement on top of collapsed sets. It seems a
 *   good challenge without this, though.
 */

bool menu = true;

void setup() {
  arduboy.begin();

  //~ arduboy.setFrameRate(15);
}

void do_menu()
{
    Sprites::drawOverwrite(0, 0, title, 0);
    arduboy.pollButtons();

    if (arduboy.justPressed(A_BUTTON) || arduboy.justPressed(B_BUTTON))
    {
        menu = false;
        board.shuffle(arduboy.generateRandomSeed());
    }
}

void user_action()
{
    arduboy.pollButtons();
    
    if (arduboy.justPressed(UP_BUTTON)) hand.up();
    if (arduboy.justPressed(DOWN_BUTTON)) hand.down();
    if (arduboy.justPressed(LEFT_BUTTON)) hand.left();
    if (arduboy.justPressed(RIGHT_BUTTON)) hand.right();

    if (arduboy.justPressed(A_BUTTON)) hand.grab(board);
    if (arduboy.justPressed(B_BUTTON)) hand.put_back(board);
}


void draw_display()
{
    arduboy.clear();
    board.draw();
    hand.draw();
}

/* Also reminder: F() macro is to convert string constant from flash */
void loop() {
    if (!(arduboy.nextFrame()))
        return;

    if (menu)
    {
        do_menu();
    }
    else
    {
        user_action();
        hand.gravity(board);
        board.check_matches();
        draw_display();
    }
    arduboy.display();
}
