# Installation

Install the Library via the [release tab](https://github.com/GameOfNicoYT/HTL-Pinkafeld-Peripherie-Schild-Library/releases) on GitHub

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

`lightArray(int number, bool active)`: Controls an individual light in a light array (bar) by turning it on or off based on the active parameter. The number parameter specifies which light to control.

`getLDRState()`: Returns the current analog reading from the light-dependent resistor (LDR), indicating the level of ambient light.

`getPotiState()`: Returns the current analog reading from the potentiometer, reflecting its rotational position.

`RGBLED(int red, int green, int blue)`: Sets the color of the RGB LED by controlling the intensity of red, green, and blue components. The parameters are binary (0 or 1), indicating off or on for each color component.

`getJoyStickState(int *x, int *y)`: Reads the current position of the joystick and returns the x and y coordinates through pointer arguments.

`clearSegment()`: Turns off all segments of a segment display to clear any previously displayed number or pattern.

`printSegment(int number, bool point)`: Displays a digit (0-9) on a segment display and optionally a decimal point. The number parameter specifies the digit, and the point parameter indicates whether to display the decimal point.

`getButtonState(int number)`: Returns the state (HIGH or LOW) of a specified button. The function handles four buttons, identified by numbers 0 through 3.

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

void joystickRGBHandler();
void joystickXHandler();

void potiSegmentHandler();

void potiArrayHandler();

void setup()
{
  Serial.begin(9600);
}

void loop()
{

  if (shield.getSwitchState(0) == 1)
  {
    joystickXHandler();
    shield.RGBLED(0, 0, 0);
    int red = shield.getSwitchState(1);
    int green = shield.getSwitchState(2);
    int blue = shield.getSwitchState(3);
    shield.RGBLED(red, green, blue);
    potiSegmentHandler();
  }
  else
  {
    joystickRGBHandler();
    for (int i = 0; i < 8; i++)
    {
      shield.lightArray(i, 0);
    }
    potiArrayHandler();
    shield.clearSegment();
  }
}

void potiSegmentHandler()
{

  float poti = shield.getPotiState();

  poti = (poti / 1024) * 10;

  poti = floor(poti);

  Serial.println(poti);

  shield.printSegment(poti, 0);
}

void joystickXHandler()
{
  int x, y;
  shield.getJoyStickState(&x, &y);

  for (int i = 0; i < 8; i++)
  {
    shield.lightArray(i, 0);
  }

  // Joystick in der Mitte
  if (x > 450 && x < 550)
  {
    shield.lightArray(3, 1);
    shield.lightArray(4, 1);
  }
  // Bewegung nach rechts (vorher links)
  else if (x <= 450)
  {
    shield.lightArray(0, 0);
    shield.lightArray(1, 0);
    shield.lightArray(2, 0);
    shield.lightArray(3, 0);
    shield.lightArray(4, 1);
    if (x < 337)
    {
      shield.lightArray(5, 1);
    }
    else
    {
      shield.lightArray(5, 0);
    }
    if (x < 224)
    {
      shield.lightArray(6, 1);
    }
    else
    {
      shield.lightArray(6, 0);
    }
    if (x < 111)
    {
      shield.lightArray(7, 1);
    }
    else
    {
      shield.lightArray(7, 0);
    }
  }
  // Bewegung nach links (vorher rechts)
  else if (x >= 550)
  {
    shield.lightArray(3, 1);
    shield.lightArray(4, 0);
    shield.lightArray(5, 0);
    shield.lightArray(6, 0);
    shield.lightArray(7, 0);
    if (x > 669)
    {
      shield.lightArray(2, 1);
    }
    else
    {
      shield.lightArray(2, 0);
    }
    if (x > 788)
    {
      shield.lightArray(1, 1);
    }
    else
    {
      shield.lightArray(1, 0);
    }
    if (x > 907)
    {
      shield.lightArray(0, 1);
    }
    else
    {
      shield.lightArray(0, 0);
    }
  }
}

void joystickRGBHandler()
{
  int x, y;
  shield.getJoyStickState(&x, &y);

  if (x < 400)
  {
    shield.RGBLED(1, -1, -1);
  }
  else
  {
    shield.RGBLED(0, -1, -1);
  }
  if (x > 600)
  {
    shield.RGBLED(-1, 1, -1);
  }
  else
  {
    shield.RGBLED(-1, 0, -1);
  }
  if (y < 400)
  {
    shield.RGBLED(-1, -1, 1);
  }
  else
  {
    shield.RGBLED(-1, -1, 0);
  }
  if (y > 600)
  {
    shield.RGBLED(1, 1, 1);
  }

  if (y > 400 && x > 400 && y < 600 && x < 600)
  {
    shield.RGBLED(0, 0, 0);
  }
}

void potiArrayHandler()
{

  float poti = shield.getPotiState();

  poti = (poti / 1024) * 100;

  poti = floor(poti);

  if (poti > 12)
  {
    shield.lightArray(0, 1);
    if (poti > 24)
    {
      shield.lightArray(1, 1);
      if (poti > 36)
      {
        shield.lightArray(2, 1);
        if (poti > 48)
        {
          shield.lightArray(3, 1);
          if (poti > 60)
          {
            shield.lightArray(4, 1);
            if (poti > 72)
            {
              shield.lightArray(5, 1);
              if (poti > 84)
              {
                shield.lightArray(6, 1);
                if (poti > 96)
                {
                  shield.lightArray(7, 1);
                }
                else
                {
                  shield.lightArray(7, 0);
                }
              }
              else
              {
                shield.lightArray(6, 0);
              }
            }
            else
            {
              shield.lightArray(5, 0);
            }
          }
          else
          {
            shield.lightArray(4, 0);
          }
        }
        else
        {
          shield.lightArray(3, 0);
        }
      }
      else
      {
        shield.lightArray(2, 0);
      }
    }
    else
    {
      shield.lightArray(1, 0);
    }
  }
  else
  {
    shield.lightArray(0, 0);
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
