
#include <xc.h>
#include"MCAL.h"
#include"config.h"
#include "HAL.h"


/******************************************************************//**
 * Function: seven_segment_init()
 * 
 * /b Description:
 * 
 *This function is used to initialize dio pins of seven segment 
 * PRE_CONDITION: none
 * 
 * POST_CONDITION: Dio pins of seven segment is set as an output
 * @param [void] 
 * 
 * @return void
 * \b
                                                                     * 
 *  Example:
 * 
 * @code
 * 
 * seven_segment_init();
 * 
 * @endcode
 **************************************************************************/


void seven_segment_init() {
//set enable pins of seven segments as output
 
    pin_output(seven_segment1, seven_segment_enable_port);
    pin_output(seven_segment2, seven_segment_enable_port);
    pin_output(seven_segment3, seven_segment_enable_port);
    port_output(seven_segment_data_port);//set seven_segment data port as output

}
/******************************************************************//**
 * Function: seven_segment_print()
 * 
 * /b Description:
 * 
 *This function is used to print a number on a seven segment 
*
 * PRE_CONDITION: seven_segment_init()
 * 
 * POST_CONDITION: a no. is displayed on seven segment
 * @param [char] sevensegmentno 
 *  @param [char] variable
*
 * @return void
 * \b
                                                                     * 
 *  Example:
 * 
 * @code
 * 
 * seven_segment_print(sevensegment2,'2');
 * 
 * @endcode
 **************************************************************************/

void seven_segment_print(char sevensegmentno, char variable) {
    port_clear(seven_segment_enable_port);
    pin_set(sevensegmentno, seven_segment_enable_port);//set enable pin

    if (variable == '0')      PORTD = 0b00111111;
    else if (variable == '1') PORTD = 0b00000110;
    else if (variable == '2') PORTD = 0b01011011;
    else if (variable == '3') PORTD = 0b01001111;
    else if (variable == '4') PORTD = 0b01100110;
    else if (variable == '5') PORTD = 0b01101101;
    else if (variable == '6') PORTD = 0b01111101;
    else if (variable == '7') PORTD = 0b00000111;
    else if (variable == '8') PORTD = 0b01111111;
    else if (variable == '9') PORTD = 0b01101111;
    

}

/******************************************************************//**
 * Function: seven_segment_print_int()
 * 
 * /b Description:
 * 
 *This function is used to print an integer number on a two seven segments
 * PRE_CONDITION: seven_segment_init()
 * 
 * POST_CONDITION: an integer number is printed on both seven segments
 * @param [void] 
 * 
 * @return void
 * \b
                                                                     * 
 *  Example:
 * 
 * @code 
 * 
 * seven_segment_print_int(15);
 * 
 * @endcode
 **************************************************************************/
void seven_segment_print_int(int number)
{
  seven_segment_print(seven_segment2,(number/10)+'0');//print first digit of number
      __delay_ms(10);
       seven_segment_print(seven_segment3,(number%10)+'0'); //print second digit of number
       __delay_ms(10);   
    
    
}
/******************************************************************//**
 * Function: EepromWriteByte()
 * 
 * /b Description:
 * 
 *This function is used to write a byte to EEprom
 * PRE_CONDITION: I2C_Master_init(), I2C_Master_Start()
 * 
 * POST_CONDITION: a byte is written in EEprom
 * @param [unsigned char] Data 
 * @param [unsigned char] Address
 *@param [unsigned char] Page
 *
 * @return void
 * \b
                                                                     * 
 *  Example:
 * 
 * @code
 * 
 * EepromWriteByte('c',2,3);
 * 
 * @endcode
 **************************************************************************/


void EepromWriteByte(unsigned char Data,unsigned char Address , unsigned char Page)
{
    I2C_Master_Start();          //send start bit
    I2C_Master_Write(0xA0|(Page<<1)); //wait if bus is busy
        I2C_Master_Write(Address); // send addrres to EEprom
            I2C_Master_Write(Data); // send data 
            I2C_Master_Stop();       // send stop bit

}

/******************************************************************//**
 * Function: EepromReadByte()
 * 
 * /b Description:
 * 
 *This function is used to read a byte from EEprom
 * PRE_CONDITION: I2C_Master_init(),I2C_Master_Start()
 * 
 * POST_CONDITION: byte is read from EEprom
 * @param [unsigned char]  Address
 *@param [unsigned char]  Page
 * 
 * @return unsigned char 
 * \b
                                                                     * 
 *  Example:
 * 
 * @code
 * 
 * data=EepromReadByte(3,1);
 * 
 * @endcode
 **************************************************************************/


unsigned char EepromReadByte(unsigned char Address , unsigned char Page)
{

    unsigned char data;
    I2C_Master_Start();     // send start bit
I2C_Master_Write(0xA0|(Page<<1));   //send address
        I2C_Master_Write(Address);  
        I2C_Master_RepeatedStart();   // resend start to restart transmission without releasing bus
        I2C_Master_Write(0xA1|Page>>1); 
        data = I2C_Master_Read(0);// store data in variable
        I2C_Master_Stop();   // send stop bit
        return data;
}

/******************************************************************//**
 * Function: buttons_Read()
 * 
 * /b Description:
 * 
 *This function is used to read push buttons pressed by user
 * PRE_CONDITION: port_input()
 * 
 * POST_CONDITION: push button is detected
 * @param [void] 
 * 
 * @return unsigned char
 * \b
                                                                     * 
 *  Example:
 * 
 * @code
 * 
 * button_pressed= buttons_read();
 * 
 * @endcode
 **************************************************************************/

unsigned char buttons_read()
{
    
    if (power_button_pressed){
    while(power_button_pressed); //for debounce
    return power_button ;}
    else if (up_button_pressed){
    while(up_button_pressed);  // for debounce

    return up_button ;}
    else if (down_button_pressed){
    while(down_button_pressed);    // for debounce
    return down_button ;} 
    
    else return none; // if no key pressed return no key
    
}