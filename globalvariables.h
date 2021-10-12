/* 
 * File:   globalvariables.h
 * Author: mohanadahmad
 *
 * Created on July 9, 2020, 1:27 AM
 */
#include "config.h"

#ifndef GLOBALVARIABLES_H
#define	GLOBALVARIABLES_H

 volatile int display_counter=10;
 int temp_setting_counter=500;
 char system_mode=temp_set;
 volatile char temp_sensing_flag=0;
 volatile char display_flag=0;
 volatile char buttons_flag=0;
 volatile char heating=0;


#endif	/* GLOBALVARIABLES_H */

