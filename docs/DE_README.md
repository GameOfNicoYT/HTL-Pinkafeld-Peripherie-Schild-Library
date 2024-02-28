# Installation

Installiere die Bibliothek über den [Release-Tab](https://github.com/GameOfNicoYT/HTL-Pinkafeld-Peripherie-Schild-Library/releases) auf GitHub

**Installation in der Arduino IDE**

1. Öffne die Arduino IDE
2. Klicke auf `Sketch` und dann auf `Bibliothek einbinden`
3. Klicke auf `.ZIP-Bibliothek hinzufügen`
4. Füge zuletzt die .ZIP-Datei hinzu, die du gerade heruntergeladen hast. Und zack, fertig!

**Installation in Visual Studio Code mit Platform IO**

1. Öffne Visual Studio Code
2. Erstelle ein neues PlatformIO-Projekt
3. Öffne den src-Ordner der ZIP-Datei
4. Extrahiere die .h-Datei in den Include-Ordner deines PlatformIO-Projekts
5. Extrahiere die .cpp-Datei in den src-Ordner deines PlatformIO-Projekts

# Nutzung

Importiere die Bibliothek mit folgendem Befehl:

```c++
#include <peripheralShield.h>
```

Und füge ein Synonym für peripheralShield hinzu wie folgt:

```c++
peripheralShield shield;
```

Nun kannst du auf alle coolen Funktionen der Bibliothek mit `shield.xxxxx` zugreifen

#Funktionen:

`getSwitchState(int number)`: Gibt den Zustand (HIGH oder LOW) eines bestimmten Schalters zurück. Die Funktion behandelt vier Schalter, die durch Nummern 0 bis 3 identifiziert werden.

`lightArray(int number, bool active)`: Steuert ein einzelnes Licht in einem Lichtarray (Leiste), indem es basierend auf dem aktiven Parameter ein- oder ausgeschaltet wird. Der Parameter number gibt an, welches Licht gesteuert werden soll.

`getLDRState()`: Gibt den aktuellen analogen Wert des lichtabhängigen Widerstands (LDR) zurück, der das Niveau des Umgebungslichts anzeigt.

`getPotiState()`: Gibt den aktuellen analogen Wert des Potentiometers zurück, der seine Drehposition widerspiegelt.

`RGBLED(int red, int green, int blue)`: Legt die Farbe der RGB-LED fest, indem die Intensität der Rot-, Grün- und Blaukomponenten gesteuert wird. Die Parameter sind binär (0 oder 1) und geben an, ob jede Farbkomponente aus- oder eingeschaltet ist.

`getJoyStickState(int *x, int *y)`: Liest die aktuelle Position des Joysticks und gibt die x- und y-Koordinaten über Zeigerargumente zurück.

`clearSegment()`: Schaltet alle Segmente einer Segmentanzeige aus, um eine zuvor angezeigte Zahl oder ein Muster zu löschen.

`printSegment(int number, bool point)`: Zeigt eine Ziffer (0-9) auf einer Segmentanzeige an und optional einen Dezimalpunkt. Der Parameter number gibt die Ziffer an, und der Parameter point gibt an, ob der Dezimalpunkt angezeigt werden soll.

`getButtonState(int number)`: Gibt den Zustand (HIGH oder LOW) eines bestimmten Knopfes zurück. Die Funktion behandelt vier Knöpfe, die durch Nummern 0 bis 3 identifiziert werden.

## Beispiel:

Dies ist ein Beispiel für fast alles, was das Board anzeigen kann. Der Schalter auf der linken Seite ist für den Modus.

### 1. Schalter links = **Oben**

Wenn der linke Schalter oben ist, kannst du das Segmentdisplay mit dem Potentiometer und das LED-Array mit dem Joystick sowie das Segmentdisplay mit dem Potentiometer steuern.

Das LED-Array zeigt die x-Richtung des Joysticks an.

Die RGB-LED kann mit den drei rechten Schaltern gesteuert werden.

Das Segmentdisplay kann mit dem Potentiometer gesteuert werden.

### 2. Schalter links = **Unten**

Wenn der linke Schalter unten ist, kann das Lichtarray mit dem Potentiometer gesteuert werden und der Joystick ist für die RGB-LED.

Das LED-Array zeigt die Drehung des Potentiometers an.

Die RGB-LED kann mit dem Joystick gesteuert werden.

| **Joystick** | **RGB LED** |
| ------------ | ----------- |
| Oben         | Weiß        |
| Unten        | Blau        |
| Rechts       | Rot         |
| Linkjs       | Grün        |

```c++
#include <Arduino.h>
#include <peripheralShield.h>

peripheralShield shield;

// Function prototypes for better readability
void joystickRGBHandler();
void joystickXHandler();
void potiSegmentHandler();
void potiArrayHandler();
void lightJoystickDirection(int start, int end, int x, int firstThreshold, int secondThreshold, int thirdThreshold, int direction);

void setup()
{
  Serial.begin(9600); // Initialize serial communication at 9600 bits per second
}

void loop()
{
  // Check switch state and call appropriate handlers
  if (shield.getSwitchState(0) == 1)
  {
    joystickXHandler();
    // Reset RGB LED before setting new colors
    shield.RGBLED(0, 0, 0);
    // Set RGB LED based on switch states
    int red = shield.getSwitchState(1);
    int green = shield.getSwitchState(2);
    int blue = shield.getSwitchState(3);
    shield.RGBLED(red, green, blue);
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
    shield.clearSegment();
  }
}

// Handles the potentiometer input for the 7-segment display
void potiSegmentHandler()
{
  float poti = shield.getPotiState();
  // Scale potentiometer value to range 0-10
  poti = (poti / 1024) * 10;
  poti = floor(poti);
  shield.printSegment(poti, 0); // Display poti value on 7-segment display
}

// Handles joystick X-axis movement for the LED array
void joystickXHandler()
{
  int x, y;
  shield.getJoyStickState(&x, &y); // Get joystick state

  // Clear LED array before setting new state
  for (int i = 0; i < 8; i++)
  {
    shield.lightArray(i, 0);
  }

  // Handle joystick position and light up LEDs accordingly
  // The joystick handling is divided into regions based on the X-axis value
  if (x > 450 && x < 550)
  {
    // Joystick in middle position
    shield.lightArray(3, 1);
    shield.lightArray(4, 1);
  }
  else if (x <= 450)
  {
    // Joystick moved to the right
    lightJoystickDirection(4, 7, x, 350, 125, 10, 1);
  }
  else if (x >= 550)
  {
    // Joystick moved to the left
    lightJoystickDirection(0, 3, x, 700, 800, 1000, -1);
  }
}

// Refactored function to light up LEDs based on joystick direction
void lightJoystickDirection(int start, int end, int x, int firstThreshold, int secondThreshold, int thirdThreshold, int direction)
{
  // Zuerst alle LEDs ausschalten
  for (int i = start; i <= end; i++)
  {
    shield.lightArray(i, 0);
  }

  Serial.println(x);

  // Decide how many LEDs should be turned on with respect of the threshold
  int activeLedCount = 1;
  if (direction == -1)
  {
    if (x > firstThreshold)
      activeLedCount = 2;
    if (x > secondThreshold)
      activeLedCount = 3;
    if (x > thirdThreshold)
      activeLedCount = 4;
  }
  if (direction == 1)
  {
    if (x < firstThreshold)
      activeLedCount = 2;
    if (x < secondThreshold)
      activeLedCount = 3;
    if (x < thirdThreshold)
      activeLedCount = 4;
  }
  // Activate LEDs with respect to direction
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
  shield.getJoyStickState(&x, &y); // Get joystick state

  // Set RGB LED based on joystick position
  if (x < 400)
  {
    shield.RGBLED(1, -1, -1); // Red
  }
  else if (x > 600)
  {
    shield.RGBLED(-1, 1, -1); // Green
  }
  if (y < 400)
  {
    shield.RGBLED(-1, -1, 1); // Blue
  }
  else if (y > 600)
  {
    shield.RGBLED(1, 1, 1); // White
  }
  if (y > 400 && x > 400 && y < 600 && x < 600)
  {
    shield.RGBLED(0, 0, 0); // Off
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
Dies ist ein color Picker. Du kannst die Rot Grün und Blau (RGB) anteile mit den linken drei Schaltern ein oder aus schalten.

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
