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

class peripheralShield
{
public:
  peripheralShield(); // Konstruktor
  void initShield();
  void lightArray(const int number, const bool active);
  int getButtonState(const int number);
  int getSwitchState(const int number);
  int printSegment(const int number, const bool point);
  void clearSegment();
  int getLDRState();
  int getPotiState();
  void getJoyStickState(int *x, int *y);
  void RGBLED(int red, int green, int blue);

private:
  const int segments = 8;
  int segment[8] = {30, 31, 32, 33, 34, 35, 36, 37};
  int lightBar[8] = {22, 23, 24, 25, 26, 27, 28, 29};
};

#endif
