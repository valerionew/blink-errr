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

#define LED_PIN (1 << 1) // define led pin as the port mask for the pin

#ifndef F_CPU
#  define F_CPU   1000UL  // for delay function
#endif

#include <avr/io.h> // register definitions
#include "settings.h" // header file for the functions of the program


int main() {
    PORTA.DIR = LED_PIN; // set the led as output

    my_system_init(); // initialize the system: set the clock and enable the watchdog
    PORTA.OUTSET = LED_PIN; // light the LED
    PORTA.OUTCLR = LED_PIN; // turn off the LED
    sleep(); // go to sleep

    return (0);
}


void my_system_init(){
  set_clock_32k(); // set the clock to the 32k ULP oscillator with the defined prescaler
  watchdog_enable(); // enable the watchdog
}

void set_clock_32k(){
  uint8_t savedsreg = SREG; // save the status register with the interrupt enable flags
  asm("CLI"); // disable all interrupts
  CCP = 0xD8;   // sign CCP for modifying clock selection register
  CLKCTRL.MCLKCTRLA = 0x01; // set the main clock to OSCULP32K
  CCP = 0xD8; // sign CCP for modifying clock prescaler register
  CLKCTRL.MCLKCTRLB = (0x04<<1) | 1; // set prescaler to
  SREG = savedsreg; // restore the SREG (re-enable the interrupts)

}

void watchdog_enable(){
     CCP = 0xD8; // sign change
     WDT.CTRLA = 0x0B; // watchdog 4 seconds
}

void sleep(){
    SLPCTRL.CTRLA = 0x03; // set the sleep to power down, enable the sleep
    asm("SLEEP"); // pass the SLEEP instruction to the CPU
}
