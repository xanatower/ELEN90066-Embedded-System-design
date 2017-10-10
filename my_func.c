#define INCREMENT		51

void PWN_init(void){
    
    LCD_BACKLIGHT_DIR(OUT);//direction of the port
    //need to modify TCCR0:Timer control register
    //01111010
    TCCR0 = (1<<WGM00) | (1<<COM01) | (1<<COM00) | (1<<WGM01) | (1<<CS01);
    //when oc1b

    OCR0 = BOTTOM;//set it to lowest
}

void PWM(void){
    if (ACT3_BUTTON)
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