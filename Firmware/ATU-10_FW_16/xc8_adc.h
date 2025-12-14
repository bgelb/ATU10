#ifndef ATU10_XC8_ADC_H
#define ATU10_XC8_ADC_H

#include <xc.h>
#include <stdint.h>

// ADC helpers mirroring mikroC library calls, but implemented for XC8.
#define _ADC_INTERNAL_VREFL 0x01
#define _ADC_INTERNAL_FVRH1 0x02
#define _ADC_INTERNAL_FVRH2 0x04
#define _ADC_INTERNAL_VREFH 0x08

void ADC_Init(void);
void ADC_Init_Advanced(uint8_t cfg);
unsigned int ADC_Get_Sample(uint8_t channel);

#endif // ATU10_XC8_ADC_H
