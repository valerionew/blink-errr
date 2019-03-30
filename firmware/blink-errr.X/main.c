/*
 * File:   main.c
 * Author: valerio\new (github.com/5N44P)
 *
 * Created on 24 march 2019, 21.15
 *
 * Target: ATtiny202 (0x1E 0x91 0x23)
 *
 *
 *
 */

#define LED_PIN (1 << 1)

#ifndef F_CPU
#  define F_CPU   1000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include "settings.h"


int main(int argc, char** argv) {
    PORTA.DIR = LED_PIN; 

    my_system_init();
    PORTA.OUTSET = LED_PIN;
    PORTA.OUTCLR = LED_PIN;
    sleep();
    
   
    
    return (0);
}


void my_system_init(){
  set_clock_32k();
  watchdog_enable();
    }

void set_clock_32k(){
  uint8_t savedsreg = SREG; // save the status register with the interrupt enable flags
  asm("CLI"); // disable all interrupts
  CCP = 0xD8;   // set CCP for modifying clock selection register
  CLKCTRL.MCLKCTRLA = 0x01; // set the main clock to OSCULP32K        
  CCP = 0xD8;
  CLKCTRL.MCLKCTRLB = (0x04<<1) | 1; // set prescaler to 
  SREG = savedsreg; // restore the SREG (re-enable the interrupts)
    
}

void watchdog_enable(){
     CCP = 0xD8; // sign change
     WDT.CTRLA = 0x0B; // watchdog 4 seconds
}

void sleep(){
    SLPCTRL.CTRLA = 0x03;
    asm("SLEEP");
}