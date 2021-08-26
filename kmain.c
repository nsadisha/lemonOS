#include "drivers/io.h"
#include "drivers/frame_builder.h"
#include "drivers/serial_write.h"
#include "drivers/gdt.h"
#include "drivers/interrupts/interrupts.c"
#include "multiboot.h"

#define POSITION 0
#define PORT 0x3F8
#define BAUD_RATE 4

void init(){
    //configure serial port
    serial_configure(PORT, BAUD_RATE);
    
    //initialize segment descriptor tables
    init_gdt();
    
    //initialize interrupt descriptor table
    interrupts_install_idt();
}

void kmain(unsigned int ebx){
    init();
    
    multiboot_info_t *mbinfo = (multiboot_info_t *) ebx;
    multiboot_module_t* modules = (multiboot_module_t*) mbinfo->mods_addr; 
    unsigned int address_of_module = modules->mod_start;

    if(mbinfo->mods_count == 1){
        char str[] = "Hello, Welcome to LemonOS...!!!";
        //determining the length of the string
        unsigned int len = sizeof(str) / sizeof(str[0]);
    
        //frame builder writing
        fb_write(POSITION, str, len);
    
        //serial writing
        char str2[] = "Module is loaded correctly.\n";
        unsigned int s_len = sizeof(str2) / sizeof(str2[0]);
        serial_write(PORT, str2, s_len);
        
        typedef void (*call_module_t)(void);
        /* ... */
        call_module_t start_program = (call_module_t) address_of_module;
        start_program();
        /* we'll never get here, unless the module code returns */
    }else{
        char errorMsg[] = "Error: Number of modules loaded is not equal to 1.\n";
        unsigned int err_len = sizeof(errorMsg) / sizeof(errorMsg[0]);
        fb_write(POSITION, errorMsg, err_len);
        serial_write(PORT, errorMsg, err_len);
    }
}
