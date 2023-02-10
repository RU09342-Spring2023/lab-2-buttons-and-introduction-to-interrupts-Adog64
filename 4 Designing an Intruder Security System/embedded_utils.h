#pragma once

#include <msp430.h>
#include <stdbool.h>

#define OUTPUT 0x01
#define INPUT 0x00

/// @brief kill the watchdog timer
void killWatchdogTimer();


/// @brief disable low power lock on GPIO
void unlockGPIO();

/// @brief Set a pin as output P[port].[pin]
/// @param port port containing pin
/// @param pin bit index within register
void setOutputPin(char port, char pin);

/// @brief Set a pin as input P[port].[pin]
/// @param port port containing pin
/// @param pin bit index within register
void setInput(char port, char pin);

/// @brief Set the value of pin P[port].[pin] to logic 1
/// @param port port containing pin
/// @param pin @bit index within register
void setPin(char port, char pin);

/// @brief Set the value of pin P[port].[pin] to logic 0
/// @param port port containing pin
/// @param pin @bit index within register
void clearPin(char port, char pin);

/// @brief Toggle the value of pin P[port].[pin]
/// @param port port containing pin
/// @param pin bit index within register
void togglePin(char port, char pin);

/// @brief Enable interrupts locally on pin P[port].[pin]
/// @param port port containing pin
/// @param pin bit index within register
void enablePinInterrupt(char port, char pin);

//================= DEFINITIONS ==================

void setOutput(char port, char pin)
{
    char bit = BIT0 << pin;
    port -= 1;
    char* dir = 0x0204 + ((port >> 1) << 5) + (port & 1);
    *dir |= bit;
}

void setInput(char port, char pin)
{
    char bit = BIT0 << pin;
    port -= 1;
    char* dir = 0x0204 + ((port >> 1) << 5) + (port & 1);
    *dir &= ~bit;
}


void setPin(char port , char pin)
{
    char bit = BIT0 << pin;
    port -= 1;
    char* out = 0x0202 + ((port >> 1) << 5) + (port & 1);
    *out |= bit;
}

void clearPin(char port , char pin)
{
    char bit = BIT0 << pin;
    port -= 1;
    char* out = 0x0202 + ((port >> 1) << 5) + (port & 1);
    *out &= ~bit;
}

void togglePin(char port, char pin)
{
    char bit = BIT0 << pin;
    port -= 1;
    char* out = 0x0202 + ((port >> 1) << 5) + (port & 1);
    *out ^= bit;
}

void enablePinInterrupt(char port, char pin)
{
    char bit = BIT0 << pin;
    port -= 1;
    char* ie = 0x021A + ((port >> 1) << 5) + (port & 1);
    *ie |= bit;
}


void killWatchdogTimer()
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
}

void unlockGPIO()
{
    PM5CTL0 &= ~LOCKLPM5;
}