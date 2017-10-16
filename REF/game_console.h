
/*************************************************************************
Title:    Game Console Template Header File
Inital Author:   David Jahshan
Extended by : (Rong-Jhen TSAI) (816613) 
Software: AVR-GCC 
Hardware: ATMEGA16 @ 8Mhz 

DESCRIPTION:
	Macros for Game Console

*************************************************************************/

#include <avr/io.h> 
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#define byte unsigned char 

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

/*SET and GET MACRO*/
#define SET(PORT,MASK,VALUE) PORT = ((MASK & VALUE) | (PORT & ~MASK))
#define GET(PORT,MASK) PORT & MASK

//============================
//  Devices Direction MACROs  
//============================
//#define MULTI_LINES_DIR(DIR) SET(DDR?,(_BV(P?#)|_BV(P?#)|_BV(P?#)),DIR)
#define BAT_LOW_LED_DIR(DIR) SET(DDRA,_BV(PA4),DIR)

#define UP_BUTTON_DIR(DIR) SET(DDRC,_BV(PC0),DIR)
#define DOWN_BUTTON_DIR(DIR) SET(DDRC,_BV(PC1),DIR)
#define RIGHT_BUTTON_DIR(DIR) SET(DDRA,_BV(PA5),DIR)
#define LEFT_BUTTON_DIR(DIR) SET(DDRA,_BV(PA6),DIR)
#define ACTION_BUTTON_DIR(DIR) SET(DDRA,_BV(PA7),DIR)
#define EXIT_BUTTON_DIR(DIR) SET(DDRC,_BV(PC7),DIR)
#define HOME_BUTTON_DIR(DIR) SET(DDRC,_BV(PC6),DIR)

#define LCD_BL_DIR(DIR) SET(DDRB,_BV(PB3),DIR)
#define LCD_CS_DIR(DIR) SET(DDRA,_BV(PA2),DIR)
#define LCD_RST_DIR(DIR) SET(DDRA,_BV(PA1),DIR)
#define LCD_CD_DIR(DIR) SET(DDRA,_BV(PA0),DIR)

//#define MOSI_DIR(DIR) SET(DDRB,_BV(PB5),DIR)
//#define MISO_DIR(DIR) SET(DDRB,_BV(PB6),DIR)
//#define SCK_DIR(DIR) SET(DDRB,_BV(PB6),DIR)

//============================
//  Devices Outputs
//============================
//#define MULTI_LINES(STATE) SET(DDR?,(_BV(P?#)|_BV(P?#)|_BV(P?#)),DIR)
#define BAT_LOW_LED(STATE) SET(PORTA,_BV(PA4), STATE)

#define UP_BUTTON_SET(STATE) SET(PORTC,_BV(PC0), STATE)
#define DOWN_BUTTON_SET(STATE) SET(PORTC,_BV(PC1), STATE)
#define RIGHT_BUTTON_SET(STATE) SET(PORTA,_BV(PA5), STATE)
#define LEFT_BUTTON_SET(STATE) SET(PORTA,_BV(PA6), STATE)
#define ACTION_BUTTON_SET(STATE) SET(PORTA,_BV(PA7), STATE)  //B
#define EXIT_BUTTON_SET(STATE) SET(PORTC,_BV(PC6), STATE)  //A
#define HOME_BUTTON_SET(STATE) SET(PORTC,_BV(PC7), STATE)

#define LCD_BL_SET(STATE) SET(PORTB,_BV(PB3), STATE)
#define LCD_CS_SET(STATE) SET(PORTA,_BV(PA2), STATE)
#define LCD_RST_SET(STATE) SET(PORTA,_BV(PA1), STATE)
#define LCD_CD_SET(STATE) SET(PORTA,_BV(PA0), STATE)

#define MOSI_SET(STATE) SET(PORTB,_BV(PB5), STATE)
#define MISO_SET(STATE) SET(PORTB,_BV(PB6), STATE)
#define SCK_SET(STATE) SET(PORTB,_BV(PB7), STATE)

//============================
//  Devices Inputs
//============================
#define UP_BUTTON GET(PINC,_BV(PC0))
#define DOWN_BUTTON GET(PINC,_BV(PC1))
#define RIGHT_BUTTON GET(PINA,_BV(PA5))
#define LEFT_BUTTON GET(PINA,_BV(PA6))
#define ACTION_BUTTON GET(PINA,_BV(PA7))
#define EXIT_BUTTON GET(PINC,_BV(PC6))
#define HOME_BUTTON GET(PINC,_BV(PC7))

//====================================================================
#define SET(PORT,MASK,VALUE) PORT = ((MASK & VALUE) | (PORT & ~MASK))
#define GET(PORT,MASK) PORT & MASK

#define AD_TRANS_DIR(DIR) SET(DDRA,_BV(PA3),DIR)  
#define AD_TRANS(STATE) SET(PORTA,_BV(PA3),STATE)

#define INTERRUPT_DIR(DIR) SET(DDRD,_BV(PD3),DIR)
#define INTERRUPT_S(STATE) SET(PORTD,_BV(PD3),STATE)
#define INTERRUPT GET(PIND,_BV(PD3))

#define PWM_DIR(DIR) SET(DDRB,_BV(PB3),DIR)//
#define BRIGHT_INI 30

#define LCD_CD_DIR(DIR) SET(DDRA,_BV(PA0),DIR)
#define LCD_CD(STATE) SET(PORTA,_BV(PA0),STATE)

#define LCD_RST_DIR(DIR) SET(DDRA,_BV(PA1),DIR)
#define LCD_RST(STATE) SET(PORTA,_BV(PA1),STATE)

#define LCD_CS_DIR(DIR) SET(DDRA,_BV(PA2),DIR)
#define LCD_CS(STATE) SET(PORTA,_BV(PA2),STATE)

#define SS_DIR(DIR) SET(DDRB, _BV(PB4), DIR)
#define MOSI_DIR(DIR) SET(DDRB, _BV(PB5), DIR)
#define MISO_DIR(DIR) SET(DDRB, _BV(PB6), DIR)
#define SCK_DIR(DIR) SET(DDRB, _BV(PB7), DIR)

#define OFF 0x00
#define ON  0xFF

#define IN 0x00
#define OUT  0xFF

#define HIGH 0xFF
#define LOW 0x00

#define BAT_LOW 900

#define COMMAND 0x00
#define DATA 0xFF

#define CMD_PAGE 0xB0
#define CMD_COL_LSB 0x00
#define CMD_COL_MSB 0x10

#define MAX_COLUMNS 102
#define MAX_PAGES 8
#define MAX_ROWS 64
#define MIN_ROWS 0
#define ROWS_INIT 32
#define COLUMNS_INIT 51

#define MAX_BRIGHT 255
#define MIN_BRIGHT 0
#define ADJUST_BRIGHT 20

#define DISPLAY_ST 0x40
#define SEG_REVERSE 0xA1
#define NORMAL_COM 0xC0
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

//=================================================================
unsigned int addata;
unsigned char frame_buffer[MAX_COLUMNS][MAX_PAGES];
volatile int bright=BRIGHT_INI;
unsigned char ROWS=ROWS_INIT;
unsigned char COLUMNS=COLUMNS_INIT;

byte Bright_State[8] = {0x00,0x20,0x40,0x60,0x80,0xA0,0xC0,0xE0};
byte Bright_Level = 1;
