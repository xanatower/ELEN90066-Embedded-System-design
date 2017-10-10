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


int main(void)
{
	/*pin init*/
	
	//BAT_LOW_LED(OFF); //Make sure it is off before changing direction
	//BAT_LOW_LED_DIR(OUT); //Set BATTERY LED I/Os as outputs.
	//UP_BUTTON_DIR(IN); //Set UP_BUTTON I/Os as input.


	
	//try to turn on LCD backlight
	LCD_BACKLIGHT_DIR(OUT);
	LCD_BACKLIGHT(OFF);

	BAT_LOW_LED_DIR(OUT);
	BAT_LOW_LED(ON);
	
	while (TRUE)//Master loop always true so always loop
	{

		//TRY TO DETECT BUTTON BY INTERUPT???



		//turn everything off
		
		/*//Turn on the LED if UP_BUTTON is pressed
		if (UP_BUTTON)
		{
			BAT_LOW_LED(ON);	
		} 	
		else
		{
			BAT_LOW_LED(OFF);
		}*/

	}

}
