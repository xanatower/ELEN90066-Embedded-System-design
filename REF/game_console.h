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
#include <util/delay.h>


#define byte unsigned char
 
/*ON OFF*/
#define ON 				0xFF
#define OFF 			0x00
#define HIGH 			0xFF
#define LOW 			0x00
#define IN 				0x00
#define OUT 			0xFF
#define ALL 			0xFF
#define TRUE 			1
#define FALSE 			0
#define FORWARD 		0x00
#define BACK 			0xFF

#define COMMAND 		0x00
#define DATA 			0xFF

#define DD_MOSI 		DDB5
#define DD_SCK 			DDB7
#define DDR_SPI 		DDRB

#define STARTLINE0 		0x40
#define SEG_DIR 		0xA1
#define COM_DIR 		0xC0
#define ALL_PIX_ON 		0xA4
#define DIS_INV_OFF 	0xA6
#define ST_BIAS 		0xA2
#define ST_PWR_CONTR	0x2F
#define ST_R_RATIO 		0x27
#define ST_ELEC_VOL 	0x81
#define ST_ELEC_VOL2 	0x10
#define ST_TEMP_CONTR 	0xFA
#define ST_TEMP_CONTR2 	0x90
#define DISP_ON 		0xAF

#define CMD_PAGE 		0xB0
#define MAX_PAGE		8
#define MIN_PAGE 		1
#define MAX_COL 		102  
#define MIN_COL			1
#define CMD_COL_LSB 	0x00
#define CMD_COL_MSB 	0x10
	
#define P_LSB 			0x0F
#define SHIFT2MSB 		4
#define CLEAR 			0x00
#define INF_LOOP 		1
#define BOTTOM 			0x00
#define TOP 			0xFF
#define INCREMENT		51
#define BATT_TH			560

//#define 

/*SET and GET MACRO*/
#define SET(PORT,MASK,VALUE) 		PORT = ((MASK & VALUE) | (PORT & ~MASK))
#define GET(PORT,MASK) 				PORT & MASK


//Devices Direction MACROs
//#define MULTI_LINES_DIR(DIR) SET(DDR?,(_BV(P?#)|_BV(P?#)|_BV(P?#)),DIR)
	//Battery Low LED
#define BAT_LOW_LED_DIR(DIR)		SET(DDRC,_BV(PC1),DIR)
	//Buttoms
#define UP_BUTTON_DIR(DIR)			SET(DDRA,_BV(PA1),DIR)
#define LEFT_BUTTON_DIR(DIR)		SET(DDRA,_BV(PA2),DIR)
#define RIGHT_BUTTON_DIR(DIR) 		SET(DDRA,_BV(PA3),DIR)
#define DOWN_BUTTON_DIR(DIR) 		SET(DDRA,_BV(PA4),DIR)
#define ACT1_BUTTON_DIR(DIR) 		SET(DDRA,_BV(PA5),DIR)
#define ACT2_BUTTON_DIR(DIR) 		SET(DDRA,_BV(PA6),DIR)
#define ACT3_BUTTON_DIR(DIR) 		SET(DDRA,_BV(PA0),DIR)
	//LCD
#define LCD_CS_DIR(DIR)				SET(DDRD,_BV(PD7),DIR)
#define LCD_CD_DIR(DIR) 			SET(DDRD,_BV(PD6),DIR)
#define LCD_RST_DIR(DIR) 			SET(DDRD,_BV(PD5),DIR)
#define LCD_BKLIGHT_DIR(DIR) 		SET(DDRD,_BV(PD4),DIR)
	//NAND
#define EX_INTERRUPT_DIR(DIR) 		SET(DDRD,_BV(PD3),DIR)	
	//RAM
#define FRAM_WP_DIR(DIR) 			SET(DDRB,_BV(PB0),DIR)
#define FRAM_CS_DIR(DIR) 			SET(DDRB,_BV(PB1),DIR)
#define FRAM_HOLD_DIR(DIR) 			SET(DDRB,_BV(PB3),DIR)
	//
#define MOSI_DIR(DIR)			 	SET(DDRB,_BV(PB5),DIR)
#define MISO_DIR(DIR)	 			SET(DDRB,_BV(PB6),DIR)
#define SCK_DIR(DIR) 				SET(DDRB,_BV(PB7),DIR)
#define SS_HAT_DIR(DIR) 			SET(DDRB,_BV(PB4),DIR)
#define ADC_BATT_DIR(DIR) 				SET(DDRA,_BV(PA7),DIR)

//Devices Outputs
//#define MULTI_LINES(STATE) SET(DDR?,(_BV(P?#)|_BV(P?#)|_BV(P?#)),DIR)
#define BAT_LOW_LED(STATE) 			SET(PORTC,_BV(PC1),~STATE) //active LOW
#define UP_BUTTON_PULL(STATE) 		SET(PORTA,_BV(PA1), STATE) //active high
#define LEFT_BUTTON_PULL(STATE) 	SET(PORTA,_BV(PA2), STATE)
#define RIGHT_BUTTON_PULL(STATE) 	SET(PORTA,_BV(PA3), STATE)
#define DOWN_BUTTON_PULL(STATE) 	SET(PORTA,_BV(PA4), STATE)
#define ACT1_BUTTON_PULL(STATE) 	SET(PORTA,_BV(PA5), STATE)
#define ACT2_BUTTON_PULL(STATE) 	SET(PORTA,_BV(PA6), STATE)
#define ACT3_BUTTON_PULL(STATE) 	SET(PORTA,_BV(PA0), STATE)
#define EX_INTERRUPT_PULL(STATE) 	SET(PORTD,_BV(PD3), STATE)


#define LCD_CS(STATE) 				SET(PORTD,_BV(PD7),~STATE) // CS inverse 
#define LCD_CD(STATE) 				SET(PORTD,_BV(PD6), STATE)
#define LCD_RST(STATE) 				SET(PORTD,_BV(PD5),~STATE) // RST inverse 
#define LCD_BKLIGHT(STATE) 			SET(PORTD,_BV(PD4), STATE) // active low

#define FRAM_WP(STATE)				SET(PORTB,_BV(PB0), STATE)
#define FRAM_CS(STATE)				SET(PORTB,_BV(PB1), STATE)
#define FRAM_HOLD(STATE)			SET(PORTB,_BV(PB3), STATE)
#define SS_HAT(STATE) 				SET(PORTB,_BV(PB4), STATE)  


//Devices Inputs
#define UP_BUTTON 					~GET(PINA,_BV(PA1))
#define LEFT_BUTTON 				~GET(PINA,_BV(PA2))
#define RIGHT_BUTTON 				~GET(PINA,_BV(PA3))
#define DOWN_BUTTON 				~GET(PINA,_BV(PA4))
#define ACT1_BUTTON 				~GET(PINA,_BV(PA5))
#define ACT2_BUTTON 				~GET(PINA,_BV(PA6))
#define ACT3_BUTTON 				~GET(PINA,_BV(PA0))
#define EX_INTERRUPT 				~GET(PIND,_BV(PD3))

#define ADC_BATT					GET(PINA,_BV(PA7))
/* function declaration */
