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
  
  // Modules disable
  PMD0 = 0b00011110; //
  PMD1 = 0b11111110;
  PMD2 = 0b01000111;
  PMD3 = 0b01111111;
  PMD4 = 0b1110111;
  PMD5 = 0b11011111;
  //interrupt setting
  INTCONbits.GIE = 1;
  Delay_ms (100);
  return;
}
