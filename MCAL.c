/****************************************************************//*
* 
* @Title : MCAL ( microcontroller abstraction layer)
* @Filename : MCAL.C
* @Author : Mohanad Ahmad
* @Origin Date : 7/9/2020
* @Version : 1.0.0
* @Compiler : MPLAB v3.55
* @Target : PIC16F877a
* @Notes : None
*
*
******************************************************************/
/** @file file.h
 * A brief file description.
 * A more elaborated file description.
 */
#include <xc.h> 
#include "config.h"
/*!Defines the system clock as 8MHZ */
#define _XTAL_FREQ 8000000


/******************************************************************//*
 * Function: pin_output()
 * 
 * /b Description:
 * 
 * This function is used to set a pin as an output pin 
 * PRE_CONDITION: none
 * 
 * POST_CONDITION: Dio pin is initialized
 * @param [in] the no of the pin in the port
 * @param [in] the letter of the port
 * 
 * @return void
 * \b
 *  Example:
 * 
 * @code
 * 
 * pin_output(1,'a');
 * 
 * @endcode
 **************************************************************************/

void pin_output(char pin, char PORT)
{ if (PORT=='A'||PORT=='a')
    TRISA&=~(1<<pin);
    else if (PORT=='B'||PORT=='b')
    TRISB&=~(1<<pin);
    else if (PORT=='C'||PORT=='c')
    TRISC&=~(1<<pin);
     else if (PORT=='D'||PORT=='d')
    TRISD&=~(1<<pin);
     else if (PORT=='E'||PORT=='e')
    TRISE&=~(1<<pin);
    }
/******************************************************************//**
 * Function: pin_input()
 * 
 * /b Description:
 * 
 * This function is used to set a pin as an input pin 
 * PRE_CONDITION: none
 * 
 * POST_CONDITION: Dio pin is initialized as an input pin
 * @param  the no of the pin in the port
 * @param  the letter of the port
 * 
 * @return void
 * 
 * \b 
 * 
 * Example:
 * @code
 * 
 * pin_input(1,'a');
 * 
 * @endcode
 * *************************************************************************/
void pin_input (char pin , char PORT)
{
    if (PORT=='A'||PORT=='a')
    TRISA|=(1<<pin);
    else if (PORT=='B'||PORT=='b')
    TRISB|=(1<<pin);
    else if (PORT=='C'||PORT=='c')
    TRISC|=(1<<pin);
     else if (PORT=='D'||PORT=='d')
    TRISD|=(1<<pin);
     else if (PORT=='E'||PORT=='e')
    TRISE|=(1<<pin);
    }   

/******************************************************************//*
 * Function: port_input()
 * 
 * /b Description:
 * 
 * This function is used to set a whole port as input 
 * PRE_CONDITION: none
 * 
 * POST_CONDITION: Dio port is initialized as input 
 * @param [in]  the port letter
 * 
 * @return void
 * \b
 *  Example:
 * @code
 * port_input('a');
 * 
 * @endcode
 * *************************************************************************/
void port_input (char PORT)
{
    if (PORT=='A'||PORT=='a')
    TRISA=255;
    else if (PORT=='B'||PORT=='b')
    TRISB=255;
    else if (PORT=='C'||PORT=='c')
    TRISC=255;
     else if (PORT=='D'||PORT=='d')
   TRISD=255;}
    
    /******************************************************************//*
 * Function: port_output()
 *
 * /b Description:
 * 
 * This function is used to set a whole port as output 
 * PRE_CONDITION: none
 * 
 * POST_CONDITION: Dio port is initialized as output 
 * @param [in]  the port letter
 * 
 * @return void
 * \b 
 * Example:
 * @code
 * port_output('a');
 * 
 * @endcode
 * *************************************************************************/
    
    void port_output ( char PORT)
{
    if (PORT=='A'||PORT=='a')
    TRISA=0;
    else if (PORT=='B'||PORT=='b')
    TRISB=0;
    else if (PORT=='C'||PORT=='c')
    TRISC=0;
     else if (PORT=='D'||PORT=='d')
   TRISD=0;}
    /******************************************************************//**
 * Function: pin_set()
 * 
 * /b Description:
 * 
 * This function is used to set a digital pin as a high 
 * 
 * PRE_CONDITION: pin_output()
 * 
 * POST_CONDITION: Dio port is initialized as output 
 * @param [in]  the port letter
 * @param [in]  the pin number
 * @return void
 * \b
 *  Example:
 * @code
 * pin_set(1,'a')
 * 
 * @endcode
 *@see pin_output()
 * *************************************************************************/
    void pin_set ( char pin , char PORT)
    {if (PORT=='A'||PORT=='a')
   PORTA|=(1<<pin);                 
    else if (PORT=='B'||PORT=='b')
    PORTB|=(1<<pin);
    else if (PORT=='C'||PORT=='c')
    PORTC|=(1<<pin);
     else if (PORT=='D'||PORT=='d')
    PORTD|=(1<<pin);
     else if (PORT=='E'||PORT=='e')
    PORTE|=(1<<pin);
        
}
     /******************************************************************//**
 * Function: pin_clear()
 * 
 * /b Description:
 * 
 * This function is used to set a digital pin as a low 
 * 
 * PRE_CONDITION: pin_output()
 * 
 * POST_CONDITION: Dio port is initialized as output 
 * @param [in]  the port letter
 * @param [in]  the pin number
 * @return void
 * \b 
 * Example:
 * @code
 * pin_clear(1,'a')
 * 
 * @endcode
 *@see pin_output()
 * *************************************************************************/
    void pin_clear(char pin , char PORT)
    {
if (PORT=='A'||PORT=='a')
    PORTA&=~(1<<pin);
    else if (PORT=='B'||PORT=='b')
    PORTB&=~(1<<pin);
    else if (PORT=='C'||PORT=='c')
    PORTC&=~(1<<pin);
     else if (PORT=='D'||PORT=='d')
    PORTD&=~(1<<pin);
     else if (PORT=='E'||PORT=='e')
    PORTE&=~(1<<pin);
    }
    
     /******************************************************************//**
 * Function: port_set()
 * 
 * /b Description:
 * 
 * This function is used to set a digital port as a high 
 * 
 * PRE_CONDITION: port_output()
 * 
 * POST_CONDITION: Dio port is initialized as output 
 * @param [in]  the port letter
 * 
 * @return void
 * \b 
 * Example:
 * @code
 * port_set(1,'a')
 * 
 * @endcode
 * 
 *@see port_output()
 * *************************************************************************/
    void port_set ( char PORT)
    {
        
    if (PORT=='A'||PORT=='a')
    PORTA=255;
    else if (PORT=='B'||PORT=='b')
    PORTB=255;
    else if (PORT=='C'||PORT=='c')
    PORTC=255;
     else if (PORT=='D'||PORT=='d')
   PORTD=255;
        
     }
    
        /******************************************************************//**
 * Function: port_clear()
 * 
 * /b Description:
 * 
 * This function is used to set a digital port as a low
 * 
 * PRE_CONDITION: port_output()
 * 
 * POST_CONDITION: Dio port is initialized as output 
 * @param [in]  the port letter
 * 
 * @return void
 * \b 
 * Example:
 * @code
 * port_clear(1,'a')
 * 
 * @endcode
 *@see port_output()
 * *************************************************************************/
    void port_clear (  char PORT)
    {
         if (PORT=='A'||PORT=='a')
    PORTA=0;
    else if (PORT=='B'||PORT=='b')
    PORTB=0;
    else if (PORT=='C'||PORT=='c')
    PORTC=0;
     else if (PORT=='D'||PORT=='d')
   PORTD=0;
          
    }
    
    
           /******************************************************************//**
 * Function: timer1_init()
 * 
 * /b Description:
 * 
 * This function is used to set timer1 to initiate an interrupt every 50 ms which is the
 * tick of the system.
 * 
 *The external clock (FOSC)is 8MHZ ,prescaler=8
 * 
 * CLOCK= ((FOSC)/4)/8
 * initial count of timer1=53036
 * SYSTEM TICK= ( 1/CLOCK)*(2^16)-53036= 50ms 
 * 
 * PRE_CONDITION: NONE
 * 
 * POST_CONDITION: system tick is initialized into 100ms 
 * 
 * @param [in]  void
 * 
 * @return void
 * \b 
 * Example:
 * @code
 * 
 * port_clear(1,'a')
 * 
 * @endcode
 *@see port_output()
 * *************************************************************************/
  
     void timer1_init()
    {
       //frequency clock is 8 mhz 
        T1CON|=(1<<5)|(1<<4);// set prescaler to 8 
        TMR1=53036; // use
        PIE1=(1<<0);//timer1 interrupt enable
        INTCON=(1<<7)|(1<<6); //global peripheral interrupt enable
       T1CON|=(1<<0);//enable timer1 
    }
     
     
        /******************************************************************//**
 * Function: ADC_read_channel()
 * 
 * /b Description:
 * 
 * This function is used to initialize ADC peripheral and read from a certain channel
 * 
 * PRE_CONDITION: NONE
 * 
 * POST_CONDITION: ADC reading returned 
 * 
 * @param [in]  no of channel
 * 
 * @return unsigned long int Adc reading
 * \b 
 * Example:
 * @code
 * 
 * ADC_read_channel(2);
 * 
 * @endcode
 *
 * *************************************************************************/
  
   unsigned long int  ADC_read_channel( char channel ) 
    { int result;
    if (channel== 0)
    { ADCON0=(1<<0) ;          // initialize the adc channel
         ADCON1=0b10001110;    // set adc pins into analog mode
    TRISA|=(1<<0);}             // set the channel pin as input
    else if (channel==1){
    
        ADCON0=(1<<0)|(1<<3);   // initialize the adc channel
        ADCON1=0b10001101;      // set adc pins into analog mode
        TRISA|=(1<<1);           // set the channel pin as input
    
    }
    else if(channel==2)
    {
     ADCON0=(1<<0)|(1<<4);         // initialize the adc channel
        ADCON1=0b10000001;         // set adc pins into analog mode
        TRISA|=(1<<2);             // set the channel pin as input
    }
    
         ADCON0|=(1<<2);          // start Adc conversion
         while(ADCON0&(1<<2));    // wait for conversion
         result=(ADRESH<<8)+( ADRESL);  
         return result;       //return result
    }
   
      /******************************************************************//**
 * Function: I2C_Master_Init()
 * 
 * /b Description:
 * 
 * This function is used to initialize the microcontroller into master mode 
 *in I2C communication
 * 
 * 
 * PRE_CONDITION: NONE
 * 
 * POST_CONDITION: Microcontroller is set into a master in I2C communication
 * 
 * @param [in] Baudrate
 * 
 * @return void
 * \b 
 * Example:
 * @code
 * 
 *  I2C_Master_Init(100000) 

 * 
 * @endcode
 *
 * *************************************************************************/
  
   
   void I2C_Master_Init(const unsigned long c)
{ 
    SSPCON = 0b00101000; // set enable bit sspen ,SSMP3_SSMP0 into master mode 1000
    SSPCON2 = 0;        //  set all register to 0
    SSPADD = (_XTAL_FREQ/(4*c))-1; //baudrate register
    SSPSTAT = 0;                   
    TRISC3 = 1;     //initialize pins 
    TRISC4 = 1;     // initialize pins
}
   
   
/******************************************************************//**
 * Function: I2C_Master_Wait()
 * 
 * /b Description:
 * 
 * This function is used to delay the microcontroller to make sure there is no current
 * data transfer
 * 
 * PRE_CONDITION: I2C_Master_Init()
 * 
 * POST_CONDITION: wait until current communication is done
 * 
 * @param [in] void
 * 
 * @return void
 * \b 
 * Example:
 * @code
 * 
 *  I2C_Master_Wait()

 * 
 * @endcode
 *
 * *************************************************************************/
void I2C_Master_Wait()
{
    while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));   // wait for current comm
}

/******************************************************************//**
 * Function: I2C_Master_Start()
 * 
 * /b Description:
 * 
 * This function is used to send a start bit on the I2c bus
 * 
 * 
 * PRE_CONDITION: I2C_Master_init( ) , I2C_Master_ Wait() to make sure bus is not busy
 * 
 * POST_CONDITION: start bit is sent on the bus
 * 
 * @param [in] void
 * 
 * @return void
 * \b 
 * Example:
 * @code
 * 
 * I2C_Master_Start()

 * 
 * @endcode
 *
 * *************************************************************************/
void I2C_Master_Start()
{
    I2C_Master_Wait();  
    SEN = 1; // send start bit
}


/******************************************************************//**
 * Function: I2C_Master_RepeatedStart()
 * 
 * /b Description:
 * 
 * This function is used to send a repeated start bit on the I2c bus  in order
 *to initiate a new transfer without releasing the bus 
 * 
 * PRE_CONDITION: I2C_Master_Start( ) , I2C_Master_ Wait() to make sure bus is not busy
 * 
 * POST_CONDITION: start bit is sent on the bus
 * 
 * @param [in] void
 * 
 * @return void
 * \b 
 * Example:
 * @code
 * 
 * I2C_Master_RepeatedStart()

 * 
 * @endcode
 *
 * *************************************************************************/

void I2C_Master_RepeatedStart()
{
    I2C_Master_Wait();
    RSEN = 1;  // send repeated start
}

/******************************************************************//**
 * Function: I2C_Master_Stop()
 * 
 * /b Description:
 * 
 * This function is used to send a stop bit on the I2c bus
 * 
 * 
 * PRE_CONDITION: I2C_Master_Start( ) , I2C_Master_ Wait() to make sure bus is not busy
 * 
 * POST_CONDITION: stop bit is sent on the bus
 * 
 * @param [in] void
 * 
 * @return void
 * \b 
 * Example:
 * @code
 * 
 * I2C_Master_Stop()

 * 
 * @endcode
 *
 * *************************************************************************/
void I2C_Master_Stop()
{
    I2C_Master_Wait();
    PEN = 1;  // send stop bit
}

/******************************************************************//**
 * Function: I2C_Master_Write()
 * 
 * /b Description:
 * 
 * This function is used to send a byte over the bus
 * 
 * 
 * PRE_CONDITION: I2C_Master_Start( ) , I2C_Master_ Wait() to make sure bus is not busy
 * 
 * POST_CONDITION:data is sent over the bus
 * 
 * @param [in] unsigned char data
 * 
 * @return void
 * \b 
 * Example:
 * @code
 * 
 * I2C_Master_Write(0xA0);

 * 
 * @endcode
 *
 * *************************************************************************/
void I2C_Master_Write(unsigned  d)
{
    I2C_Master_Wait();
    SSPBUF = d;  // write data to buffer register
} 

/******************************************************************//**
 * Function: I2C_Master_Read()
 * 
 * /b Description:
 * 
 * This function is used to receive data from the bus
 * 
 * 
 * PRE_CONDITION: I2C_Master_ Wait() to make sure bus is not busy
 * 
 * POST_CONDITION: data is received 
 * 
 * @param [in] void
 * 
 * @return unsigned char data
 * \b 
 * Example:
 * @code
 * 
 * data= I2C_Master_Read()

 * 
 * @endcode
 *
 * *************************************************************************/
unsigned short I2C_Master_Read(unsigned short a)
{
    unsigned char temp;
    I2C_Master_Wait();
    RCEN = 1;  // enable receive
    I2C_Master_Wait();
    temp = SSPBUF; //  read data from buffer
    I2C_Master_Wait();
    ACKDT = (a)?0:1;    // ACK or NACK
    ACKEN = 1;
    
    
    return temp;
}