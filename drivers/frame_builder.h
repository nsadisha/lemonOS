#ifndef INCLUDE_FRAME_BUFFER_H
#define INCLUDE_FRAME_BUFFER_H

#include "io.h"

/**Colors**/
#define FB_GREEN 2
#define FB_DARK_GREY 8

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

//writing a charactor
void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg)
{
    fb[i] = c;
    fb[i + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
}


//moving the cursor
/* The I/O ports */
#define FB_COMMAND_PORT         0x3D4
#define FB_DATA_PORT            0x3D5

/* The I/O port commands */
#define FB_HIGH_BYTE_COMMAND    14
#define FB_LOW_BYTE_COMMAND     15

/** fb_move_cursor:
*  Moves the cursor of the framebuffer to the given position
*
*  @param pos The new position of the cursor
*/
void fb_move_cursor(unsigned short pos)
{
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT,    ((pos >> 8) & 0x00FF));
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT,    pos & 0x00FF);
}


//Writing a buffer
void fb_write(unsigned int pos, char *buff, unsigned int len)
{
    unsigned int currentPos;
    for(unsigned int i=0; i<(len-1); i++){
        //setting current position
    	currentPos = (pos+i)*2;
    	    	   
        //writing charactors
    	fb_write_cell(currentPos, *(buff+i), FB_GREEN, FB_DARK_GREY);
    }
    //setting the cursor
    fb_move_cursor(pos+len-1);
}

#endif
