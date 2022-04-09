//===========================================================
// Example Program for the TIVA TM4C1294XL Evaluation Board
// With this file the LEDs D0 to D3 on the eval board will
// blink each one after another. To control the LEDs the
// Ports N and F with Pins PN0, PN1, PF0 and PF4 have to be
// enabled and set as digital output.
//===========================================================
// Include the Header File for controller tm4c1294ncpdt
// Vorname, Nachname => Celestine S. Machuca
#include "inc/tm4c1294ncpdt.h"
#include <stdint.h>
void main(void)
{
    int i = 0;                      // => 
    SYSCTL_RCGCGPIO_R = 0x00001020; // => Enable clock 
    i++;                            // =>   i = 1
    GPIO_PORTC_DEN_R = 0x03;        // => Enable digital function on Port N
    GPIO_PORTN_DIR_R = 0x03;        // => Set Port N as output
    GPIO_PORTF_AHB_DEN_R = 0x11;    // => Enable digital function on Port F
    GPIO_PORTF_AHB_DIR_R = 0x11;    // => Set Port F as output
    // => i = 1
    while (1)
    {
        GPIO_PORTP_DATA_R = 0x02; // => Turn on LED D0
        for (i = 0; i < 500000; i++)
            ;                     // => wait loop
        GPIO_PORTN_DATA_R = 0x01; // => Turn on LED D1
        for (i = 0; i < 500000; i++)
            ;                         // => wait loop
        GPIO_PORTN_DATA_R = 0x00;     // => Turn on LED D2
        GPIO_PORTF_AHB_DATA_R = 0x10; // => Turn on LED D3
        for (i = 0; i < 500000; i++)
            ;                         // => wait loop
        GPIO_PORTF_AHB_DATA_R = 0x01; // => Turn on LED D3
        for (i = 0; i < 500000; i++)
            ;                         // => wait loop
        GPIO_PORTF_AHB_DATA_R = 0x00; // => Turn on LED D3
    }
}
