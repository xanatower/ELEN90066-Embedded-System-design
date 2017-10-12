#define INCREMENT 51

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
	if (ACT3_BUTTON)
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

/*
//SPI Send byte function GIVEN IN LECTURE
byte LCD_data_tx(byte tx_byte) //Sends a data byte
{
	byte tx_processed;
	byte tx_mask = 0x80;
	LCD_CHIP_SELECT;
	LCD_DATA;
	while (tx_mask != 0x00)
	{
		tx_processed = tx_byte & tx_mask;
		SCK_SET_HIGH;
		if (tx_processed)
			MOSI_SET_HIGH;
		else
			MOSI_SET_LOW;
		SCK_SET_LOW;
		tx_mask >>= 1;
	}
	SCK_SET_HIGH;
	LCD_CHIP_DESELECT;
	return (TRUE);
}*/



//From datasheet P138

void SPI_MasterInit(void)
{	

	//P140

	/* Set MOSI and SCK output, all others input */
	DDR_SPI = (1 << DD_MOSI) | (1 << DD_SCK);
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
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
	LCD_CD(LCD_type); //Instruction: Command / transfer Data
	LCD_CS (HIGH); //select this chip

	//cData is the input data that will be transmitted

	//SPI Data Register SPDR

	/* Start transmission */
	SPDR = cData;

	/* Wait for transmission complete */
	while (!(SPSR & (1 << SPIF)));
	LCD_CS(LOW); //deselect this chip

}



//return byte
byte LCD_initialise(void)
{	
	//initialise MCU pin
	LCD_CS(LOW); //Chip Deselect
	LCD_CS_DIR(OUT);
	
	LCD_CD_DIR(OUT); 
	
	LCD_RST_DIR(OUT);
	LCD_RST(HIGH);
	_delay_ms(10);
	
	LCD_RST(LOW);
	_delay_ms(10);

	LCD_TX(CMD, 0x40); //Display start line 0
	LCD_TX(CMD, 0xA1); //SEG reverse
	LCD_TX(CMD, 0xC0); //Normal COM0~COM63
	LCD_TX(CMD, 0xA4); //Disable -> Set All Pixel to ON
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

	return (TRUE);
}