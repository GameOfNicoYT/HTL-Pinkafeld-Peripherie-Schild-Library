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
