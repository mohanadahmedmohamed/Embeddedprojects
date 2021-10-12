  
#ifndef config_H
#define	config_H

#define seven_segment_enable_port 'A'
#define seven_segment_data_port 'd'
#define seven_segment1 2
#define seven_segment2 3
#define seven_segment3 4
#define seven_segment4 5
#define off 1
#define temp_set 2
#define working_state 3
#define none 'i'
#define up_button 2
#define down_button 1
#define power_button 0
#define up_button_pressed !(PORTB&(1<<2))
#define down_button_pressed !(PORTB&(1<<1))
#define power_button_pressed !(PORTB&(1<<0))
#define heating 1
#define cooling 0
#define no 'n'


#endif	/* XC_HEADER_TEMPLATE_H */

