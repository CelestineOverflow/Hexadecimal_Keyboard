// Celestine Machuca

#include "lib\basics.h"
#include "inc/tm4c1294ncpdt.h"
#include <stdint.h>
// prototypes
void squareWave(uint32_t steps, volatile uint32_t *latReg);
void setup(void);
void loop(void);
char getKey(void);

void main(void)
{
    setup();
    loop();
}

void setup()
{   
    printf("Starting Keyboard\n");
    startClock(0x210); // enable clock to ports e to k
    // 0x7FFF for using all ports
    // port K OUTPUT
    // direction
    GPIO_PORTK_DIR_R |= 0xFF;
    // data enable
    GPIO_PORTK_DEN_R |= 0xFF;
    // port E INPUT
    // direction
    GPIO_PORTE_AHB_DIR_R |= 0x00;
    // data enable
    GPIO_PORTE_AHB_DEN_R |= 0xFF;
    printf("Setup Finish\n");
}

void loop()
{
    while (1)
    {
        printf("key pressed ====> %c\n", getKey());
        delay(100);
    }
}

char keyboard_output[4][4] = {{'1', '2', '3', 'F'}, {'4', '5', '6', 'E'}, {'7', '8', '9', 'D'}, {'A', '0', 'B', 'C'}};

char getKey()
{
    char key = '\0';
    int keys = 0;
    for (int i = 0; i < 4; i++)
    {
        setPin(&GPIO_PORTK_DATA_R, i, false);
        delay(1000);
        for (int j = 0; j < 4; j++)
        {
            if (!checkPin(j, GPIO_PORTE_AHB_DATA_R))
            {
                keys++;
                key = keyboard_output[i][j];
            }
        }
        setPin(&GPIO_PORTK_DATA_R, i, true);
    }
    if (keys == 1)
    {
        return key;
    }
    if (keys == 0)
    {
        return 'x';
    }
    else
    {
        printf("Error: %d keys pressed\n", keys);
        return '\0';
    }
}
