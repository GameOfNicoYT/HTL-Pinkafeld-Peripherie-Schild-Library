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

#ifndef peripheralShield_h
#define peripheralShield_h

#include <Arduino.h>

class Led
{
public:
  void rgb(int red, int green, int blue);
  void hex(unsigned long hex);
};

class Buzzer
{
public:
  void success();
  void error();
  void reading();
  void understood();
  void criticalError();
  void alarm();
  void frequency(unsigned const int frequency);
  void stop();
};

class JoyStick
{
public:
  void getRaw(int *x, int *y);
  int x();
  int y();
};

class Segment
{
public:
  void clear();
  void print(const int number, const bool point);
  void manual(const int segment, const bool state);

private:
  const int segmentsNumber = 8;
  int segmentArray[8] = {30, 31, 32, 33, 34, 35, 36, 37};
};

class peripheralShield
{
public:
  peripheralShield(); // Konstruktor
  void lightArray(const int number, const bool active);
  int getButtonState(const int number);
  int getSwitchState(const int number);
  int getLDRState();
  int getPotiState();
  Buzzer buzzer;
  JoyStick joystick;
  Segment segment;
  Led led;

private:
  const int segmentsNumber = 8;
  int segmentArray[8] = {30, 31, 32, 33, 34, 35, 36, 37};
  int lightBar[8] = {22, 23, 24, 25, 26, 27, 28, 29};
};

#endif
