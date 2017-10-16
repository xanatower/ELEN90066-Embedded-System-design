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

#define MAX_PAGE 8
#define MAX_COLUMN 132

#define CMD 0x00
#define DAT 0xFF

#define CMD_PAGE 0xB0
#define MAX_PAGE 8
#define MIN_PAGE 1

#define BUFFER_ROW 8
#define BUFFER_COL 102

#define MAX_COLUMNS 132
#define MAX_PAGES 8
#define MAX_ROWS 64
#define MIN_ROWS 0

#define COL_OFFSET 30

#define CMD_COL_LSB 0x00 //page 5 of data sheet
#define CMD_COL_MSB 0x10 //page 5 of data sheet
#define P_LSB 0x0F
#define SHIFT2MSB 4
#define CLEAR 0x00

//LCD INITIALISATION

#define DISPLAY_ST 0x40
#define SEG_REVERSE 0xA0
#define NORMAL_COM 0xC8
#define DIS_PIXELS_ON 0xA4
#define DIS_INVERSE_OFF 0xA6
#define LCD_BIAS_RATIO 0xA2
#define POWER_CONTROL 0x2F
#define LCD_RESISTOR_RATIO 0x27
#define SET_ELECTRONIC_VOLUME1 0x81
#define SET_ELECTRONIC_VOLUME2 0x10
#define SET_ADVANCED_PROGRAM_CONTROL0 0xFA
#define SET_ADVANCED_PROGRAM_CONTROL1 0x90
#define DISPLAY_ON 0xAF

/*SET and GET MACRO*/

#define SET(PORT, MASK, VALUE) PORT = ((MASK & VALUE) | (PORT & ~MASK))
#define GET(PORT, MASK) PORT &MASK

//Devices Direction MACROs
//#define MULTI_LINES_DIR(DIR) SET(DDR?,(_BV(P?#)|_BV(P?#)|_BV(P?#)),DIR)

#define BAT_LOW_LED_DIR(DIR) SET(DDRA, _BV(PA1), DIR)

//buttons DIRections
#define UP_BUTTON_DIR(DIR) SET(DDRA, _BV(PA2), DIR)
#define DOWN_BUTTON_DIR(DIR) SET(DDRA, _BV(PA3), DIR)
#define LEFT_BUTTON_DIR(DIR) SET(DDRA, _BV(PA4), DIR)
#define RIGHT_BUTTON_DIR(DIR) SET(DDRA, _BV(PA5), DIR)
#define A_BUTTON_DIR(DIR) SET(DDRA, _BV(PA6), DIR)
#define B_BUTTON_DIR(DIR) SET(DDRA, _BV(PA7), DIR)

//button outputs
#define UP_BUTTON_PULL(STATE) SET(PORTA, _BV(PA2), STATE) //active high
#define DOWN_BUTTON_PULL(STATE) SET(PORTA, _BV(PA3), STATE)
#define LEFT_BUTTON_PULL(STATE) SET(PORTA, _BV(PA4), STATE)
#define RIGHT_BUTTON_PULL(STATE) SET(PORTA, _BV(PA5), STATE)

#define A_BUTTON_PULL(STATE) SET(PORTA, _BV(PA6), STATE)
#define B_BUTTON_PULL(STATE) SET(PORTA, _BV(PA7), STATE)

//Devices(button) Inputs
#define UP_BUTTON ~GET(PINA, _BV(PA2))//Active Low
#define DOWN_BUTTON ~GET(PINA, _BV(PA3))
#define LEFT_BUTTON ~GET(PINA, _BV(PA4))
#define RIGHT_BUTTON ~GET(PINA, _BV(PA5))
#define A_BUTTON ~GET(PINA, _BV(PA6))
#define B_BUTTON ~GET(PINA, _BV(PA7))

//LCD
#define LCD_BACKLIGHT_DIR(DIR) SET(DDRB, _BV(PB3), DIR)

//Devices Outputs
///#define MULTI_LINES(STATE) SET(DDR?,(_BV(P?#)|_BV(P?#)|_BV(P?#)),DIR)

#define BAT_LOW_LED(STATE) SET(PORTA, _BV(PA1), ~STATE)
#define LCD_BACKLIGHT(STATE) SET(PORTB, _BV(PB3), STATE)

//LCD and SPI stuffs
#define LCD_CS_DIR(DIR) SET(DDRD, _BV(PD3), DIR)
#define LCD_CD_DIR(DIR) SET(DDRD, _BV(PD5), DIR)
#define LCD_RST_DIR(DIR) SET(DDRD, _BV(PD4), DIR)

#define LCD_CS(STATE) SET(PORTD, _BV(PD3), STATE)
#define LCD_CD(STATE) SET(PORTD, _BV(PD5), STATE)
#define LCD_RST(STATE) SET(PORTD, _BV(PD4), STATE)

#define LCD_CS_SET(STATE) SET(PORTD, _BV(PD3), STATE)
#define LCD_RST_SET(STATE) SET(PORTD, _BV(PD4), STATE)
#define LCD_CD_SET(STATE) SET(PORTD, _BV(PD5), STATE)

#define MOSI_SET(STATE) SET(PORTB, _BV(PB5), STATE)
#define MISO_SET(STATE) SET(PORTB, _BV(PB6), STATE)
#define SCK_SET(STATE) SET(PORTB, _BV(PB7), STATE)

//MOSI MISO SCK, Only to set output direction
#define MOSI_DIR(DIR) SET(DDRB, _BV(PB5), DIR)
#define MISO_DIR(DIR) SET(DDRB, _BV(PB6), DIR)
#define SCK_DIR(DIR) SET(DDRB, _BV(PB7), DIR)
#define PB4_DIR(DIR) SET(DDRB, _BV(PB4), DIR)
#define PB4_SS(STATE) SET(PORTB, _BV(PB4), STATE)

#define INTERRUPT_DIR(DIR) SET(DDRD, _BV(PD2), DIR)

#define RAM_CS_DIR(DIR) SET(DDRB, _BV(PB2), DIR)
#define RAM_HOLD_DIR(DIR) SET(DDRD, _BV(PD6), DIR)
#define RAM_WP_DIR(DIR) SET(DDRD, _BV(PD7), DIR)

#define RAM_HOLD(STATE) SET(PORTD, _BV(PD6), STATE)
#define RAM_WP(STATE) SET(PORTD, _BV(PD7), STATE)
#define RAM_CS(STATE) SET(PORTB, _BV(PB2), STATE)

#define ADC_BATT_DIR(DIR) SET(DDRA, _BV(PA0), DIR)
#define ADC_BATT(STATE) SET(PORTA, _BV(PA0), STATE)

#define WREN 0x06
#define WRITE 0b00000010
#define READ 0b00000011

#define ROWS_INIT 40
#define COLUMNS_INIT 90

#define BATT_TH 900

#define INCREMENT 51

//#define UP_BUTTON_PULL(STATE) SET(PORTA, _BV(PA2), STATE)
unsigned char frame_buffer[BUFFER_COL][BUFFER_ROW];
unsigned char ROWS = ROWS_INIT;
unsigned char COLUMNS = COLUMNS_INIT;
