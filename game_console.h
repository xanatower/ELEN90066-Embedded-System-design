/*************************************************************************
Title:    Game Console Template Header File
Inital Author:   David Jahshan
Extended by : (PUT YOUR NAME HERE) (PUT YOUR STUDENT NUMBER HERE) 
Software: AVR-GCC 
Hardware: ATMEGA16 @ 8Mhz 

DESCRIPTION:
	Macros for Game Console

*************************************************************************/

#include <avr/io.h> 
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/delay.h>

#define byte unsigned char

//#define F_CPU = 7379300L


/*ON OFF*/

#define ON 0xFF
#define OFF 0x00
#define HIGH 0xFF
#define LOW 0x00
#define IN 0x00
#define OUT 0xFF
#define ALL 0xFF
#define TRUE 1
#define FALSE 0
#define FORWARD 0x00
#define BACK 0xFF 
#define BOTTOM 0x00
#define TOP 0xFF



#define CMD 0x00
#define DAT 0xFF

/*SET and GET MACRO*/

#define SET(PORT,MASK,VALUE) PORT = ((MASK & VALUE) | (PORT & ~MASK))
#define GET(PORT,MASK) PORT & MASK

//Devices Direction MACROs
//#define MULTI_LINES_DIR(DIR) SET(DDR?,(_BV(P?#)|_BV(P?#)|_BV(P?#)),DIR)
#define BAT_LOW_LED_DIR(DIR) SET(DDRA,_BV(PA1),DIR)

//buttons DIRections
#define UP_BUTTON_DIR(DIR) SET(DDRA,_BV(PA2),DIR)
#define DOWN_BUTTON_DIR(DIR) SET(DDRA,_BV(PA3),DIR)
#define LEFT_BUTTON_DIR(DIR) SET(DDRA,_BV(PA4),DIR)
#define RIGHT_BUTTON_DIR(DIR) SET(DDRA,_BV(PA5),DIR)
#define A_BUTTON_DIR(DIR) SET(DDRA,_BV(PA6),DIR)
#define B_BUTTON_DIR(DIR) SET(DDRA,_BV(PA7),DIR)

//button outputs
//button pull up after 
#define UP_BUTTON_PULL(STATE) SET(PORTA,_BV(PA2), STATE) //active high
#define DOWN_BUTTON_PULL(STATE) SET(PORTA,_BV(PA3), STATE)
#define LEFT_BUTTON_PULL(STATE) SET(PORTA,_BV(PA4), STATE)
#define RIGHT_BUTTON_PULL(STATE) SET(PORTA,_BV(PA5), STATE)

#define A_BUTTON_PULL(STATE) SET(PORTA,_BV(PA6), STATE)
#define B_BUTTON_PULL(STATE) SET(PORTA,_BV(PA7), STATE)


//Devices(button) Inputs
#define UP_BUTTON ~GET(PINA,_BV(PA2))
#define DOWN_BUTTON ~GET(PINA,_BV(PA3))
#define LEFT_BUTTON ~GET(PINA,_BV(PA4))
#define RIGHT_BUTTON ~GET(PINA,_BV(PA5))
#define A_BUTTON ~GET(PINA,_BV(PA6))
#define B_BUTTON ~GET(PINA,_BV(PA7))



//LCD
#define LCD_BACKLIGHT_DIR(DIR) SET(DDRB,_BV(PB3),DIR)

//Devices Outputs
///#define MULTI_LINES(STATE) SET(DDR?,(_BV(P?#)|_BV(P?#)|_BV(P?#)),DIR)

#define BAT_LOW_LED(STATE) SET(PORTA,_BV(PA1),~STATE)
#define LCD_BACKLIGHT(STATE) SET(PORTB,_BV(PB3), STATE)

//LCD and SPI stuffs
#define LCD_CS_DIR(DIR) SET(DDRD,_BV(PD3),DIR)
#define LCD_CD_DIR(DIR) SET(DDRD,_BV(PD5),DIR)
#define LCD_RST_DIR(DIR) SET(DDRD,_BV(PD4),DIR)

#define LCD_CS(STATE) SET(PORTD,_BV(PD3), ~STATE)
#define LCD_CD(STATE) SET(PORTD,_BV(PD5), STATE)
#define LCD_RST(STATE) SET(PORTD,_BV(PD4), ~STATE)


//MOSI MISO SCK, Only to set output direction
#define MOSI_DIR(DIR) SET(DDRB,_BV(PB5),DIR)
#define MISO_DIR(DIR) SET(DDRB,_BV(PB6),DIR)
#define SCK_DIR(DIR) SET(DDRB,_BV(PB7),DIR)
#define PB4_DIR(DIR) SET(DDRB,_BV(PB4),DIR)







