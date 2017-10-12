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

//global variables
	byte row = 0;
	byte page = 0;
	byte column = 0;
	byte pixel = 0;
	byte frame_buffer[MAX_COL][MAX_PAGE];
	int ADC_BATT_V;


void buff_clr(void)
{	byte col;
	byte rrow;
	for(rrow = 0; rrow < MAX_PAGE; rrow++)
	{
		for(col=0;col<MAX_COL;col++)
			{
				frame_buffer[col][rrow] = 0x00;
			}
	}
}

void SPI_MasterInit(void) 
{	
	SS_HAT_DIR(OUT);
	SS_HAT(HIGH);

/* Set MOSI and SCK output, all others input */
	DDR_SPI = (1<<DD_MOSI)|(1<<DD_SCK); 

/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
	//data sheet page 140.
	//SPCR: SPI Control Register
	//SPE: SPI Enable
	//SPR1, SPR0: SPI Clock Rate Select 1 and 0

} // data sheet page 138	

void LCD_tx(byte LCD_type, byte LCD_inData) //type: data OR command
{	

	LCD_CD(LCD_type); //Instruction: Command / transfer Data
	LCD_CS (HIGH); //Chip select

	SPDR = LCD_inData;


	/* Wait for transmission complete */
	while(!( SPSR & _BV(SPIF)));

	/* Start transmission */
	
	//DATASHEET 142
	//SPSR: SPI Status Register
	//SPIF: SPI Interrupt Flag
	
	// When a serial transfer is complete, the SPIF Flag is set. An interrupt is generated if SPIE in
	//SPCR is set and global interrupts are enabled. If SS is an input and is driven low when the SPI is
	//in Master mode, this will also set the SPIF Flag. SPIF is cleared by hardware when executing the
	//corresponding interrupt handling vector. Alternatively, the SPIF bit is cleared by first reading
	//the SPI Status Register with SPIF set, then accessing the SPI Data Register (SPDR).

	//SPDR: SPI Data Register. The SPI Data Register is a read/write register used for data transfer
	//between the Register File and the SPI Shift Register. Writing to the register initiates data
	//transmission. Reading the register causes the Shift Register Receive buffer to be read.

	//while(!(SPSR & (1<<SPIF))) OR (!(SPSR & _BV(SPIF)));
	//(SPSR & (1<<SPIF)) will only have two values, either 0000 0000 or 1000 0000.the while loop will be
	//running only when the condition would be true. The condition will become false when SPIF will be as 
	//1 making (SPSR & (1<<SPIF)) = 1000 0000 which is non zero and the program will come out of the loop.

	LCD_CS(LOW); //Chip deselect

}

//Alternative method: bit bang

// void LCD_command_tx(byte tx_byte) //Sends a data byte
// {
// 	byte tx_processed;
// 	byte tx_mask = 0x80;
// 	LCD_CHIP_SELECT;
// 	LCD_DATA;
// 	while (tx_mask != 0x00)
// 	{
// 		tx_processed = tx_byte & tx_mask;
// 		SCK_SET_HIGH;
// 		if(tx_processed)
// 			MOSI_SET_HIGH;
// 		else
// 			MOSI_SET_LOW;
// 		SCK_SET_LOW;
// 		tx_mask>>=1;
// 	}
// 	SCK_SET_HIGH;
// 	LCD_CHIP_DESELECT;
// 	return(TRUE);
// }


void LCD_initialise(void)
{	

	LCD_CS(LOW); //Chip Deselect
	LCD_CS_DIR(OUT);

	LCD_CD_DIR(OUT); 

	LCD_RST_DIR(OUT);
	LCD_RST(HIGH);
	_delay_ms(10);

	LCD_RST(LOW);
	_delay_ms(10);

	LCD_tx(COMMAND, STARTLINE0);//Display start line 0 
	LCD_tx(COMMAND, SEG_DIR);//SEG reverse; Set SEG dirction
	LCD_tx(COMMAND, COM_DIR);//Normal COM0~COM63 
	LCD_tx(COMMAND, ALL_PIX_ON);//Disable -> Set All Pixel to ON 
	LCD_tx(COMMAND, DIS_INV_OFF);//Display inverse off 
	_delay_ms(120);
	LCD_tx(COMMAND, ST_BIAS);//Set LCD Bias Ratio A2/A3
	LCD_tx(COMMAND, ST_PWR_CONTR);//Set Power Control 28...2F; Booster, Regulator and Follower on
	LCD_tx(COMMAND, ST_R_RATIO);//Set VLCD Resistor Ratio 20...27
	LCD_tx(COMMAND, ST_ELEC_VOL);//Set Electronic Volume
	LCD_tx(COMMAND, ST_ELEC_VOL2);//Set Electronic Volume 00...3F
	LCD_tx(COMMAND, ST_TEMP_CONTR);//Set Adv. Program Control
	LCD_tx(COMMAND, ST_TEMP_CONTR2);//Set Adv. Program Control x00100yz yz column wrap x Temp Comp 
	LCD_tx(COMMAND, DISP_ON);//Display on	
}


void pin_Init(vold)
{

	BAT_LOW_LED_DIR(OUT); //Set BATTERY LED I/Os as outputs.
	BAT_LOW_LED(OFF); //Make sure it is off before changing direction
	
	LCD_BKLIGHT(OFF); //Turn off LCD_BKLIGHT
	LCD_BKLIGHT_DIR(OUT); // Set LCD_BKLIGHT I/Os as output.

	UP_BUTTON_DIR(IN); //Set UP_BUTTON I/Os as input.
	UP_BUTTON_PULL(ON);  //Set UP_BUTTON_PILL I/Os internal pull up.

	LEFT_BUTTON_DIR(IN); 
	LEFT_BUTTON_PULL(ON);

	RIGHT_BUTTON_DIR(IN); 
	RIGHT_BUTTON_PULL(ON);

	DOWN_BUTTON_DIR(IN); 
	DOWN_BUTTON_PULL(ON); 

	ACT1_BUTTON_DIR(IN);
	ACT1_BUTTON_PULL(ON);

	ACT2_BUTTON_DIR(IN);
	ACT2_BUTTON_PULL(ON);

	ACT3_BUTTON_DIR(IN);
	ACT3_BUTTON_PULL(ON); 

}


void select_page(byte page)
{
	byte page_cmd_address;

	page_cmd_address = (CMD_PAGE|page);
	LCD_tx(COMMAND,page_cmd_address);

}

// void select_page(byte page)
// {
// 	byte page_cmd_address;

// 	if (page>MAX_PAGE)
// 	{
// 		page = MAX_PAGE-1;
// 	}

// 	if (page<0)
// 	{
// 		page = 0;
// 	}
// 	page_cmd_address = (CMD_PAGE|page);

// 	LCD_tx(COMMAND,page_cmd_address);
// }

void select_column(byte column)
{
	byte page_cmd_address_MSB;
	byte page_cmd_address_LSB;


	page_cmd_address_LSB = (CMD_COL_LSB|(column & P_LSB));
	page_cmd_address_MSB = (CMD_COL_MSB|column >> SHIFT2MSB);

	LCD_tx(COMMAND,page_cmd_address_LSB);
	LCD_tx(COMMAND,page_cmd_address_MSB);
}


void LCD_clear(void)
{

	byte page;
	byte column;

	for (page = MIN_PAGE-1; page < MAX_PAGE; page++ )
	{
		select_page(page);

		for (column = MIN_COL-1; column < MAX_COL; column++)
		{	
			select_column(column);
			LCD_tx(DATA, CLEAR);
		}
	}	
}


void Sketch(void)
{
	
		if(UP_BUTTON)
		{
			if(row>0)
			row--;
		}

		if(DOWN_BUTTON)
		{
			if(row<8*MAX_PAGE-1)
			row++;
		}

		if(LEFT_BUTTON)
		{
			if(column>0)
			column--;
		}

		if(RIGHT_BUTTON)
		{
			if(column<MAX_COL-1)
			column++;
		}

		page = row/8;
		pixel = row%8;

		select_page(page);
		select_column(column);
		
		pixel = (_BV(pixel)|frame_buffer[column][page]);
		frame_buffer[column][page] = pixel;

		LCD_tx(DATA,pixel);
		_delay_ms(225);
}


// Pin D4 (OC1B)
void PWM_Init(void)
{
	LCD_BKLIGHT_DIR(OUT);
	TCCR1A = (1<<COM1B1)|(1<<COM1B0)|(1<<WGM10); //00110001 page 110
	TCCR1B = (1<<WGM12)|(1<<CS11); //00001010
	TCNT1 = 0;
	ICR1 = 2048;
	OCR1A = 0;
	OCR1B = TOP; 

	// page 114
	// CLK I/O /8
}

void PWM(void)
{
	if (ACT3_BUTTON)
	{
		if(OCR1B + INCREMENT<=TOP)
		{
			OCR1B += INCREMENT;
		}
		else
		{
			OCR1B = BOTTOM;
		}
		_delay_ms(120);
	}

}



void INTERRUPT_Inti(void)
{	

	// Interrupt page 45

	/* Enable change of interrupt vectors */
	GICR = _BV(INT1);//PD3
	// General Interrupt Control Register (GICR)
	/* Move interrupts to boot Flash section */
	GIFR = _BV(INTF1); //optional
	//Gerneral Interrupt Flag Register
	//When the IVSEL bit is cleared (zero), the Interrupt Vectors are placed at the start 
	//of the Flash memory. When this bit is set (one), the interrupt vectors are moved to 
	//the beginning of the Boot Loader section of the Flash.
	//The IVCE bit must be written to logic one to enable change of the IVSEL bit.

	MCUCR = _BV(ISC11) | _BV(ISC10);//INT1
	// SET CONTROL OF INT1

  	sei();//Enable interrupts 
  	//another way to write enable: SREG(1<<7);

}


ISR(INT1_vect)
{
	PWM();
	

//	Sketch();

}


void ADC_Init(void)
{
	ADMUX = (1<<REFS0)|(1<<REFS1)|(1<<MUX2)|(1<<MUX1)|(1<<MUX0);
	
	//Internal 2.56V Voltage Reference with external capacitor at AREF pin
	//PA7

	ADCSRA = (1<<ADEN);//ADC Enable


}


int ADC_READ(void)
{
	ADCSRA |= (1<<ADSC); //bitwise opration 

	while(ADCSRA &(1<<ADSC));// wait for conversion to compplete

	return (ADC);

}


int main(void)
{	
	LCD_BKLIGHT(OFF); 
	pin_Init();
	SPI_MasterInit(); //Initialise SPI
	LCD_initialise(); //Initialise LCD
	LCD_clear();
	PWM_Init();	

	_delay_ms(100);
	LCD_BKLIGHT(ON); 

	EX_INTERRUPT_DIR(IN); 
	EX_INTERRUPT_PULL(HIGH);
	INTERRUPT_Inti();
	_delay_ms(100);

	buff_clr();
	_delay_ms(100);

	ADC_Init();
	_delay_ms(200);

	while(TRUE)
	{
		// check Battary life
		ADC_BATT_V = ADC_READ();
		if(ADC_BATT_V < BATT_TH)
		{
		BAT_LOW_LED(ON);
		}
		else
		{
		BAT_LOW_LED(OFF);
		}	

		Sketch();

		
	}

}

