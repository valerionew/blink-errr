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


int main(int argc, char** argv) {
    PORTA.DIR = LED_PIN; // set the led as output

    my_system_init(); // initialize the system: set the clock and enable the watchdog
    while(1){
      PORTA.OUTSET = LED_PIN; // light the LED
      PORTA.OUTCLR = LED_PIN; // turn off the LED
      sleep(); // go to sleep
      //RTC.PITINTFLAGS = 0x01; // clear the interrupt flag
    }
    return (0);
}


void my_system_init(){
  asm("CLI"); // disable all interrupts
  set_clock_32k(); // set the clock to the 32k ULP oscillator with the defined prescaler
  //watchdog_enable(); // enable the watchdog
  pit_enable();
}

void set_clock_32k(){
  CCP = 0xD8;   // sign CCP for modifying clock selection register
  CLKCTRL.MCLKCTRLA = 0x01; // set the main clock to OSCULP32K
  CCP = 0xD8; // sign CCP for modifying clock prescaler register
  CLKCTRL.MCLKCTRLB = (0x04<<1) | 1; // set prescaler to
}

void watchdog_enable(){
     CCP = 0xD8; // sign change
     WDT.CTRLA = 0x0B; // watchdog 4 seconds
}

void pit_enable(){
     RTC.CLKSEL = 0x01; //select the 32k oscillator prescaled to 1kHz
     RTC.PITCTRLA  = (0x0C << 3); // Set the interrupt frequency to CYC8192
     RTC.PITINTCTRL = (0x01); // enable the PIT interrupt
     RTC.PITCTRLA |= (0x01); // enable the PIT
     asm("SEI");
}

void sleep(){
    SLPCTRL.CTRLA = 0x03; // set the sleep to power down, enable the sleep
    asm("SLEEP"); // pass the SLEEP instruction to the CPU
}
