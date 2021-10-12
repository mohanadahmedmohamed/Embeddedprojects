/* 
 * File:   app.h
 * Author: mohanadahmad
 *
 * Created on July 7, 2020, 6:01 PM
 */

#ifndef APP_H
#define	APP_H


void buttons_task();
void display_task();
unsigned char buttons_read();
void temp_sensing_task();
void interrupt timer_isr();
    void system_on();
        void system_off();
         void system_init();




#endif	/* APP_H */

