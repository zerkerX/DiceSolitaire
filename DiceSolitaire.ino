/*
This file is part of MPDControl.

MPDControl is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Foobar is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Foobar.  If not, see <https://www.gnu.org/licenses/>.
*/
#include "Hand.hpp"
#include "Board.hpp"

#include <Arduboy2.h>
#include <string.h>

Arduboy2 arduboy;
Hand hand;
Board board;

void setup() {
  arduboy.begin();

  //~ arduboy.setFrameRate(15);
}

void user_action()
{
    arduboy.pollButtons();
    
    if (arduboy.justPressed(UP_BUTTON)) hand.up();
    if (arduboy.justPressed(DOWN_BUTTON)) hand.down();
    if (arduboy.justPressed(LEFT_BUTTON)) hand.left();
    if (arduboy.justPressed(RIGHT_BUTTON)) hand.right();

    if (arduboy.justPressed(A_BUTTON)) hand.grab(board);
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

    user_action();
    draw_display();
    arduboy.display();
}
