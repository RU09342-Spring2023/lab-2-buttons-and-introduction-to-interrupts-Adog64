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

/// @brief Enable interrupts locally on pin P[port].[pin]
/// @param port port containing pin
/// @param pin bit index within register
void enablePinInterrupt(char port, char pin);

//================= DEFINITIONS ==================

void setPinMode(char port, char pin, bool mode)
{
    char bit = BIT0 << pin;
    port -= 1;
    char* dir = 0x0204 + ((port >> 1) << 5) + (port & 1);
    *dir = (mode) ? *dir | bit : *dir & ~bit; 
}

void setPinState(char port , char pin, bool value)
{
    char bit = BIT0 << pin;
    port -= 1;
    int* out = 0x0202 + ((port >> 1) << 5) + (port & 1);
    *out = (value) ? *out | bit : *out & ~bit;
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

void enablePinInterrupt(char port, char pin)
{
    char bit = BIT0 << pin;
    switch (port)
    {
    case 1:
        P1IE |= bit;
        break;
    case 2:
        P2IE |= bit;
        break;
    case 3:
        P3IE |= bit;
        break;
    case 4:
        P4IE |= bit;
        break;
    case 5:
        P5IE |= bit;
        break;
    case 6:
        P6IE |= bit;
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