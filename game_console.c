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


void button_init(void){
	
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

void button_det(void){
					//Turn on the LED if UP_BUTTON is pressed
					//Turn on the LED if UP_BUTTON is pressed
		if (UP_BUTTON)//get device status
		{
			BAT_LOW_LED(ON);	
		} 	
		else
		{
			BAT_LOW_LED(OFF);
		}
					//Turn on the LED if UP_BUTTON is pressed
		if (DOWN_BUTTON)//get device status
		{
			BAT_LOW_LED(ON);	
		} 	
		else
		{
			BAT_LOW_LED(OFF);
		}

		if (A_BUTTON)//get device status
		{
			BAT_LOW_LED(ON);	
		} 	
		else
		{
			BAT_LOW_LED(OFF);
		}
		
		
		//Turn on the LED if UP_BUTTON is pressed
		if (B_BUTTON)//get device status
		{
			BAT_LOW_LED(ON);	
		} 	
		else
		{
			BAT_LOW_LED(OFF);
		}

}

int main(void)
{
	/*pin init*/
	button_init();//initialise the buttons and pull up

	//try to turn on LCD backlight
	LCD_BACKLIGHT_DIR(OUT);
	LCD_BACKLIGHT(OFF);

	BAT_LOW_LED_DIR(OUT);
	BAT_LOW_LED(OFF);
	
	while (TRUE)//Master loop always true so always loop
	{
		button_det();
	

	}


	
}
