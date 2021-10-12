
#ifndef HAL_H
#define	HAL_H
#include <xc.h> 
#include"MCAL.h"


void seven_segment_init();
void seven_segment_print (char sevensegmentno, char variable);
void seven_segment_print_int(int number);
void EepromWriteByte(unsigned char Data,unsigned char Address , unsigned char Page);
unsigned char EepromReadByte(unsigned char Address , unsigned char Page);
unsigned char buttons_read();




#endif