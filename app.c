#include<xc.h>
#include <stdlib.h>
#include"HAL.h"
#include"MCAL.h"
#include "config.h"

int one_sec_display_counter=0;             /** \brief variable to make led blink every second */
char button_state=0;                       /** \brief the buttons task state variable */
char first_time_flag=0;                   /** \ brief flag to determine if this is the first time to use the heater*/
unsigned int temp_setted=0 ;              /** \ brief variable which contains the temp setted by the user*/
unsigned int current_temp;                /** \ brief current temperature of the system */
unsigned char button_pressed =none;     /** \brief current temperature of the system */
char index=0;                             /** \brief index of the readings array */
int readings_arr[10];                      /** \brief array in which last 10 readings are stored */
volatile int display_counter=21;           /** \brief counter to display cycles for display 20*50ms 1 sec */  
int temp_setting_counter=50 ;              /** \brief counter to temp_set exit time 100*50ms 5secs */
char system_mode;                          /** \brief  system mode*/
volatile char temp_sensing_flag=0;          /** \brief  flag to initiate temp_sensing task*/
volatile char display_flag=0;                /** \brief  flag to initiate display task*/
volatile char buttons_flag=0;                 /** \brief  flag to initiate buttons task*/
volatile char heating_or_cooling=cooling;                      /** \brief determine whether system is in heating or                                                                 cooling*/
volatile int buttons_counter=2;             /** \brief counter to set buttons task time 2*50ms 100msecs */
volatile int  temp_sensing_counter=3;        /** \brief counter to set temp_sensing task time 2*50ms 100msecs */




/******************************************************************//**
 * Function: system_init()
 * 
 * /b Description:
 * 
 *initialize the initial state of the system
 * PRE_CONDITION:None
 * 
 * POST_CONDITION: system is initialized
 * @param [void] 
 * 
 * @return [void]
 * \b
                                                                     * 
 *  Example:
 * 
 * @code
 * 
 * system_init()
 * 
 * @endcode
 **************************************************************************/

void  system_init()
    {
        system_mode=off;           //set system in off state initially
        timer1_init();             // initialize timer1
        I2C_Master_Init(100000);   // initialize I2C
        pin_input(up_button,'b');  // initialize push buttons as input
        pin_input(down_button,'b');
        pin_input(power_button,'b');
        first_time_flag=EepromReadByte(2,0); // read the first time flag from eeprom
        if(first_time_flag!= no)
       {
          EepromWriteByte(no,2,0); // if it is the first time set the flag into no for the next time
          EepromWriteByte('6',0,0);  // for first time set the temp initially into 60
          EepromWriteByte('0',1,0);  
        }
    }
    /******************************************************************//**
 * Function: system_on ()
 * 
 * /b Description:
 * 
 *This function is used to  put the system in on state
 * PRE_CONDITION: None
 * 
 * POST_CONDITION: system is in working state
 * @param [void] 
 * 
 * @return void
 * \b
                                                                     * 
 *  Example:
 * 
 * @code
 * 
 * system_on()
 * 
 * @endcode
 **************************************************************************/




    void system_on()
    { unsigned char c[3]={0,0,'\0'};
    system_init();
      system_mode=working_state;     
      pin_output(5,'c');
      pin_output(2,'c');
      c[0]=EepromReadByte(0,0);
      c[1]=EepromReadByte(1,0);
      temp_setted= atoi(c);
      pin_output(0,'e'); 
      seven_segment_init();  
    }
    
    /******************************************************************//**
 * Function: system_off ()
 * 
 * /b Description:
 * 
 *This function is used to  put the system in off state
 * PRE_CONDITION: None
 * 
 * POST_CONDITION: system is in off state
 * @param [void] 
 * 
 * @return void
 * \b
                                                                     * 
 *  Example:
 * 
 * @code
 * 
 * system_off();
 * 
 * @endcode
 **************************************************************************/


    
    void system_off()
    {
       
        PORTC=0;
        PORTA=0;
        pin_clear(0,'e');
        system_mode=off;
        pin_input(2,'e');
        
        
    }
   
    
     
    /******************************************************************//**
 * Function: buttons_task ()
 * 
 * /b Description:
 * 
 *This is the task used to read from the push buttons it consists of two states
 *first one is to detect the press, and the second is to determine the action

 * PRE_CONDITION: system_init()
 * 
 * POST_CONDITION: button pressed is detected and system changes its state
 * @param [void] 
 * 
 * @return void
 * \b
                                                                     * 
 *  Example:
 * 
 * @code
 * 
 * buttons_task();
 * 
 * @endcode
 **************************************************************************/
 
void buttons_task()
{  
    switch(button_state)
    {   case 0 :
         button_pressed= buttons_read();
        if (button_pressed == none)      // if no key is pressed
        { button_state=0;   } 
        
        else
 {button_state=1;}  // if user pressed a button set the state into 1 to decipher it
                  
        buttons_flag=0; // set the flag into zero which will be reset by scheduler
       break;
       
        case 1:  if (button_pressed==power_button)
                  {
                    if(system_mode==off)  
        
                      { 
                        system_on();}     // on the system 
                    else 
                    { 
                         system_off();
                         heating_or_cooling=none; // put a none variable in heating or cooling
                         for(int i =0;i<=9;i++)  // reset last 10 readings
                             readings_arr[i]=0;
                  }    // off the system
            
                      button_state=0;       //return to state zero
                      button_pressed=none;} //reset button to no key
        
                 else if (button_pressed==up_button||button_pressed==down_button)
                 
                {
                   if (system_mode==working_state)
                    {
                       system_mode= temp_set; // user pressed up or down system turns from working state to temp_set
                       button_state=0;      // reset button state into zero
                       button_pressed=none;  // reset button pressed into no key
                       temp_setting_counter=100;  // set the counter into 50 , which means 5 secs
                                                }
        
               else if(system_mode==temp_set)
                  {
                if (button_pressed==up_button)
                { 
                    temp_setted=temp_setted+5; // if the mode is temp set and up pressed inc the temp
                      if(temp_setted>75)   
                      { temp_setted=75;        // max temp is 75
                                         }
                       temp_setting_counter=100;}  // after each press reset the counter to 5 secs again
                
                else{temp_setting_counter=100;
                    temp_setted=temp_setted-5; // min temp is 35 
                    if(temp_setted<35)
                    { temp_setted=35;}
                }
            }
                button_state=0;         //reset the state of task
                button_pressed=none;  // reset button pressed to no key
        }
                buttons_flag=0;      // turn off the task

                break;
    }
}

 
    /******************************************************************//**
 * Function: display_task ()
 * 
 * /b Description:
 * 
 *This is the task used to display temperatures on seven segment
 *

 * PRE_CONDITION: system_init()
 * 
 * POST_CONDITION: temperatures are displayed on seven segments displays
 * @param [void] 
 * 
 * @return void
 * \b
                                                                     * 
 *  Example:
 * 
 * @code
 * 
 * display_task();
 * 
 * @endcode
 **************************************************************************/

void display_task()
{
  
   switch(system_mode)
   { 
       case working_state:       
           
           seven_segment_print_int(current_temp);   // if system is in working state display the temp sensed
              display_flag=0;                      // turn off the task
              

           break;
           
       case temp_set:
           if(one_sec_display_counter<10){         
           seven_segment_print_int(temp_setted);    //if system is in temp setting state print the temp setted 
           one_sec_display_counter++;               // increment the counter until it reaches 10,i.e 1 sec
           }
           else{display_flag=0;                    // turn off the task 
           PORTA=0;                                // disable seven segments
           one_sec_display_counter=0;}             // reset counter
           break;
   }
      
    
    
}


    /******************************************************************//**
 * Function: temp_sensing_task ()
 * 
 * /b Description:
 * 
 *This is the task used to sense the temperature and control the heating and cooling element
 *

 * PRE_CONDITION: system_init(), system_mode = working_state
 * 
 * POST_CONDITION: heating or cooling element is on
 * @param [void] 
 * 
 * @return void
 * \b
                                                                     * 
 *  Example:
 * 
 * @code
 * 
 * temp_sensing_task();
 * 
 * @endcode
 **************************************************************************/


void temp_sensing_task()
{ int sum=0,average;  // variables to save the sum and average

    current_temp=( ADC_read_channel(2)*500)/1024 ; // read temperature from adc channel 2
    readings_arr[index]=current_temp;              //save the temperature in last index of array
    if(index==9) index=0;                           // if index reaches 10th place move to first if not increment
    else index++;                                  
    for(int i=0;i<=9;i++)
    {
        sum=sum+readings_arr[i];                   // loop to calculate the sum of last 10 readings
    }
    average= (int)sum/10;                           // calculate the average
    if (average > (temp_setted+5)) {
        pin_clear(5,'c');                           // turn off  the heating element
        pin_set(2,'c');                             // turn on the cooling element
        heating_or_cooling=cooling;                 // specify system_state as cooling
                pin_set(0,'e');                    // turn on the relay lamp (steady for cooling)

    }
    else if(average<(temp_setted-5)) {
     pin_clear(2,'c');                             // turn off the cooling element
        pin_set(5,'c');                            // turn on the heating element
        heating_or_cooling=heating;                // specify system state as heating
    }
    temp_sensing_flag=0;                           // turn off the task 
}



    /******************************************************************//**
 * Function: timer_isr ()
 * 
 * /b Description:
 * 
 *This is interrupt service routine used here to create a simple scheduler based on overflow
* interrupt working as system tick
 *

 * PRE_CONDITION: timer1_init()
 * 
 * POST_CONDITION: system operates based on ticks and flags
 * @param [void] 
 * 
 * @return void
 * 
                                                                     * 
 * 
 * 

 **************************************************************************/


void interrupt timer_isr()
{
    if(PIR1&(1<<0)){    // the interrupt flag of timer 1
      
        if(temp_setting_counter==0&&system_mode==temp_set)
        {
            temp_setting_counter=100;            // reset counter into 5  secs
            system_mode=working_state;                          // if 5 secs passed set the system into working state
            EepromWriteByte((temp_setted/10)+'0',0,0);           // write the temp setted by user into Eeprom
                EepromWriteByte((temp_setted%10)+'0',1,0);
        }
        else if(temp_setting_counter!=0&&system_mode==temp_set) {temp_setting_counter--;}
        
        if(display_counter==0)         //display counter reached zero, which means 1 sec has passed
        {
            display_counter=20;       // reset counter to 1 sec
            if(heating_or_cooling==heating)   
            {PORTE=~PORTE;}                   // if system is heating toggle the relay lamp
            display_flag=1;                // turn on the display task 
        }
        else
            display_counter--;              // decrement counter until 1 sec ends
        
        if(temp_sensing_counter==0)
        { temp_sensing_flag=1; 
        temp_sensing_counter=2;} 
        else{temp_sensing_counter--;}// turn on temp_sensing_flag every 100 ms
        
        if(buttons_counter==0)
        {buttons_counter=2;
        buttons_flag=1;}
        else{buttons_counter--;}                    // turn on buttons_flag every 100 ms
         PIR1&=~(1<<0);                    // reset interrupt flag
         TMR1=53036;                        // reset timer 1 to create 50ms again
    }
    
}