#ifndef ATU10_MAIN_H
#define ATU10_MAIN_H


#include "pic_init.h"

void pic_init(void);
void Btn_long(void);
void Btn_short(void);
void Btn_xlong(void);
void check_reset_flags(void);
void Voltage_show(void);
void Relay_set(char, char, char);
int get_reverse(void);
int get_forward(void);
void get_pwr(void);
void get_swr(void);
void get_batt(void);
void watch_swr(void);
void coarse_cap(void);
void tune(void);
void subtune(void);
void coarse_tune(void);
void coarse_cap(void);
void coarse_ind(void);
void coarse_ind_cap(void);
void sharp_tune(void);
void sharp_cap(void);
void sharp_ind(void);
void atu_reset(void);
void draw_swr(unsigned int);
void draw_power(unsigned int);
float sqrt_n(float);
void oled_start(void);
void power_off(void);
void Greating(void);
void Ext_long(void);
void cells_reading(void);

int IntToStr(int value, char *out);
unsigned char Bcd2Dec(unsigned char bcd);
void ADC_Init(void);
void ADC_Init_Advanced(unsigned char cfg);
unsigned int ADC_Get_Sample(unsigned char channel);

#define ON 1
#define OFF 0
#define Battery_input 9
#define FWD_input 8
#define REV_input 10
#define Key_out LATDbits.LATD2
#define Key_in PORTDbits.RD2
#define Start_out LATDbits.LATD1
#define Start (!PORTDbits.RD1)

#endif // ATU10_MAIN_H
