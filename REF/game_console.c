/*************************************************************************
Title:    game_console Template
Initial Author:   David Jahshan
Extended by : (Rong-Jhen TSAI) (816613)
Software: AVR-GCC 
Hardware: ATMEGA16 @ 8Mhz 

DESCRIPTION:
	Main and functions for Game Console basic sample code

*************************************************************************/

#include "game_console.h" 

unsigned int AD()
{
 ADMUX|=_BV(REFS0)|_BV(REFS1); //Set internal 2.56V voltage reference with external capacitor at AREF pin
 ADCSRA|=_BV(ADEN); //Set ADC enable
 ADCSRA|=_BV(ADSC); //Set ADC start conversion
 while(!(ADCSRA&_BV(ADIF))); //Wait AD transformation finishes
 return(ADC);
}

void PWM_Init()
{
   TCCR0|=(1<<WGM00)|(1<<WGM01)|(1<<COM01)|(1<<CS00);
   DDRB|=(1<<PB3);
}

void SetPWMOutput(byte duty)
{
   OCR0=duty;
}

void SPI_Init(void)
{
 SPCR|= _BV(SPE) | _BV(MSTR) | _BV(SPR0); //Set SPI enable, Master Mode,SCK frequency(fosc/16)
}

unsigned char SPI_Transmit(unsigned char Tx_Data)
{
 SPDR=Tx_Data;
 while(!(SPSR&_BV(SPIF)));//Wait Master data transmission finishes
 return(SPDR);
}

void LCD_Command(unsigned char command)
{
 LCD_CS(LOW);//Set LCD_CS enable
 LCD_CD(COMMAND);//Set LCD_CD command enable
 SPI_Transmit(command);
 LCD_CS(HIGH);
    
}

void LCD_Data(unsigned char data)
{
 LCD_CS(LOW);//Set LCD_CS enable
 LCD_CD(DATA);//Set LCD_CD data enable
 SPI_Transmit(data);
 LCD_CS(HIGH);
}

void LCD_Init(void)
{
 LCD_Command(DISPLAY_ST);//Display start line 0
 LCD_Command(SEG_REVERSE);//SEG reverse
 LCD_Command(NORMAL_COM);//Normal COM0-COM63
 LCD_Command(DIS_PIXELS_ON);//Disable all pixels on
 LCD_Command(DIS_INVERSE_OFF);//Display inverse off
 LCD_Command(LCD_BIAS_RATIO);//Set LCD Bias Ratio:1/9
 LCD_Command(POWER_CONTROL);//Set power control: booster on, voltage regulator on and voltage follower on
 LCD_Command(LCD_RESISTOR_RATIO);//Set VLCD resistor ratio
 LCD_Command(SET_ELECTRONIC_VOLUME1);
 LCD_Command(SET_ELECTRONIC_VOLUME2);//Set Electronic Volume:16
 LCD_Command(SET_ADVANCED_PROGRAM_CONTROL0);
 LCD_Command(SET_ADVANCED_PROGRAM_CONTROL1);//Set Advanced Program Control:-0.11%/?, PA,WA,CA disable
 LCD_Command(DISPLAY_ON);// Display on
}

void select_page(unsigned char page)
{
 unsigned char page_cmd_address;
 page_cmd_address=(CMD_PAGE|page);//Set page address
 LCD_Command(page_cmd_address);
}

void select_column(unsigned char column)
{
 unsigned char column_cmd_address_MSB;
 unsigned char column_cmd_address_LSB;
 column_cmd_address_LSB=(CMD_COL_LSB|(column&0x0F));//Set column LSB address
 column_cmd_address_MSB=(CMD_COL_MSB|(column>>4));//Set column MSB address
 LCD_Command(column_cmd_address_LSB);
 LCD_Command(column_cmd_address_MSB);
}

void Etch_Sketch(unsigned char row,unsigned char column)
{
 if(column>MAX_COLUMNS)
 column=MAX_COLUMNS-1;//Limit column ranges

 unsigned char page=row/8;//Set page
 unsigned char pixel=row%8;//Set pixel

 if(page>MAX_PAGES)
 page=MAX_PAGES-1;//Limit page ranges

 select_page(page);
 select_column(column);
 pixel=(_BV(pixel)|(frame_buffer[column][page]));
 frame_buffer[column][page]=pixel;
 LCD_Data(pixel);
 _delay_ms(100);
}

void Interrupt_Init(void)
{
 INTERRUPT_DIR(IN);
 cli();//Set global interrupt disable  
 MCUCR|=_BV(ISC11)|_BV(ISC10);//Set interrupt 1(INT1) the rising edge generating request 
 GICR|=_BV(INT1); //Set interrupt 1(INT1) enable
 GIFR|=_BV(INTF1);//Set External Interrupt Flag 1
 sei();//Set global interrupt enable  
}

void LCD_Clear_HIGH(void)
{
 unsigned char page,column;
 for (page=0;page<MAX_PAGES;page=page+2)
 {
  for (column=0;column<MAX_COLUMNS;column=column+2)
  {
   select_page(page);
   select_column(column);
   LCD_Data(HIGH);
   frame_buffer[column][page]=HIGH;				
  }
 }
}	

void LCD_Clear_LOW(void)
{
 unsigned char page,column;
 for (page=0;page<MAX_PAGES;page++)
 {
  for (column=0;column<MAX_COLUMNS;column++)
  {
   select_page(page);
   select_column(column);
   LCD_Data(LOW);
   frame_buffer[column][page]=LOW;	//initial			
  }
 }
}	

void LCD_Image_Shift(void)
{
 unsigned char page,column;
 for (page=0;page<MAX_PAGES;page++)
 {
  for (column=0;column<MAX_COLUMNS;column++)
  {
   select_page(page);
   select_column(column);

   LCD_Data(frame_buffer[column][page]);
   frame_buffer[column][page]=frame_buffer[column+1][page+1];	
  }
 }
}

void Port_Init()
{
	//===========================
	//  I/O and initial define
	//===========================
	BAT_LOW_LED(OFF); 
	BAT_LOW_LED_DIR(OUT); 

	UP_BUTTON_SET(HIGH);
	UP_BUTTON_DIR(IN); 
	DOWN_BUTTON_SET(HIGH);
	DOWN_BUTTON_DIR(IN); 
	RIGHT_BUTTON_SET(HIGH);
	RIGHT_BUTTON_DIR(IN); 
	LEFT_BUTTON_SET(HIGH);
	LEFT_BUTTON_DIR(IN); 
	ACTION_BUTTON_SET(HIGH);
	ACTION_BUTTON_DIR(IN); 
	EXIT_BUTTON_SET(HIGH);
	EXIT_BUTTON_DIR(IN); 
	HOME_BUTTON_SET(HIGH);
	HOME_BUTTON_DIR(IN); 

	LCD_BL_SET(LOW);
	LCD_BL_DIR(OUT);
	LCD_CS_SET(LOW);
	LCD_CS_DIR(OUT);
	LCD_RST_SET(LOW);
	LCD_RST_DIR(OUT);
	LCD_CD_SET(LOW);
	LCD_CD_DIR(OUT);

	MOSI_SET(LOW);
	MOSI_DIR(OUT);
	MISO_SET(LOW);
	MISO_DIR(OUT);
	SCK_SET(LOW);
	SCK_DIR(OUT);

 	AD_TRANS_DIR(IN);//Set AD transformation input

 	PWM_DIR(OUT);//Set PWM input 
 
 	SS_DIR(OUT);//Set SS output,which is a general output pin
 	MOSI_DIR(OUT);//Set MOSI output
 	SCK_DIR(OUT);//Set SCK output

 	LCD_CD_DIR(OUT);//Set CD output
 	LCD_CS_DIR(OUT);//Set CS output

 	LCD_RST_DIR(OUT);//Set RST output
 	LCD_RST(HIGH); //Set RST disable
}

ISR(INT1_vect)// Flag which enters to interrupt 1(INT1)
{
		if(~HOME_BUTTON)  
		{	
			//BAT_LOW_LED(OFF);
 			//_delay_ms(100);
			//Etch_Sketch(ROWS, COLUMNS);
		} 
		else
		{
			//BAT_LOW_LED(ON);
		}

		if(~EXIT_BUTTON)  
		{	
			if(Bright_Level>=1)
				Bright_Level--;
			else
				Bright_Level = 0;

			SetPWMOutput(Bright_State[Bright_Level]);
 			_delay_ms(200);
		}

		if(~ACTION_BUTTON)  
		{	
			if(Bright_Level<7)
				Bright_Level++;
			else
				Bright_Level = 7;

			SetPWMOutput(Bright_State[Bright_Level]);
 			_delay_ms(200);
		} 
	
		if(~RIGHT_BUTTON && COLUMNS<MAX_COLUMNS-1)  
		{	
			Etch_Sketch(ROWS, COLUMNS++);
 			_delay_ms(100);
		}
	
		if(~LEFT_BUTTON && COLUMNS>MIN_ROWS)  
		{	
			Etch_Sketch(ROWS, COLUMNS--);
 			_delay_ms(100);
		} 	

		if(~UP_BUTTON && ROWS>MIN_ROWS)  
		{	
			Etch_Sketch(ROWS--, COLUMNS);
 			_delay_ms(100);
		} 	 	

		if(~DOWN_BUTTON && ROWS<MAX_ROWS-1)  
		{	
			Etch_Sketch(ROWS++, COLUMNS);
 			_delay_ms(100);
		}		
}

int main(void)
{
 	Port_Init();
 	SPI_Init(); 
 	PWM_Init();

	LCD_Init();
 	LCD_Clear_LOW();
 	Interrupt_Init();

	while (TRUE)
	{	 	
		//Battery Low LED
   		addata=AD();
   		if ((addata<BAT_LOW))
   		{
    		BAT_LOW_LED(OFF);
   		}
   		else 
   		{
    		BAT_LOW_LED(ON);
   		} 

	}
}
