#include "drivers/io.h"
#include "drivers/frame_builder.h"
#include "drivers/serial_write.h"
#include "drivers/gdt.h"

#include "drivers/interrupts/interrupts.c"

#define POSITION 0
#define PORT 0x3F8
#define BAUD_RATE 4

void init(){
    //configure serial port
    serial_configure(PORT, BAUD_RATE);
    
    init_gdt();
    
    interrupts_install_idt();
}

void kmain()
{
    init();

    char str[] = "Hello, Welcome to LemonOS...!!!";
    //determining the length of the string
    unsigned int len = sizeof(str) / sizeof(str[0]);
    
    //frame builder writing
    fb_write(POSITION, str, len);
    
    //serial writing
    char str2[] = "Hello Sadisha Nimsara\n";
    unsigned int s_len = sizeof(str2) / sizeof(str2[0]);
    serial_write(PORT, str2, s_len);
}
