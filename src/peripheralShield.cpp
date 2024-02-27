#include "peripheralShield.h"

peripheralShield::peripheralShield()
{
    // JoyStick
    pinMode(A11, INPUT);
    pinMode(A12, INPUT);

    // RGB-LED
    pinMode(44, OUTPUT);
    pinMode(45, OUTPUT);
    pinMode(46, OUTPUT);

    RGBLED(0, 0, 0);

    // Poti
    pinMode(A4, INPUT);

    // LDR
    pinMode(A8, INPUT);

    // Buttons
    pinMode(12, INPUT);
    pinMode(10, INPUT);
    pinMode(3, INPUT);
    pinMode(2, INPUT);

    // Switches
    pinMode(8, INPUT);
    pinMode(9, INPUT);
    pinMode(41, INPUT);
    pinMode(40, INPUT);

    for (int i = 0; i < 8; i++)
    {
        pinMode(lightBar[i], OUTPUT);
        lightArray(i, false);
    }

    for (int i = 0; i < segments; i++)
    {
        pinMode(segment[i], OUTPUT);
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

void peripheralShield::lightArray(const int number, const bool active)
{
    int light = 7 - number;

    digitalWrite(lightBar[light], active ? LOW : HIGH);
}

int peripheralShield::getLDRState()
{
    return analogRead(A8);
}

int peripheralShield::getPotiState()
{
    return analogRead(A4);
}

void peripheralShield::RGBLED(const int red, const int green, const int blue)
{
    digitalWrite(45, red == 1 ? LOW : HIGH);
    digitalWrite(44, green == 1 ? LOW : HIGH);
    digitalWrite(46, blue == 1 ? LOW : HIGH);
}

void peripheralShield::getJoyStickState(int *x, int *y)
{

    *x = analogRead(A11);
    *y = analogRead(A12);
}

void peripheralShield::clearSegment()
{
    for (int i = 0; i < segments; i++)
    {
        digitalWrite(segment[i], LOW);
    }
}

int peripheralShield::printSegment(const int number, const bool point)
{
    clearSegment();

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
    return 0;
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