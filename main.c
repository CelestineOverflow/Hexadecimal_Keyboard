//===========================================================
// Example Program for the TIVA TM4C1294XL Evaluation Board
// With this file you can print text to the console of the
// Code Composer Studio.
//==========================================================
// ! IMPORTANT !
// This program runs endless. Stop with the "Red Square Button"
// in Debug Mode (Terminate = CTRL + F2)
//==========================================================
// Include the Header File for controller tm4c1294ncpdt
#include "inc/tm4c1294ncpdt.h"
#include <stdint.h>
#include <stdio.h>
#include "lib\basics.h"
// prototypes
void setup(void);
void loop(void);
void delay(uint32_t);
char getKey();

unsigned char arr[5] = {0x07, 0x0B, 0x0D, 0x0E, 0x0F};

void main(void)
{
    setup();
    loop();
}

void setup()
{
    printf("Starting Keyboard\n");
    SYSCTL_RCGCGPIO_R |= 0x20; // clock enable
    while ((SYSCTL_RCGCGPIO_R & 0x20) == 0)
    {
    };
    GPIO_PORTM_DEN_R |= 0xFF; // enable digital I/O (BITS 0-7)
    GPIO_PORTM_DIR_R |= 0xF0; // set PORTM pins 0-3 as input and 4-7 as output
}

void loop()
{
    while (true)
    {
        printf("key being pressed => %c \n", getKey());
        delay(100000);
    }
}

char keyboard_output[16] = {'1', '2', '3', 'F', '4', '5', '6', 'E', '7', '8', '9', 'D', 'A', '0', 'B', 'C'};

char getKey()
{   
    char key = '\0';
    int keys = 0;
    int i;
    for (i = 4; i < 8; i++)
    {
        GPIO_PORTM_DATA_R |= 0xF0; // SET PORTM pins 4-7 as HIGH
        setPin(GPIO_PORTM_DATA_R, i, false);
        int j;
        for (j = 0; j < 4; j++)
        {
            if (!checkPin(j, GPIO_PORTM_DATA_R))//Active low
            {
                key = keyboard_output[j+i-4];//I hope this makes sense
                keys++;
            }
        }
        
        setPin(GPIO_PORTM_DATA_R, i, true);
    }
    if (keys == 1 || keys == 0)
    {
        return key;
    }
    else
    {   
        printf("Error: %d keys pressed\n", keys);
        return '\0';
    }
}
