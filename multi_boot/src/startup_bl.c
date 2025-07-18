#include "utils.h"
typedef unsigned int uint32_t;
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
    asm volatile("cpsid i");
    uint32_t app_end_stack = (*((uint32_t*)(APP_OFFSET)));
    void(* app_entry)(void);
    app_entry = (void *)(*((uint32_t *)(APP_OFFSET + 4)));
    asm volatile("msr msp, %0" :: "r"(app_end_stack));
    uint32_t *VTOR = (uint32_t *)0xE000ED08;
    *VTOR = (uint32_t)APP_OFFSET;
    asm volatile("mov pc, %0" ::"r"(app_entry));
}
__attribute__ ((section(".isr_vector")))
void (* const IV[])(void) =
{
	(void (*)(void))(&END_STACK),
	isr_reset,                   // Reset
	isr_fault,                   // NMI
	isr_fault,                   // HardFault
	isr_fault,                   // MemFault
	isr_fault,                   // BusFault
	isr_fault,                   // UsageFault
	0, 0, 0, 0,                  // 4x reserved
	isr_empty,                   // SVC
	isr_empty,                   // DebugMonitor
	0,                           // reserved
	isr_empty,                   // PendSV
	isr_empty,                   // SysTick

    isr_empty,                     // GPIO Port A
    isr_empty,                     // GPIO Port B
    isr_empty,                     // GPIO Port C
    isr_empty,                     // GPIO Port D
    isr_empty,                     // GPIO Port E
    isr_empty,                     // UART0 Rx and Tx
    isr_empty,                     // UART1 Rx and Tx
    isr_empty,                     // SSI0 Rx and Tx
    isr_empty,                     // I2C0 Master and Slave
    isr_empty,                     // PWM Fault
    isr_empty,                     // PWM Generator 0
    isr_empty,                     // PWM Generator 1
    isr_empty,                     // PWM Generator 2
    isr_empty,                     // Quadrature Encoder 0
    isr_empty,                     // ADC Sequence 0
    isr_empty,                     // ADC Sequence 1
    isr_empty,                     // ADC Sequence 2
    isr_empty,                     // ADC Sequence 3
    isr_empty,                     // Watchdog timer
    isr_empty,                     // Timer 0 subtimer A
    isr_empty,                     // Timer 0 subtimer B
    isr_empty,                     // Timer 1 subtimer A
    isr_empty,                     // Timer 1 subtimer B
    isr_empty,                     // Timer 2 subtimer A
    isr_empty,                     // Timer 3 subtimer B
    isr_empty,                     // Analog Comparator 0
    isr_empty,                     // Analog Comparator 1
    isr_empty,                     // Analog Comparator 2
    isr_empty,                     // System Control (PLL, OSC, BO)
    isr_empty,                     // FLASH Control
    isr_empty,                     // GPIO Port F
    isr_empty,                     // GPIO Port G
    isr_empty,                     // GPIO Port H
    isr_empty,                     // UART2 Rx and Tx
    isr_empty,                     // SSI1 Rx and Tx
    isr_empty,                     // Timer 3 subtimer A
    isr_empty,                     // Timer 3 subtimer B
    isr_empty,                     // I2C1 Master and Slave
    isr_empty,                     // Quadrature Encoder 1
    isr_empty,                     // CAN0
    isr_empty,                     // CAN1
    isr_empty,                     // CAN2
    isr_empty,                     // Ethernet
    isr_empty,                     // Hibernate
};
