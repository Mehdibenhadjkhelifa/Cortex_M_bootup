extern void* END_STACK;
void isr_reset(void){

}
void isr_fault(void){
    while(1);
}
void isr_empty(void){
}
/* This is the interrupt vector.
 * 
 * It sits at the beginning of the flash image,
 * and contains the initial stack pointer, and 
 * the service routines associated to exceptions 
 * and interrupt requests.
 *
 * Replace the default empty service routine with
 * the corresponding handler.
 */
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

