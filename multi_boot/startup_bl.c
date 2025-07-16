#include <stdint.h>
extern unsigned int _stored_data;
extern unsigned int _start_data;
extern unsigned int _start_bss;
extern unsigned int _end_data;
extern unsigned int _end_bss;
extern unsigned int _end;
extern uint32_t *END_STACK;
#define APP_OFFSET (0x00001000)
#define BOOTLOADER
void main(void);
void isr_reset(void){
    unsigned int *src,*dst;
    src = (unsigned int*) &_stored_data;
    dst = (unsigned int*) &_start_data;
    while (dst < (unsigned int*)&_end_data){
        *dst = *src;
        dst++;
        src++;
    }
    dst = &_start_bss;
    while(dst < (unsigned int*)&_end_bss){
        *dst = 0U;
        dst++;
    }
    main();
}
void isr_fault(void){
    while(1);;
}

void isr_empty(void){
}
void main(void){
    uint32_t app_end_stack = (*((uint32_t*)(APP_OFFSET)));
    void(* app_entry)(void);
    app_entry = (void *)(*((uint32_t *)(APP_OFFSET + 4)));
    asm volatile("msr msp, %0" :: "r"(app_end_stack));
}

