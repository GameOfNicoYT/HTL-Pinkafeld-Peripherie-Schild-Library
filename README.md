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
4. Open up the src folder of the ZIP file
5. Extract the .h file into the include Folder of your PlatformIO Project
6. Extract the .cpp file into the src folder of your PlatformIO Project

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
