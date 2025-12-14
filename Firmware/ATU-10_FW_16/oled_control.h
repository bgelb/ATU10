#ifndef ATU10_OLED_CONTROL_H
#define ATU10_OLED_CONTROL_H


#include "xc8_compat.h"
#include "font_5x8.h"

static const uint8_t oled_addr = 0x78;
static char shift_line = 64;  // shift the image down
static char oled_shift = 2;  // shift the image left
static char inversion = 1;
//
void oled_init (void);
void oled_clear(void);
void send_command (char);
void set_addressing (char, char);
void oled_wr_str_s(char, char, char*, char);
void oled_wr_str(char, char, char*, char);
void oled_bat (void);
void oled_voltage (int);
void oled_clear (void);

//
static const char  batt[] = {
 0b11111000,
 0b11111000,

 0b00011111,
 0b00011111,
 0b00000011,
 0b00000011,
 0b00000011,
 0b00011111,
 0b00011111,

 0b11111000,
 0b11111000,
 //
 0b11111111,
 0b11111111,
 0b00000000,
 0b00000000,
 0b00000000,
 0b00000000,
 0b00000000,
 0b00000000,
 0b00000000,
 0b11111111,
 0b11111111,
 //
 0b11111111,
 0b11111111,
 0b00000000,
 0b00000000,
 0b00000000,
 0b00000000,
 0b00000000,
 0b00000000,
 0b00000000,
 0b11111111,
 0b11111111,
 //
 0b11111111,
 0b11111111,
 0b11000000,
 0b11000000,
 0b11000000,
 0b11000000,
 0b11000000,
 0b11000000,
 0b11000000,
 0b11111111,
 0b11111111
 };

#endif // ATU10_OLED_CONTROL_H
