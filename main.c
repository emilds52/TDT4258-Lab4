#include <xc.h>
#include <stdio.h>
// #include "usart.h"

// 256*100/1024
#define DACREF_VALUE 25

void AC_init(){
    // Set pin PD2 (port D, pin 2) as an input
    PORTD.DIRCLR = PIN2_bm;
    // Disable digital input buffer and pull-up resistor for pin PD2
    PORTD.PIN2CTRL = PORT_ISC_INPUT_DISABLE_gc;
    // Remaining initialization steps...
    AC0.MUXCTRL = AC_MUXPOS_AINP0_gc |
                  AC_MUXNEG_DACREF_gc;
    AC0.CTRLA = AC_POWER_PROFILE2_gc |
                AC_ENABLE_bm;
    AC0.DACREF = DACREF_VALUE;
    AC0.CTRLB = AC_WINSEL_DISABLED_gc;
}

void VREF_init(void) {
    VREF.ACREF = VREF_REFSEL_1V024_gc;
}

void LED_init() {
    PORTA.DIRSET = PIN2_bm;
}
void set_LED_on(){
    // LED is active low. Set pin LOW to turn LED on
    PORTA.OUTCLR = PIN2_bm;
}
void set_LED_off(){
    // LED is active low. Set pin HIGH to turn LED off
    PORTA.OUTSET = PIN2_bm;
}


void main(void) {
    AC_init();
    VREF_init();
    LED_init();
    //USART3_Init();
    //char message[100];
    //sprintf(message, "MUXCTRL: 0x%02x\n", AC0.MUXCTRL);
    //USART3_SendString(message);
    //sprintf(message, "CTRLA: 0x%02x\n", AC0.CTRLA);
    //USART3_SendString(message);
    //sprintf(message, "DACREF: 0x%02x\n", AC0.DACREF);
    //USART3_SendString(message);
    while(1){
        if (AC0.STATUS & AC_CMPSTATE_bm){
            set_LED_off();
            //sprintf(message, "0x%02x\n", AC0.STATUS);
            //USART3_SendString(message);
        } else {
            set_LED_on();
        }
    }
    return;
}
