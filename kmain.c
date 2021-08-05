#include "drivers/frame_builder.h"
#include "drivers/serial_write.h"

#define POSITION 0

void kmain()
{
    char str[] = "Hello, Welcome to LemonOS...!!!";
    //determining the length of the string
    unsigned int len = sizeof(str) / sizeof(str[0]);
    
    //frame builder writing
    fb_write(POSITION, str, len);
    
    //serial writing
    serial_write(0x3F8, str, len);
}
