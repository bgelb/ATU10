#ifndef ATU10_XC8_ADC_H
#define ATU10_XC8_ADC_H

#include <xc.h>
#include <stdint.h>

// ADC helpers mirroring mikroC library calls, but implemented for XC8.
// mikroC encodes ADREF settings in bits 0..4 and the ADC FVR gain (FVRCON.ADFVR) in bits 6..7.
// ADC_Init_Advanced() masks/uses these bits directly (see mikroC __Lib_ADC_18xxx.c listing).
#define _ADC_INTERNAL_VREFL 0x00
#define _ADC_INTERNAL_VREFH 0x00
#define _ADC_INTERNAL_FVRH1 0x43  // ADPREF=FVR (0x03) + ADFVR=0b01 (0x40)
#define _ADC_INTERNAL_FVRH2 0x83  // ADPREF=FVR (0x03) + ADFVR=0b10 (0x80)

void ADC_Init(void);
void ADC_Init_Advanced(uint8_t cfg);
unsigned int ADC_Get_Sample(uint8_t channel);

#endif // ATU10_XC8_ADC_H
