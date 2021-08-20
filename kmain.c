#include "drivers/io.h"
#include "drivers/frame_builder.h"
#include "drivers/serial_write.h"
#include "drivers/gdt.h"

#include "drivers/interrupts/interrupts.c"

#define POSITION 0

void init(){
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
    char str2[] = "Hello Sadisha Nimsara";
    serial_write(0x3F8, str2, 21);
}
