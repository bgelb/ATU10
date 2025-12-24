#include "pic_init.h"

// pic_init unit for Micro C PRO
// 2020

void pic_init (void) {
// ports initialisation
  ANSELA = 0;         // all as digital
  ANSELB = 0;         // all as digital
  ANSELBbits.ANSB0 = 1;      // analog input
  ANSELBbits.ANSB1 = 1;      // analog input
  ANSELBbits.ANSB2 = 1;      // analog input
  ANSELC = 0;         // all as digital
  ANSELE = 0;         // all as digital
  ANSELD = 0;         // all as digital

  CM1CON0bits.C1ON = 0;      // Disable comparators
  CM2CON0bits.C2ON = 0;

  PORTA = 0;
  PORTB = 0;
  PORTC = 0;
  PORTD = 0;
  PORTE = 0;
  LATA = 0b00000000;
  LATB = 0b00000000;
  LATC = 0b00010000;
  LATD = 0b00000110;
  LATE = 0b00000000;
  TRISA = 0b00000000;
  TRISB = 0b00100111;
  TRISC = 0b00000000;
  TRISD = 0b00000000;
  TRISE = 0b00000000;

  // open drains
  ODCONAbits.ODCA2 = 1;
  ODCONAbits.ODCA3 = 1;
  ODCONDbits.ODCD1 = 1;
  ODCONDbits.ODCD2 = 1;
  
  // Timer0 settings
  T0CON1bits.T0CS0 = 0; // Fosc/4
  T0CON1bits.T0CS1 = 1;
  T0CON1bits.T0CS2 = 0;
  T0CON0bits.T016BIT = 1;
  TMR0L = 0xC0;   // 8_000 cycles to OF
  TMR0H = 0xE0;
  PIR0bits.TMR0IF = 0;
  T0CON0bits.T0EN = 1;
  PIE0bits.TMR0IE = 1;

#ifdef EXT_BITBANG_UART_TEST
  // Timer2 settings for 4x bitbang UART tick.
  T2CLKCONbits.CS = 0x1; // Fosc/4 (hardcoded)
  T2HLT = 0x00;           // Free-running mode
  T2RST = 0x00;           // No reset source
  T2CONbits.T2CKPS = 0;   // 1:1 prescale
  T2CONbits.T2OUTPS = 0;  // 1:1 postscale
  PR2 = BB_UART_TMR2_PR2;
  TMR2 = 0;
  PIR4bits.TMR2IF = 0;
  PIE4bits.TMR2IE = 0;
  T2CONbits.TMR2ON = 0;
#endif

  // Modules disable
  PMD0 = 0b00011110; //
#ifdef EXT_BITBANG_UART_TEST
  PMD1 = 0b11111010; // Keep Timer2 enabled for UART tick.
#else
  PMD1 = 0b11111110;
#endif
  PMD2 = 0b01000111;
  PMD3 = 0b01111111;
  PMD4 = 0b1110111;
  PMD5 = 0b11011111;
  //interrupt setting
  INTCONbits.GIE = 1;
  Delay_ms (100);
  return;
}
