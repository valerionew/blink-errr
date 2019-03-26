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
#include <stdio.h>
#include <stdlib.h>
#include <avr/cpufunc.h> // _NOP()
#include <avr/io.h>


int main(int argc, char** argv) {

    my_system_init();

    while(1){



    }
    return (0);
}


void my_system_init(){
  FUSE.BODCFG = 0; // disable brownout detection (system will go below 1.8v)
  // OCSCFG should be set? uC should run on the 32kHz oscillator
  set_clock_32k();

    }

void set_clock_32k(){
  uint8_t savedsreg = SREG; // save the status register with the interrupt enable flags
  cli(); // disable all interrupts
  CCP = 0xD8;   // set CCP for modifying clock selection register
  CLKCTRL.MCLKCTRLA = 0x1; // set the main clock to OSCULP32K
  CLKCTRL.MCLKCTRLB = 0; // disable prescaler
  SREG = savedsreg; // restore the SREG (re-enable the interrupts)
}
