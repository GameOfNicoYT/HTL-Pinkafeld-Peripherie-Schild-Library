/*

Copyright © 2023-2024 Nico Proyer. All rights reserved.

This library is free software; you can redistribute it and/or modify it under the
terms of the GNU Lesser General Public License as published by the Free Software
Foundation; either version 2.1 of the License, or (at your option) any later
version.

This library is distributed in the hope that it will be useful, but WITHOUT ANY
 WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along
with this library; if not, write to:
Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

*/

#include "peripheralShield.h"

peripheralShield::peripheralShield()
{

    // Buzzer
    pinMode(39, OUTPUT);

    // JoyStick
    pinMode(A11, INPUT);
    pinMode(A12, INPUT);

    // RGB-LED
    pinMode(44, OUTPUT);
    pinMode(45, OUTPUT);
    pinMode(46, OUTPUT);

    led.rgb(0, 0, 0);

    // Poti
    pinMode(A4, INPUT);

    // LDR
    pinMode(A8, INPUT);

    // Buttons
    pinMode(12, INPUT_PULLUP);
    pinMode(10, INPUT_PULLUP);
    pinMode(3, INPUT_PULLUP);
    pinMode(2, INPUT_PULLUP);

    // Switches
    pinMode(8, INPUT);
    pinMode(9, INPUT);
    pinMode(41, INPUT);
    pinMode(40, INPUT);

    for (int i = 0; i < 8; i++)
    {
        pinMode(lightBar[i], OUTPUT);
        lightarray.manual(i, false);
    }

    for (int i = 0; i < segmentsNumber; i++)
    {
        pinMode(segmentArray[i], OUTPUT);
    }
}

int peripheralShield::getSwitchState(const int number)
{
    switch (number)
    {
    case 0:
        return digitalRead(8);
        break;
    case 1:
        return digitalRead(9);
        break;
    case 2:
        return digitalRead(41);
        break;
    case 3:
        return digitalRead(40);
        break;
    }
    return -1;
}

void LightArray::manual(const int number, const bool active)
{
    int light = 7 - number;

    digitalWrite(lightBar[light], active ? LOW : HIGH);
}
void LightArray::nightRider(const bool reverse, const int time, const int repeat)
{
    for (int i = 0; i < repeat; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            digitalWrite(lightBar[j], HIGH);

            if (j > 2)
            {
                digitalWrite(lightBar[j - 2], Low);
            }
            delay((int)(time / 8));
        }
    }
}

int LDR::getData()
{
    return analogRead(A8);
}

int Poti::getData()
{
    return analogRead(A4);
}

void Led::rgb(int red, int green, int blue)
{

    if (red != -1)
    {
        red = map(red, 0, 255, 1023, 0);
        analogWrite(45, red);
    }
    if (green != -1)
    {
        green = map(green, 0, 255, 1023, 0);
        analogWrite(44, green);
    }
    if (blue != -1)
    {
        blue = map(blue, 0, 255, 1023, 0);
        analogWrite(46, blue);
    }
}

void Led::hex(unsigned long hex)
{

    byte red = (hex >> 16) & 0xFF;  // Verschiebe um 16 Bits nach rechts und isoliere die letzten zwei Stellen
    byte green = (hex >> 8) & 0xFF; // Verschiebe um 8 Bits nach rechts und isoliere die mittleren zwei Stellen
    byte blue = hex & 0xFF;         // Isoliere die letzten zwei Stellen

    red = map(red, 0, 255, 255, 0);
    green = map(green, 0, 255, 255, 0);
    blue = map(blue, 0, 255, 255, 0);

    analogWrite(45, red);
    analogWrite(44, green);
    analogWrite(46, blue);
}

void JoyStick::getRaw(int *x, int *y)
{

    *x = analogRead(A11);
    *y = analogRead(A12);
}

int JoyStick::x()
{
    return analogRead(A11);
}

int JoyStick::y()
{
    return analogRead(A12);
}

void Segment::clear()
{
    for (int i = 0; i < segmentsNumber; i++)
    {
        digitalWrite(segmentArray[i], LOW);
    }
}

void Segment::manual(const int segment, const bool state)
{
    int number = map(segment, 0, 8, 38, 30);

    digitalWrite(number, state);
}

void Segment::print(const int number, const bool point)
{
    clear();

    switch (number)
    {
    case 0:
        digitalWrite(32, HIGH);
        digitalWrite(33, HIGH);
        digitalWrite(34, HIGH);
        digitalWrite(35, HIGH);
        digitalWrite(36, HIGH);
        digitalWrite(37, HIGH);
        break;
    case 1:
        digitalWrite(35, HIGH);
        digitalWrite(36, HIGH);
        break;
    case 2:
        digitalWrite(31, HIGH);
        digitalWrite(33, HIGH);
        digitalWrite(34, HIGH);
        digitalWrite(36, HIGH);
        digitalWrite(37, HIGH);
        break;
    case 3:
        digitalWrite(31, HIGH);
        digitalWrite(34, HIGH);
        digitalWrite(35, HIGH);
        digitalWrite(36, HIGH);
        digitalWrite(37, HIGH);
        break;
    case 4:
        digitalWrite(31, HIGH);
        digitalWrite(32, HIGH);
        digitalWrite(35, HIGH);
        digitalWrite(36, HIGH);
        break;
    case 5:
        digitalWrite(31, HIGH);
        digitalWrite(32, HIGH);
        digitalWrite(34, HIGH);
        digitalWrite(35, HIGH);
        digitalWrite(37, HIGH);
        break;
    case 6:
        digitalWrite(31, HIGH);
        digitalWrite(32, HIGH);
        digitalWrite(33, HIGH);
        digitalWrite(34, HIGH);
        digitalWrite(35, HIGH);
        digitalWrite(37, HIGH);
        break;
    case 7:
        digitalWrite(35, HIGH);
        digitalWrite(36, HIGH);
        digitalWrite(37, HIGH);
        break;
    case 8:
        digitalWrite(31, HIGH);
        digitalWrite(32, HIGH);
        digitalWrite(33, HIGH);
        digitalWrite(34, HIGH);
        digitalWrite(35, HIGH);
        digitalWrite(36, HIGH);
        digitalWrite(37, HIGH);
        break;
    case 9:
        digitalWrite(31, HIGH);
        digitalWrite(32, HIGH);
        digitalWrite(34, HIGH);
        digitalWrite(35, HIGH);
        digitalWrite(36, HIGH);
        digitalWrite(37, HIGH);
        break;
    default:
        break;
    }

    if (point)
    {
        digitalWrite(30, HIGH);
    }
}

int peripheralShield::getButtonState(const int number)
{
    switch (number)
    {
    case 0:
        return digitalRead(12);
        break;
    case 1:
        return digitalRead(10);
        break;
    case 2:
        return digitalRead(3);
        break;
    case 3:
        return digitalRead(2);
        break;
    default:
        return -1;
    }
    return 0;
}

void Buzzer::frequency(unsigned const int frequency)
{
    tone(39, frequency);
}

void Buzzer::stop()
{
    noTone(39);
}

void Buzzer::success()
{
    tone(39, 1000);
    delay(100);
    tone(39, 2000);
    delay(100);
    tone(39, 4000);
    delay(100);
    noTone(39);
}

void Buzzer::error()
{
    tone(39, 1000);
    delay(100);
    noTone(39);
    delay(100);
    tone(39, 1000);
    delay(100);
    noTone(39);
    delay(100);
    tone(39, 1000);
    delay(100);
    noTone(39);
    delay(100);
    noTone(39);
}

void Buzzer::reading()
{
    tone(39, 2000);
    delay(100);
    tone(39, 3000);
    delay(100);
    tone(39, 4000);
    delay(100);
    tone(39, 2000);
    delay(100);
    noTone(39);
}

void Buzzer::understood()
{
    tone(39, 4000);
    delay(100);
    noTone(39);
    delay(100);
    tone(39, 4000);
    delay(100);
    tone(39, 5000);
    delay(100);
    noTone(39);
}

void Buzzer::criticalError()
{
    tone(39, 2000);
    delay(100);
    tone(39, 3000);
    delay(100);
    tone(39, 2000);
    delay(100);
    tone(39, 3000);
    delay(100);
    tone(39, 2000);
    delay(100);
    tone(39, 3000);
    delay(100);
    noTone(39);
}

void Buzzer::alarm()
{
    for (int i = 0; i < 10; i++)
    {
        for (int i = 1000; i > 200; i--)
        {
            tone(39, i);
            delay(1);
        }
        delay(50);
    }
    noTone(39);
    delay(250);
    tone(39, 2000);
    delay(350);
    noTone(39);
    delay(200);
    tone(39, 2000);
    delay(50);
    noTone(39);
    delay(100);
    tone(39, 2000);
    delay(50);
    noTone(39);
}
