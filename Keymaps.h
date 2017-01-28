#ifndef Keymaps_h
#define Keymaps_h
#include "Arduino.h"
#include <HID-Project.h>

class Keymaps {
  public:
                          KeyboardKeycode  getKey(const KeyboardKeycode address[8][8], uint8_t row, uint8_t column);
             static const KeyboardKeycode  keymapDefault[8][8] PROGMEM;
             static const KeyboardKeycode  keymapDefaultAlternate[8][8] PROGMEM;
  private:
};
#endif
