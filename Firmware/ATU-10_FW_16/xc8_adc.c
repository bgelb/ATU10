#include "xc8_adc.h"

// Lightweight ADC init/sample routines replacing mikroC's ADC library calls.

static void adc_apply_vref(uint8_t cfg){
   ADREFbits.ADNREF = 0; // Vss
   if(cfg & _ADC_INTERNAL_VREFH){
      ADREFbits.ADPREF = 0; // Vdd
      FVRCONbits.FVREN = 0;
      return;
   }
   FVRCONbits.FVREN = 1;
   if(cfg & _ADC_INTERNAL_FVRH2)
      FVRCONbits.ADFVR = 1; // 2x (2.048V)
   else
      FVRCONbits.ADFVR = 0; // 1x (1.024V)
   while(!FVRCONbits.FVRRDY);
   ADREFbits.ADPREF = 2; // FVR as positive reference
}

void ADC_Init(void){
   ADC_Init_Advanced(_ADC_INTERNAL_VREFL | _ADC_INTERNAL_FVRH1);
}

void ADC_Init_Advanced(uint8_t cfg){
   ADCON0bits.ADON = 0;
   adc_apply_vref(cfg);
   ADCLK = 3;        // Fosc/8 for TAD
   ADACQ = 10;       // Acquisition delay
   ADPCH = 0x3F;     // No channel selected
   ADCON0bits.ADFM = 1;  // Right-justified
   ADCON0bits.ADON = 1;
}

unsigned int ADC_Get_Sample(uint8_t channel){
   ADPCH = channel;
   __delay_us(5);
   ADGO = 1;
   while(ADGO);
   return ADRES;
}

