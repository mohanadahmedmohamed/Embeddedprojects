/*
 * File:   main.c
 * Author: mohanadahmad
 *
 * Created on June 29, 2020, 10:04 PM
 */


#include <xc.h>
#include"MCAL.h"
#include "HAL.h"
#include"config.h"
#include "app.h"
#include <stdint.h>
#include <stdlib.h>

 char system_mode;
 volatile char temp_sensing_flag=0;
 volatile char display_flag=0;
 volatile char buttons_flag=0;
void main() {
    system_init(); // initialize system 
    
    while(1)
    {
 switch(system_mode){
     
 case off    : buttons_task(); //read buttons
               break;
            
 case working_state :
                      if(temp_sensing_flag==1)     // if flag is set sense temp
                      temp_sensing_task();
                     if(buttons_flag==1)
                      buttons_task();   // if flag is set by scheduler begin task
                      display_task();
                     
                      break;
            
 case temp_set:  if (buttons_flag==1)
                 buttons_task();      //if flag is set read button
                 if (display_flag==1)
                 display_task();      // if flag is set display 
                 break;
    
         
}
}
}
