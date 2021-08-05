#include "drivers/frame_builder.h"

#define POSITION 0

void kmain()
{
    char str[] = "Hello, Welcome to LemonOS...!!!";
    //determining the length of the string
    unsigned int len = sizeof(str) / sizeof(str[0]);
    
    fb_write(POSITION, str, len);
}
