# Installation

Download the Library via the [release tab](https://github.com/GameOfNicoYT/HTL-Pinkafeld-Peripherie-Schild-Library/releases) on GitHub

**Installation in the Arduino IDE**

1. Open the Arduino IDE
2. Click on `Sketch`, and then on `Include Library`
3. Click on `Add .ZIP Library`
4. Finally append the .ZIP file, you just downloaded. And boom, you're done!

**Installation in Visual Studio Code with Platform IO**

1. Open Visual Studio Code
2. Create a new PlatformIO Project
3. Open up the src folder of the ZIP file
4. Extract the .h file into the include Folder of your PlatformIO Project
5. Extract the .cpp file into the src folder of your PlatformIO Project

# Usage

Import the library with following command:

```c++
#include <peripheralShield.h>
```

And add a synonym for peripheralShield like this:

```c++
peripheralShield shield;
```

Now you can get access to all the cool functions of the library with `shield.xxxxx`

## Functions:

`getSwitchState(int number)`: Returns the state (HIGH or LOW) of a specified switch. The function handles four switches, identified by numbers 0 through 3.

`lightArray.manual(int number, bool active)`: Controls an individual light in a light array (bar) by turning it on or off based on the active parameter. The number parameter specifies which light to control.

`lightArray.nightRider( int time, int repeat)`: Creates a NightRider effect, where the lights swoosh from left to right and reverse. The number of revision can be defined, as well as the time one revision takes.

`ldr.getData()`: Returns the current analog reading from the light-dependent resistor (LDR), indicating the level of ambient light.

`poti.getData()`: Returns the current analog reading from the potentiometer, reflecting its rotational position.

`led.rgb(int red, int green, int blue)`: Sets the color of the RGB LED by controlling the intensity of red, green, and blue components. The parameters are integers (0 - 255).

`led.hex(unsigned long hex)`: Sets the color of the RGB LED by controlling the intensity of red, green, and blue components. The parameters are hex numbers (0x000000 - 0xffffff). The first two numbers are for the red the middle two are for green and the last are for blue.

`joystick.getRaw(int *x, int *y)`: Reads the current position of the joystick and returns the x and y coordinates through pointer arguments.

`joystick.x()`: Returns the x Position of the JoyStick

`joystick.y()`: Returns the y Position of the JoyStick

`segment.clear()`: Turns off all segments of a segment display to clear any previously displayed number or pattern.

`segment.print(int number, bool point)`: Displays a digit (0-9) on a segment display and optionally a decimal point. The number parameter specifies the digit, and the point parameter indicates whether to display the decimal point.

`segment.manual(int segment, bool state)`: Changes the status of one of the seven (eight with dot) segments manually.

`getButtonState(int number)`: Returns the state (HIGH or LOW) of a specified button. The function handles four buttons, identified by numbers 0 through 3.

`buzzer.xxxxxxx()`: buzzer functions are sound function. You can read the sounds in the table below.

| name                     | description                                                                          |
| ------------------------ | ------------------------------------------------------------------------------------ |
| success()                | A charming sound of successfulness                                                   |
| error()                  | A sound for small errors like a wrong input. Nothing severe.                         |
| reading()                | A confirmation sound, that something is reading. Maybe helpful for NFC               |
| understood()             | A complementary sound of the reading sound. Just wonderfull after a hard scan.       |
| criticalError()          | A sound for BIG errors like a file missing or a non functional code.                 |
| alarm()                  | A sound for every thief who is just thinking about stealing your nice circuit board. |
| frequency(int frequency) | A function for you to freely experiment. You can plot your own frequencies.          |
| stop()                   | Stops the sound party                                                                |

## Example:

This is a example of nearly anything that the board can display. The switch on the left side is for the mode.

### 1. Switch Left = **Up**

If the left switch is up you can control the segment display with the Potentiometer and the led array with the Joystick as well as the segment display with the Potentiometer.

The LED array displays the x direction of the Joystick.

The RGB LED can be controlled with the three right switches.

The Segment display can be controlled with the Potentiometer.

### 2. Switch Left = **Down**

If the left switch is down the Light Array can be controlled with the Potentiometer and the Joystick is for the RGB LED.

The LED array displays the amount the Potentiometer was turned.

The RGB LED can be controlled with the Joystick.

| **Joystick** | **RGB LED** |
| ------------ | ----------- |
| Up           | White       |
| Down         | Blue        |
| Right        | Red         |
| Left         | Green       |

```c++

#include <Arduino.h>
#include <peripheralShield.h>

peripheralShield shield;

// Function prototypes for better readability
void joystickRGBHandler();
void joystickXHandler();
void potiSegmentHandler();
void potiArrayHandler();
void lightJoystickDirection(int start, int end, int x, int direction);

void setup()
{
  Serial.begin(9600); // Initialize serial communication at 9600 bits per second
}

void loop()
{

  if (shield.getSwitchState(0))
  {
    if (shield.getButtonState(0) == 0)
    {
      shield.buzzer.alarm();
    }
    if (shield.getButtonState(1) == 0)
    {
      shield.buzzer.success();
    }
    if (shield.getButtonState(2) == 0)
    {
      shield.buzzer.error();
    }
    if (shield.getButtonState(3) == 0)
    {
      shield.buzzer.criticalError();
    }
  }
  else
  {
    if (shield.getButtonState(0) == 0)
    {
      shield.buzzer.reading();
    }
    if (shield.getButtonState(1) == 0)
    {
      shield.buzzer.understood();
    }
    if (shield.getButtonState(2) == 0)
    {
      shield.buzzer.frequency(2000);
    }
    if (shield.getButtonState(3) == 0)
    {
      shield.buzzer.stop();
    }
  }

  // Check switch state and call appropriate handlers
  if (shield.getSwitchState(0) == 1)
  {
    joystickXHandler();
    // Reset RGB LED before setting new colors
    shield.led.rgb(0, 0, 0);
    // Set RGB LED based on switch states
    int red = shield.getSwitchState(1) == HIGH ? 255 : 0;
    int green = shield.getSwitchState(2) == HIGH ? 255 : 0;
    int blue = shield.getSwitchState(3) == HIGH ? 255 : 0;
    shield.led.rgb(red, green, blue);
    potiSegmentHandler();
  }
  else
  {
    joystickRGBHandler();
    // Turn off all LEDs in the array
    for (int i = 0; i < 8; i++)
    {
      shield.lightArray(i, 0);
    }
    potiArrayHandler();
    // Clear the 7-segment display
    shield.segment.clear();
  }
}

// Handles the potentiometer input for the 7-segment display
void potiSegmentHandler()
{
  float poti = shield.getPotiState();
  // Scale potentiometer value to range 0-10
  poti = (poti / 1024) * 10;
  poti = floor(poti);
  shield.segment.print(poti, 0); // Display poti value on 7-segment display
}

// Handles joystick X-axis movement for the LED array
bool activeBlink = false;
unsigned long previousMillis = 0;
void joystickXHandler()
{
  int x, y;
  shield.joystick.getRaw(&x, &y); // Get joystick state

  // Clear LED array before setting new state
  for (int i = 0; i < 8; i++)
  {
    shield.lightArray(i, 0);
  }

  int blinkFactor = map(y, 1024, 0, 100, 500);

  unsigned long interval = blinkFactor;
  unsigned long currentMillis = millis();

  // Handle joystick position and light up LEDs accordingly
  // The joystick handling is divided into regions based on the X-axis value

  if (x > 450 && x < 550)
  {
    if (currentMillis - previousMillis >= interval)
    {
      previousMillis = currentMillis;
      activeBlink = !activeBlink;
    }

    shield.lightArray(3, activeBlink ? 1 : 0);
    shield.lightArray(4, activeBlink ? 1 : 0);
  }
  else if (x <= 450)
  {
    // Joystick moved to the right
    lightJoystickDirection(4, 7, x, 1);
  }
  else if (x >= 550)
  {
    // Joystick moved to the left
    lightJoystickDirection(0, 3, x, -1);
  }
}

// Refactored function to light up LEDs based on joystick direction
void lightJoystickDirection(int start, int end, int x, int direction)
{
  for (int i = start; i <= end; i++)
  {
    shield.lightArray(i, 0);
  }

  Serial.println(x);

  int activeLedCount;
  if (direction == -1)
  {
    activeLedCount = map(x, 550, 1020, 1, 4);
  }
  if (direction == 1)
  {
    activeLedCount = map(x, 450, 4, 1, 4);
  }

  for (int i = 0; i < activeLedCount; i++)
  {
    int ledIndex;
    if (direction == -1)
    {
      ledIndex = end - i;
    }
    if (direction == 1)
    {
      ledIndex = start + i;
    }
    shield.lightArray(ledIndex, 1);
  }
}

// Handles the joystick input to change RGB LED colors
void joystickRGBHandler()
{
  int x, y;
  shield.joystick.getRaw(&x, &y); // Get joystick state

  shield.led.rgb(0, 0, 0);

  Serial.print(x);
  Serial.print(" | ");
  Serial.println(y);

  // Set RGB LED based on joystick position
  if (x < 400)
  {
    shield.led.rgb(255, -1, -1); // Red
  }
  else if (x > 600)
  {
    shield.led.rgb(-1, 255, -1); // Green
  }
  if (y < 400)
  {
    shield.led.rgb(-1, -1, 255); // Blue
  }
  else if (y > 600)
  {
    shield.led.rgb(255, 255, 255); // White
  }
  if (y > 400 && x > 400 && y < 600 && x < 600)
  {
    shield.led.rgb(0, 0, 0); // Off
  }
}

// Handles the potentiometer input for lighting up the LED array
void potiArrayHandler()
{
  float poti = shield.getPotiState();
  // Scale potentiometer value to range 0-100
  poti = (poti / 1024) * 100;
  poti = floor(poti);

  // Light up LED array based on poti value thresholds
  for (int i = 0; i < 8; i++)
  {
    if (poti > (12 + i * 12))
    {
      shield.lightArray(i, 1);
    }
    else
    {
      shield.lightArray(i, 0);
    }
  }
}


```

This code is a color Picker. You can activate the Red Green and Blue (RGB) Parts of the LED with the left thee switches.

```c++
#include <Arduino.h>
#include <peripheralShield.h>

peripheralShield shield;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  if (shield.getButtonState(0) == 1)
  {
    shield.RGBLED(1, 0, 0);
  }
  else
  {
    shield.RGBLED(0, 0, 0);
  }
    if (shield.getButtonState(1) == 1)
  {
    shield.RGBLED(0, 1, 0);
  }
  else
  {
    shield.RGBLED(0, 0, 0);
  }
    if (shield.getButtonState(2) == 1)
  {
    shield.RGBLED(0, 0, 1);
  }
  else
  {
    shield.RGBLED(0, 0, 0);
  }
}
```

# LICENCE

Copyright © 2023-2024 Nico Proyer. All rights reserved.

This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with this library; if not, write to the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
