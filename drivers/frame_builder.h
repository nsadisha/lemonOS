#include "../io/io.h"

/** fb_write_cell:
*  Writes a character with the given foreground and background to position i
*  in the framebuffer.
*
*  @param i  The location in the framebuffer
*  @param c  The character
*  @param fg The foreground color
*  @param bg The background color
*/

char *fb = (char *) 0x000B8000;

void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg)
{
    fb[i] = c;
    fb[i + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
}
