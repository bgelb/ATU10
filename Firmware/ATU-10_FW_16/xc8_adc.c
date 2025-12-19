#include "xc8_adc.h"
#include "xc8_compat.h" // for _XTAL_FREQ and __delay_us

// ADC init/sample routines matching mikroC's __Lib_ADC_18xxx.c behavior for PIC16LF18877.

void ADC_Init(void){
   ADC_Init_Advanced(_ADC_INTERNAL_VREFL | _ADC_INTERNAL_FVRH1);
}

void ADC_Init_Advanced(uint8_t reference){
   // mikroC clears these registers on each init.
   ADCON0 = 0;
   ADCON1 = 0;
   ADCON2 = 0;
   ADCON3 = 0;

   // Configure references (ADREF: ADPREF<1:0>, ADNREF).
   ADREF &= 0xEC;
   ADREF |= (reference & 0x13);

   // Configure the ADC Fixed Voltage Reference (FVRCON.ADFVR) when requested.
   if(reference & 0xC0){
      FVRCON = (uint8_t)((FVRCON & 0xFC) | ((reference & 0xC0) >> 6));
      FVRCONbits.FVREN = 1;
      while(!FVRCONbits.FVRRDY);
   } else {
      FVRCON &= 0xFC;
   }

   // mikroC sets ADCS=1 and ADFM0=1 (ADFM=0b01), then enables ADC.
   ADCON0bits.ADCS = 1;
   ADCON0bits.ADFM = 1;
   ADCON0bits.ADON = 1;
}

unsigned int ADC_Get_Sample(uint8_t channel){
   ADPCH = (uint8_t)(channel & 0x3F);
   __delay_us(22);
   ADGO = 1;
   while(ADGO);
   return ADRES;
}

