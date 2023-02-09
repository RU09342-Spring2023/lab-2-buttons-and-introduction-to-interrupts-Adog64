# Part 4: Occupancy Detection and Alert System
You are being asked to design a rudimentary occupancy alert system with the following behavior:
- The system when turned on needs to blink the Green LED once every 3 seconds to show it is armed.
- When the occupancy sensor detects someone, it will output a Logic 1, and your system needs to move into a "Warning" state, where the Green LED stops blinking, and the Red LED Blinks once per second (500ms on, 500ms off).
- If the occupancy detector still shows someone there after 10 seconds, your system should indicate this with the RED Led constantly staying on, and move into the ALERT state.
- If the occupancy detector **before** the 15 seconds goes back to a 0, indicating the room is now empty, then the system should go back to the armed state.
- When in the ALERT State, the only way for the system to go back to the Armed state is to press the P4.1 Button.

## Occupancy Sensor
You will be **first** *emulating* the Occupancy Sensor with the P4.1 button. This can be used for pretty much all of your testing and design.

When you have a design that is working, you can then test your code with a [Passive Infrared Occupancy Detector](https://www.amazon.com/DIYmall-HC-SR501-Motion-Infrared-Arduino/dp/B012ZZ4LPM)

## Let's talk Utilities

Precompiler constants
```c
#define OUTPUT 0x01
#define INPUT 0x00
```
Several helpful functions are defined in `embedded_utils.h`.

|Function Name|Brief|
|--|--|
|`void setPinMode(char port, char pin, bool mode)`|Set pin P[port].[pin] to mode (INPUT/OUTPUT)
|`void setPinState(char port, char pin, bool value)`| Set pin P[port].[pin] to value
|`void togglePinState(char port, char pin)`| Toggle the value of P[port].[pin]
|`void enablePinInterrupt(char port, char pin)`| Enable interrupts locally on pin P[port].[pin]
|`void killWatchdogTimer()`|Kills the watchdog timer
|`void unlockGPIO()`|Disable low power lock on GPIO