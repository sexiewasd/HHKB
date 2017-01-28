#include <HID-Project.h>
#include <HID-Settings.h>
#include "HHKB_Matrix.h"
#include "Keymaps.h"
Keymaps* keymaps;

const KeyboardKeycode(*currentKeymap)[8] = Keymaps::keymapDefault;

void setup() {
  // put your setup code here, to run once:
//     Serial.begin(57600);
//     while (!Serial) {
//         ; // wait for serial port to connect. Needed for native USB port only
//     }
    NKROKeyboard.begin();
}

void loop() {
     Matrix.scan();
}

void HHKB_Matrix::keyOn(uint8_t row, uint8_t column) {
      KeyboardKeycode key = keymaps->getKey(currentKeymap, row, column);
      if (key == KEY_RESERVED) {
          currentKeymap = Keymaps::keymapDefaultAlternate;
        }
      NKROKeyboard.press(key);
}

void HHKB_Matrix::keyOff(byte row, byte column) {
      KeyboardKeycode key = keymaps->getKey(currentKeymap, row, column);
      if (key == KEY_RESERVED) {
          currentKeymap = Keymaps::keymapDefault;
        }
      NKROKeyboard.release(key);
}

