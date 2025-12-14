#ifndef ATU10_XC8_COMPAT_H
#define ATU10_XC8_COMPAT_H


#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

// Shim layer to mimic mikroC idioms (delays, bitfields) when building under XC8.
#define _XTAL_FREQ 32000000UL

#define Delay_ms  __delay_ms
#define Delay_us  __delay_us

static inline void VDelay_ms(uint16_t ms) {
    while (ms--) {
        __delay_ms(1);
    }
}

// Simple 8-bit value with bitfield-style accessors to mimic mikroC's B0..B7
typedef union {
    uint8_t value;
    struct {
        uint8_t b0:1;
        uint8_t b1:1;
        uint8_t b2:1;
        uint8_t b3:1;
        uint8_t b4:1;
        uint8_t b5:1;
        uint8_t b6:1;
        uint8_t b7:1;
    } bits;
} bits8_t;

#define B0 bits.b0
#define B1 bits.b1
#define B2 bits.b2
#define B3 bits.b3
#define B4 bits.b4
#define B5 bits.b5
#define B6 bits.b6
#define B7 bits.b7


#endif // ATU10_XC8_COMPAT_H
