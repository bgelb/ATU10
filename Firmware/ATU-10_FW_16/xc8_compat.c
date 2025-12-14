#include "xc8_compat.h"

int IntToStr(int value, char *out){
   // mikroC's IntToStr emits a 6-wide, space-padded string; mimic that here.
   sprintf(out, "%6d", value);
   return 0;
}

unsigned char Bcd2Dec(unsigned char bcd){
   return (unsigned char)((bcd >> 4) * 10u + (bcd & 0x0Fu));
}

