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
        delay(1610000);
    }
}

char keyboard_output[4][4] = {{'1', '4', '7', 'a'},
                              {'2', '5', '8', '0'},
                              {'3', '6', '9', 'b'},
                              {'f', 'e', 'd', 'c'}};

char getKey()
{
    char key = '\0';
    int keys = 0;
    for (int x = 0; x < 4; x++)
    {
        setPin(&GPIO_PORTK_DATA_R, x, false);
        delay(10);
        for (int y = 0; y < 4; y++)
        {
            if (!checkPin(y, GPIO_PORTE_AHB_DATA_R))
            {
                keys++;
                key = keyboard_output[x][y];
            }
        }
        setPin(&GPIO_PORTK_DATA_R, x, true);
    }
    if (keys == 1 || keys == 0)
    {
        return key;
    }
    printf("Error: %d keys pressed\n", keys);
    return '\0';
}
