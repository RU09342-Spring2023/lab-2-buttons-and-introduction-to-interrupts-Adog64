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

#define HALF_SECOND 500000
#define ONE_SECOND 1000000
#define ONE_AND_A_HALF_SECONDS HALF_SECOND + ONE_SECOND
#define TEN_SECONDS 10*ONE_SECOND

char state = ARMED;
long int warningTime;

int main(void)
{
    killWatchdogTimer();
    unlockGPIO();

    setPinMode(4,1, INPUT);
    setPinMode(6,6, OUTPUT);
    setPinMode(1,0, OUTPUT);
    setPinState(6,6, 0);
    setPinState(1,0, 1);

    P4IFG &= ~BIT1;                         // Clear P4.1 IFG


    while (true)
    {
        __bis_SR_register(GIE);
        switch (state)
        {
            case ARMED:
                setPinState(1,0, 0);
                togglePinState(6,6);
                __delay_cycles(ONE_AND_A_HALF_SECONDS);
                break;
            case WARNING:
                if (warningTime <= 0)
                    state = ALERT; 
                setPinState(6,6, 0);
                togglePinState(1,0);
                __delay_cycles(HALF_SECOND);
                warningTime -= HALF_SECOND;
                break;
            case ALERT:
                setPinState(1,0, 1);
                setPinState(6,6, 0);
        }
    }
}

void __attribute__ ((interrupt(PORT4_VECTOR))) Port_4 (void)
{
    P4IFG &= ~BIT1;                         // Clear P4.1 IFG
    P4IES ^= BIT1;                          // Transition the Edge Type (Low --> High, or High --> Low)

    if (state == ARMED)
    {
        state = WARNING;
        warningTime = TEN_SECONDS;
    }
}