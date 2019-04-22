/*
 *
 * Project: BLINK-ERRR (github.com/5N44P/blink-errr)
 * File:   main.c
 * Author: valerio\new (github.com/5N44P)
 *
 * Created on 24 march 2019, 21.15
 *
 * Target: ATtiny202 (0x1E 0x91 0x23)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 *
 */

#define LED_PIN_MASK (1 << 1) // define led pin as the port mask for the pin
#define BLINK_PERIOD 0x0A // defines the time between every blink

#include <avr/io.h> // register definitions
#include "settings.h" // header file for the functions of the program


int main() {
    PORTA.DIR = LED_PIN_MASK; // set the led as output
    system_init(); // initialize the system: set the clock and enable the watchdog/pit
    while(1){
      PORTA.OUTSET = LED_PIN_MASK; // turn on the LED
      PORTA.OUTCLR = LED_PIN_MASK; // turn off the LED
      sleep(); // go to sleep
      RTC.PITINTFLAGS = 0x01; // clear the interrupt flag
    }
    return (0);
}


void system_init(){
  asm("CLI"); // disable all interrupts to allow configuration
  set_clock_1k(); // set the clock to the 32k ULP oscillator with the defined prescaler
  //watchdog_enable(); // LEGACY for reference, to be removed. Enable the watchdog
  pit_enable(); // enable the periodic interrupt (RTC peripheral)
  asm("SEI"); // enable global interrupts
}

void set_clock_1k(){
  CCP = 0xD8;   // sign CCP for modifying clock selection register
  CLKCTRL.MCLKCTRLA = 0x01; // set the main clock to OSCULP32K
  CCP = 0xD8; // sign CCP for modifying clock prescaler register
  CLKCTRL.MCLKCTRLB = (0x04<<1) | 1; // set prescaler to :32 -> cpu running at 1kHz
}

// LEGACY for reference, to be removed.
/* void watchdog_enable(){
     CCP = 0xD8; // sign change
     WDT.CTRLA = BLINK_PERIOD; // watchdog 4 seconds
} */

void pit_enable(){
     RTC.CLKSEL = 0x01; //select the 32k oscillator prescaled to 1kHz
     RTC.PITCTRLA  = (BLINK_PERIOD << 3); // Set the interrupt frequency to BLINK_PERIOD
     RTC.PITINTCTRL = (0x01); // enable the PIT interrupt
     RTC.PITCTRLA |= (0x01); // enable the PIT
     asm("SEI"); // enable global interrupts
}

void sleep(){
    SLPCTRL.CTRLA = (0x02 << 1) | 0x01; // set the sleep to power down, enable the sleep
    asm("SLEEP"); // pass the SLEEP instruction to the CPU
}
