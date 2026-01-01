#ifndef ATU10_PIC_INIT_H
#define ATU10_PIC_INIT_H


#include "xc8_compat.h"

// Connections
#define GetButton        (!PORTBbits.RB5)
#define Red              LATBbits.LATB4
#define Green            LATBbits.LATB3
#define OLED_PWD         LATAbits.LATA4
#define C_sw             LATEbits.LATE0
#define L_010            LATDbits.LATD7
#define L_022            LATDbits.LATD6
#define L_045            LATDbits.LATD5
#define L_100            LATDbits.LATD4
#define L_220            LATCbits.LATC7
#define L_450            LATCbits.LATC6
#define L_1000           LATCbits.LATC5
#define C_22             LATAbits.LATA5
#define C_47             LATEbits.LATE1
#define C_100            LATAbits.LATA7
#define C_220            LATAbits.LATA6
#define C_470            LATCbits.LATC0
#define C_1000           LATCbits.LATC1
#define C_2200           LATCbits.LATC2
#define Rel_to_gnd       LATDbits.LATD3
#define Rel_to_plus_N    LATCbits.LATC4

#ifdef EXT_BITBANG_UART_TEST
// Timer2 tick for 4x oversampled bitbang TX.
#define BB_UART_BAUD 1200u
#define BB_UART_OVERSAMPLE 4u
#define BB_UART_TMR2_PRESCALE 8u
#define BB_UART_TMR2_PRESCALE_BITS 3u
#define BB_UART_TMR2_PR2_ADJ 0
#define BB_UART_TICKS_PER_SEC (BB_UART_BAUD * BB_UART_OVERSAMPLE)
#define BB_UART_TMR2_COUNTS ((uint16_t)((_XTAL_FREQ / 4u) / (BB_UART_TICKS_PER_SEC * BB_UART_TMR2_PRESCALE)))
#define BB_UART_TMR2_PR2 ((uint8_t)(BB_UART_TMR2_COUNTS - 1u + BB_UART_TMR2_PR2_ADJ))
#endif

#endif // ATU10_PIC_INIT_H
