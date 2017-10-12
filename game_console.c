/*************************************************************************
Title:    game_console Template
Initial Author:   David Jahshan
Extended by : (PUT YOUR NAME HERE) (PUT YOUR STUDENT NUMBER HERE)
Software: AVR-GCC 
Hardware: ATMEGA16 @ 8Mhz 

DESCRIPTION:
	Main and functions for Game Console basic sample code

*************************************************************************/

#include "game_console.h"

#define INCREMENT 51

#define MAX_PAGE		8
#define MAX_COLUMN		102



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


byte row = 0;
byte page = 0;
byte column = 0;
byte pixel = 0;
byte frame_buffer[MAX_COL][MAX_PAGE];



//From datasheet P138

void SPI_MasterInit(void)
{	

	//P140
	MOSI_DIR(OUT);
	SCK_DIR(OUT);
	PB4_DIR(OUT);//WHY???

	/* Set MOSI and SCK output, all others input */
//	DDR_SPI = (1 << DD_MOSI) | (1 << DD_SCK); //this doesnt work for some reason
	//so we set it manually

	/* Enable SPI, Master, set clock rate fck/16 */
	//p140
	SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0) ;
	//SPCR: SPI Control Register
	//SPE: SPI Enable
	//SPR1, SPR0: SPI Clock Rate Select 1 and 0
}



//CS: CHIP SELECT
//CD: 



//customeised SPI_MasterTransmit()
//P142
void LCD_TX(byte type, byte cData)
{	
	//2 MODES: type can be COMMAND or DATA
	LCD_CD(type); //Instruction: Command / transfer Data
	LCD_CS(HIGH); //select this chip

	//cData is the input data that will be transmitted

	//SPI Data Register SPDR

	/* Start transmission */
	SPDR = cData;

	/* Wait for transmission complete */
	//SPSR: SPI status register
	//SPIF: 
	while (!(SPSR & _BV(SPIF)));
	
	LCD_CS(LOW); //deselect this chip

}



//return byte
void LCD_initialise(void)
{	
	//initialise MCU pin

	LCD_CS_DIR(OUT);
	LCD_CS(LOW); //Chip Deselect
	
	LCD_CD_DIR(OUT); 
	
	LCD_RST_DIR(OUT);
	LCD_RST(HIGH);
	_delay_ms(10);
	
	LCD_RST(LOW);
	_delay_ms(10);

	//page 8 of the DOGLCD manual

	LCD_TX(CMD, 0x40); //Display start line 0
	LCD_TX(CMD, 0xA0); //SEG reverse //A1 is the other orientation
	LCD_TX(CMD, 0xC8); //Normal COM0~COM63 //C8 is the reversed COM 
	LCD_TX(CMD, 0xA4); //Disable -> Set All Pixel to A5 is to ptint a black screen
	LCD_TX(CMD, 0xA6); //Display inverse off
	_delay_ms(120);
	LCD_TX(CMD, 0xA2); //Set LCD Bias Ratio A2/A3
	LCD_TX(CMD, 0x2F); //Set Power Control 28...2F
	LCD_TX(CMD, 0x27); //Set VLCD Resistor Ratio 20...27
	LCD_TX(CMD, 0x81); //Set Electronic Volume
	LCD_TX(CMD, 0x10); //Set Electronic Volume 00...3F
	LCD_TX(CMD, 0xFA); //Set Adv. Program Control
	LCD_TX(CMD, 0x90); //Set Adv. Program Control x00100yz yz column wrap x Temp Comp
	LCD_TX(CMD, 0xAF); //Display on
	//SRAM seem to be something inside the MCU, NOT the internal FRAM
	



	//return (TRUE);
}


void select_column(byte column)
{
	byte page_cmd_address_MSB;
	byte page_cmd_address_LSB;


	page_cmd_address_LSB = (CMD_COL_LSB|(column & P_LSB));
	page_cmd_address_MSB = (CMD_COL_MSB|column >> SHIFT2MSB);

	LCD_TX(CMD,page_cmd_address_LSB);
	LCD_TX(CMD,page_cmd_address_MSB);
}

void select_page(byte page)
{
	byte page_cmd_address;

	page_cmd_address = (CMD_PAGE|page);
	LCD_TX(CMD,page_cmd_address);

}
void LCD_CLR(void)
{

	byte page;
	byte column;

	for (page = MIN_PAGE-1; page < MAX_PAGE; page++ )
	{
		select_page(page);

		for (column = MIN_COL-1; column < MAX_COL; column++)
		{	
			select_column(column);
			LCD_TX(DAT, CLEAR);
		}
	}	
}

void button_init(void)
{

	UP_BUTTON_DIR(IN);
	UP_BUTTON_PULL(ON);

	DOWN_BUTTON_DIR(IN);
	DOWN_BUTTON_PULL(ON);

	LEFT_BUTTON_DIR(IN);
	LEFT_BUTTON_PULL(ON);

	RIGHT_BUTTON_DIR(IN);
	RIGHT_BUTTON_PULL(ON);

	A_BUTTON_DIR(IN);
	A_BUTTON_PULL(ON);

	B_BUTTON_DIR(IN);
	B_BUTTON_PULL(ON);
}

void PWN_init(void)
{

	LCD_BACKLIGHT_DIR(OUT); //direction of the port
	//need to modify TCCR0:Timer control register
	//01111010
	TCCR0 = (1 << WGM00) | (1 << COM01) | (1 << COM00) | (1 << WGM01) | (1 << CS01);
	//when oc1b

	OCR0 = BOTTOM; //set it to lowest
}

void PWM(void)
{
	if (A_BUTTON)
	{
		if (OCR0 + INCREMENT <= TOP)
		{
			OCR0 += INCREMENT;
		}
		else
		{
			OCR0 = BOTTOM;
		}
		_delay_ms(120);
	}
}

void UP_BUT_NOT_FUNCTIONING(void)
{
	if (UP_BUTTON) //get device status
	{
		BAT_LOW_LED(ON);
	}
	else
	{
		BAT_LOW_LED(OFF);
	}
}

void button_det(void)
{

	UP_BUT_NOT_FUNCTIONING();
	if (DOWN_BUTTON) //get device status
	{
		BAT_LOW_LED(ON);
	}
	else
	{
		BAT_LOW_LED(OFF);
	}

	PWM();

	if (B_BUTTON) //get device status
	{
		BAT_LOW_LED(ON);
	}
	else
	{
		BAT_LOW_LED(OFF);
	}
}

//input is a 8 bit 
void select_page (byte page)
{
	byte page_cmd_address;
	//the format of the command is set 
	page_cmd_address =(CMD_PAGE | page);
	LCD_TX(DAT, page_cmd_address);


}

void select_column (byte column)
{	
	//P5 
	//fixed format
	byte page_cmd_adress_MSB;
	byte page_cmd_address_LSB;
	page_cmd_address_LSB =(CMD_COL_LSB | (column&0x0F));
	page_cmd_address_MSB =(CMD_COL_MSB | (column >> 4));
	//the whole command is splitted into 2 halves
	LCD_TX(DAT, page_cmd_address_LSB);
	LCD_TX(DAT, page_cmd_address_MSB);
}





//GICR, 
//External
/*Interrupts P68
The External Interrupts are triggered by the INT0, INT1, and INT2 pins. Observe that, if enabled,
the interrupts will trigger even if the INT0..2 pins are configured as outputs. This feature provides
a way of generating a software interrupt*/

int main(void)
{
	/*pin init*/
	SPI_MasterInit();
	LCD_BACKLIGHT_DIR(OUT);
	LCD_BACKLIGHT(OFF);
	button_init(); //initialise the buttons and pull up
	PWN_init();

	BAT_LOW_LED_DIR(OUT);
	BAT_LOW_LED(ON);
	LCD_BACKLIGHT(ON);

	//STUCK HERE
	LCD_initialise();
	//LCD_CLR();

	BAT_LOW_LED(OFF);
	LCD_BACKLIGHT(OFF);

	//try to turn on LCD backlight


	

	while (TRUE) //Master loop always true so always loop
	{
		button_det();
	}
}
