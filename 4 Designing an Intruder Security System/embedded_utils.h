#pragma once

#include <msp430.h>
#include <stdbool.h>

#define OUTPUT 0x01
#define INPUT 0x00

/// @brief kill the watchdog timer
void killWatchdogTimer();


/// @brief disable low power lock on GPIO
void unlockGPIO();

/// @brief Set a pin as input or output P[port].[pin]
/// @param port port containing pin
/// @param pin bit index within register
/// @param mode set as input or output
void setPinMode(char port, char pin, bool mode);

/// @brief Set the value of pin P[port].[pin]
/// @param port port containing pin
/// @param pin @bit index within register
/// @param value value to set the pin
void setPinState(char port, char pin, bool value);


/// @brief Toggle the value of pin P[port].[pin]
/// @param port port containing pin
/// @param pin bit index within register
void togglePinState(char port, char pin);

//================= DEFINITIONS ==================

void setPinMode(char port, char pin, bool mode)
{
    char bit = BIT0 << pin;
    switch (port)
    {
        case 1:
            P1DIR = (mode) ? P1DIR | bit : P1DIR & ~bit;
            break;
        case 2:
            P2DIR = (mode) ? P2DIR | bit : P2DIR & ~bit;
            break;
        case 3:
            P3DIR = (mode) ? P3DIR | bit : P3DIR & ~bit;
            break;
        case 4:
            P4DIR = (mode) ? P4DIR | bit : P4DIR & ~bit;
            break;
        case 5:
            P5DIR = (mode) ? P5DIR | bit : P5DIR & ~bit;
            break;
        case 6:
            P6DIR = (mode) ? P6DIR | bit : P6DIR & ~bit;
            break;
    }
}

void setPinState(char port , char pin, bool value)
{
    char bit = BIT0 << pin;
    switch (port)
    {
        case 1:
            P1OUT = (value) ? P1OUT | bit : P1OUT & ~bit;
            break;
        case 2:
            P2OUT = (value) ? P2OUT | bit : P2OUT & ~bit;
            break;
        case 3:
            P3OUT = (value) ? P3OUT | bit : P3OUT & ~bit;
            break;
        case 4:
            P4OUT = (value) ? P4OUT | bit : P4OUT & ~bit;
            break;
        case 5:
            P5OUT = (value) ? P5OUT | bit : P5OUT & ~bit;
            break;
        case 6:
            P6OUT = (value) ? P6OUT | bit : P6OUT & ~bit;
            break;
    }
}

void togglePinState(char port, char pin)
{
    unsigned int bit = BIT0 << pin;
    switch (port)
    {
        case 1:
            P1OUT ^= bit;
            break;
        case 2:
            P2OUT ^= bit;
            break;
        case 3:
            P3OUT ^= bit;
            break;
        case 4:
            P4OUT ^= bit;
            break;
        case 5:
            P5OUT ^= bit;
            break;
        case 6:
            P6OUT ^= bit;
            break;
    }
}

void killWatchdogTimer()
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
}

void unlockGPIO()
{
    PM5CTL0 &= ~LOCKLPM5;
}