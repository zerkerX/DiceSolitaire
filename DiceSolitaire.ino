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
#include <Arduboy2.h>
#include <Sprites.h>
#include <string.h>

#include "blackdice.h"
#include "whitedice.h"
#include "cursor.h"

Arduboy2 arduboy;

void setup() {
  arduboy.begin();

  //~ arduboy.setFrameRate(15);
}

int cursx = 0;
int cursy = 0;

const int minx = 0;
const int maxx = 9;
const int miny = 0;
const int maxy = 4;

void move_cursor()
{
    arduboy.pollButtons();
    
    if (arduboy.justPressed(UP_BUTTON)) cursy--;
    if (arduboy.justPressed(DOWN_BUTTON)) cursy++;
    if (arduboy.justPressed(LEFT_BUTTON)) cursx--;
    if (arduboy.justPressed(RIGHT_BUTTON)) cursx++;
    
    if (cursy < miny) cursy = miny;
    if (cursy > maxy) cursy = maxy;
    if (cursx < minx) cursx = minx;
    if (cursx > maxx) cursx = maxx;
}

/* Full display resolution is 128 x 64
 * Font size (if I use it) is 6 x 8 pixels */
void draw_display()
{
    arduboy.clear();
    
    for (int i = 0; i < 6; i++)
    {
        Sprites::drawOverwrite(i * 12, 12, blackdice, i);
        Sprites::drawOverwrite(i * 12, 24, whitedice, i);
    }

    Sprites::drawPlusMask(cursx * 12, cursy * 12, cursor, 0);
}

/* Also reminder: F() macro is to convert string constant from flash */

void loop() {
    if (!(arduboy.nextFrame()))
        return;

    move_cursor();
    draw_display();
    arduboy.display();
}
