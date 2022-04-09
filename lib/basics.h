//Frequent used functions

#include "inc/tm4c1294ncpdt.h"
#include <stdint.h>
#include <stdio.h>

typedef enum { false, true } bool;

void delay(uint32_t ms) // create delay funtion by using assembly nop
{
    uint32_t i;
    for (i = 0; i < ms; i++)
    {
        __asm("nop");//nop is a no operation instruction
    }
}

void setPin(uint32_t portData, uint8_t pinNumber, bool value){//set pin to high or low
    if(value){
        portData |= (1 << pinNumber);
    }
    else{
        portData &= ~(1 << pinNumber);
    }
}

int checkPin(uint8_t pinNumber, unsigned char input){
    if(input & (1 << pinNumber)){
        return true;
    }
    return false;
}


void square(uint32_t GPIO, uint32_t steps){//square wave
    GPIO = 0xFF;
    delay(steps / 2);
    GPIO = 0x00;
    delay(steps / 2);
}

void enable_port(uint32_t GPIO){//enable port;
    GPIO |= 0xFF; // enable digital I/O (BITS 0-7)
}