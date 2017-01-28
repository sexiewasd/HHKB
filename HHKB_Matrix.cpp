#include "HHKB_Matrix.h"
HHKB_Matrix Matrix;
HHKB_Matrix::HHKB_Matrix() {
  //  changing which pins are used on the Feather is as easy as changing the number in the pin column
  /* --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
  /*|     Definition                   |    Pin   |     PinMode                                     |   Default State                               |   HHKB  |   Function    |  Description                              |*/
  /*|----------------------------------|----------|-------------------------------------------------|-----------------------------------------------|---------|---------------|-------------------------------------------|*/ 
  /*|     N/A                          |    USB   |     Vcc                                         |                                               |   1     |   +5v         | +5v  Does not hold key state at 3.3v      |*/
  /*|                                  |          |                                                 |     N/A                                       |         |               |      *logic pins do work at 3.3v          |*/
  /*|----------------------------------|----------|-------------------------------------------------|-----------------------------------------------|---------|---------------|-------------------------------------------|*/
  /*|     N/A                          |    USB   |     Vcc                                         |                                               |   1     |   +5v         | +5v  Does not hold key state at 3.3v      |*/
  /*|                                  |          |                                                 |     N/A                                       |         |               |      *logic pins do work at 3.3v          |*/
  /*|----------------------------------|----------|-------------------------------------------------|-----------------------------------------------|---------|---------------|-------------------------------------------|*/                   
  /*|*/   #define KEY_PIN            /*|*/  13  /*|     PC7 input(with pullup)                      |                                               |   3     |   TP1684      | ~KEY: Low(0) when key is pressed          |*/
  /*|                                  |          |*/   pinMode(KEY_PIN,           INPUT_PULLUP); /*|     N/A                                       |         |               |                                           |*/
  /*|----------------------------------|----------|-------------------------------------------------|-----------------------------------------------|---------|---------------|-------------------------------------------|*/
  /*|*/   #define HYS_PIN            /*|*/  12  /*|     PD6 output                                  |                                               |   4     |   TP1684      |  HYS: High(1) when key is pressed         |*/
  /*|                                  |          |*/   pinMode(HYS_PIN,           OUTPUT);        /*|*/   digitalWrite(HYS_PIN,          LOW);   /*|         |               |                                           |*/
  /*|----------------------------------|----------|-------------------------------------------------|-----------------------------------------------|---------|---------------|-------------------------------------------|*/
  /*|*/   #define ROW_PIN_0          /*|*/  11  /*|     PB7 output                                  |                                               |   5     |   HC4051      |  A(bit0)\                                 |*/
  /*|                                  |          |*/   pinMode(ROW_PIN_0,         OUTPUT);       /*|*/   digitalWrite(ROW_PIN_0,         HIGH);  /*|         |               |                                           |*/
  /*|----------------------------------|----------|-------------------------------------------------|-----------------------------------------------|---------|---------------|-------------------------------------------|*/
  /*|*/   #define ROW_PIN_1          /*|*/  10  /*|     PB6 output                                  |                                               |   6     |   HC4051      |  B(bit1) > select row 0-7                 |*/
  /*|                                  |          |*/   pinMode(ROW_PIN_1,         OUTPUT);       /*|*/   digitalWrite(ROW_PIN_1,         HIGH);  /*|         |               |                                           |*/
  /*|----------------------------------|----------|-------------------------------------------------|-----------------------------------------------|---------|---------------|-------------------------------------------|*/
  /*|*/   #define ROW_PIN_2          /*|*/  9   /*|     PD7 output                                  |                                               |   7     |   HC4051      |  C(bit2)/                                 |*/
  /*|                                  |          |*/   pinMode(ROW_PIN_2,         OUTPUT);       /*|*/   digitalWrite(ROW_PIN_2,         HIGH);  /*|         |               |                                           |*/
  /*|----------------------------------|----------|-------------------------------------------------|-----------------------------------------------|---------|---------------|-------------------------------------------|*/
  /*|*/   #define COLUMN_PIN_0       /*|*/  6   /*|     PB5 output                                  |                                               |   8     |   LS145       |  A(bit0)\                                 |*/
  /*|                                  |          |*/   pinMode(COLUMN_PIN_0,      OUTPUT);       /*|*/   digitalWrite(COLUMN_PIN_0,      HIGH);  /*|         |               |                                           |*/
  /*|----------------------------------|----------|-------------------------------------------------|-----------------------------------------------|---------|---------------|-------------------------------------------|*/
  /*|*/   #define COLUMN_PIN_1       /*|*/  5   /*|     PC6 output                                  |                                               |   9     |   LS145       |  B(bit1) > select column 0-7              |*/
  /*|                                  |          |*/   pinMode(COLUMN_PIN_1,      OUTPUT);       /*|*/   digitalWrite(COLUMN_PIN_1,      HIGH);  /*|         |               |                                           |*/
  /*|----------------------------------|----------|-------------------------------------------------|-----------------------------------------------|---------|---------------|-------------------------------------------|*/
  /*|*/   #define COLUMN_PIN_2       /*|*/  3   /*|     PD0 output                                  |                                               |   10    |   LS145       |  C(bit2)/                                 |*/
  /*|                                  |          |*/   pinMode(COLUMN_PIN_2,      OUTPUT);       /*|*/   digitalWrite(COLUMN_PIN_2,      HIGH);  /*|         |               |                                           |*/
  /*|----------------------------------|----------|-------------------------------------------------|-----------------------------------------------|---------|---------------|-------------------------------------------|*/
  /*|*/   #define COLUMN_ENABLE_PIN  /*|*/  2   /*|     PD1 output                                  |                                               |   11    |   LS145       | ~D(enable) Low(0) enables selected column |*/
  /*|                                  |          |*/   pinMode(COLUMN_ENABLE_PIN, OUTPUT) ;      /*|*/   digitalWrite(COLUMN_ENABLE_PIN, HIGH);  /*|         |               |                                           |*/
  /*|----------------------------------|----------|-------------------------------------------------|-----------------------------------------------|---------|---------------|-------------------------------------------|*/
  /*|     N/A                          |    GND   |     GND                                         |                                               |   12    |   GND         | GND                                       |*/
  /*|                                  |          |                                                 |     N/A                                       |         |               |                                           |*/
  /*|----------------------------------|----------|-------------------------------------------------|-----------------------------------------------|---------|---------------|-------------------------------------------|*/
  /*|     N/A                          |    GND   |     GND                                         |                                               |   13    |   GND         | GND                                       |*/
  /*|                                  |          |                                                 |     N/A                                       |         |               |                                           |*/
  /*|----------------------------------|----------|-------------------------------------------------|-----------------------------------------------|---------|---------------|-------------------------------------------|*/
}

void  HHKB_Matrix::scan() {
              const  uint8_t     ROW_PINS  [3]  =  { ROW_PIN_0, ROW_PIN_1, ROW_PIN_2 };           //  static array that stores the row control pins so that we can easily loop through them
              const  uint8_t  COLUMN_PINS  [3]  =  { COLUMN_PIN_0, COLUMN_PIN_1, COLUMN_PIN_2 };  //  static array that stores the column control pins so that we can easily loop through them
      static         uint8_t     keyState  [8]  =  { 0, 0, 0, 0, 0, 0, 0, 0 };                    //  static array that stores the previous key states (up/down) so we can see if they have changed
                                                                                                      //  indexes of the array represent the row number 0..7. each index stores one 8-bit byte.
                                                                                                      //  each bit position represents a column, the least significant bit is column 0
      for (uint8_t row = 0; row <= 7; row++) {                                                    //  loop through each row of keys
          for (uint8_t i=0; i<3; i++) digitalWrite(ROW_PINS[i], bitRead(row, i));                 //  loop through the pins, set the pins high/low to match each bit of the decimal "value"
          for (uint8_t column = 0; column <= 7; column++) {                                       //  for each row of keys loop through each column of keys
              for (uint8_t i=0; i<3; i++) digitalWrite(COLUMN_PINS[i], bitRead(column, i));       //  loop through the pins, set the pins high/low to match each bit of the decimal "value"
              bool previousState = bitRead(keyState[row], column);                                //  fetch the previous key state
              digitalWrite(COLUMN_ENABLE_PIN, LOW);                                               //  enable the column
              if (previousState != !digitalRead(KEY_PIN)) {                                       //  read the key state and check against the old value to see if it has changed, keypin login is reversed, LOW = Key is pressed.
                 bitWrite(keyState[row], column, !previousState);                                 //  save the new key state
                 !previousState ? keyOn(row, column) : keyOff(row, column);                       //  if the key is pressed call the keyOn function, if the key has been released call the keyOff function
              }
              digitalWrite(COLUMN_ENABLE_PIN, HIGH);                                              //  turn off the column
          }
      }
}
/*
void HHKB_Matrix::keyOn(uint8_t row, uint8_t column) { }                                           //  called when a key is first pressed
                                                                                              //  define this function in your sketch.

void HHKB_Matrix::keyOff(uint8_t row, uint8_t column) { }                                          //  called when a key is released
                                                                                              //  define this function in your sketch.
*/
