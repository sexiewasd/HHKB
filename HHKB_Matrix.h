#ifndef HHKB_Matrix_h
#define HHKB_Matrix_h
#include "Arduino.h"

class HHKB_Matrix {
  public:
                     HHKB_Matrix  (                             );
               void  scan         (                             );
      virtual  void  keyOn        ( uint8_t row, uint8_t column );
      virtual  void  keyOff       ( uint8_t row, uint8_t column );
  private:
};

extern HHKB_Matrix Matrix;

#endif
