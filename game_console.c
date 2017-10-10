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

#define INCREMENT		51


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

void PWN_init(void){
    
    LCD_BACKLIGHT_DIR(OUT);//direction of the port
    //need to modify TCCR0:Timer control register
    //01111010
    TCCR0 = (1<<WGM00) | (1<<COM01) | (1<<COM00) | (1<<WGM01) | (1<<CS01);
    //when oc1b

    OCR0 = BOTTOM;//set it to lowest
}

void PWM(void){
    if (A_BUTTON)
	{
		if(OCR0 + INCREMENT<=TOP)
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


void button_det(void){
					//Turn on the LED if UP_BUTTON is pressed
					//Turn on the LED if UP_BUTTON is pressed
		//if (UP_BUTTON)//get device status
		//{
			//BAT_LOW_LED(ON);	
		//} 	
		//else
		//{
		//	BAT_LOW_LED(OFF);
		//}
					//Turn on the LED if UP_BUTTON is pressed
		if (DOWN_BUTTON)//get device status
		{
			BAT_LOW_LED(ON);	
		} 	
		else
		{
			BAT_LOW_LED(OFF);
		}

		PWM();
		
		
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
	PWN_init();

	//try to turn on LCD backlight
	//LCD_BACKLIGHT_DIR(OUT);
	LCD_BACKLIGHT(OFF);

	BAT_LOW_LED_DIR(OUT);
	BAT_LOW_LED(OFF);
	
	while (TRUE)//Master loop always true so always loop
	{
		button_det();
		

	}


	
}
