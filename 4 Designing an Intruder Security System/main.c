/*
 * OccupancyDetector.c
 *
 *  Created on: February 2nd, 2023
 *      Author: Adog64
 */

#include <msp430.h>
#include "embedded_utils.h"
#include <stdbool.h>

#define ARMED 0x00
#define WARNING 0x01
#define ALERT 0x02

#define ONE_SECOND 1000000
#define ONE_AND_A_HALF_SECONDS 1500000

char state = ARMED;

int main(void)
{
    killWatchdogTimer();
    unlockGPIO();

    setPinMode(4,1, INPUT);
    setPinMode(1,0, OUTPUT);
    setPinState(1,0, 0);

    while (true)
    {
        switch (state)
        {
            case ARMED:
                togglePinState(1,0);
                __delay_cycles(ONE_AND_A_HALF_SECONDS);
                break;
            case WARNING:
                break;
        }
    }
}



