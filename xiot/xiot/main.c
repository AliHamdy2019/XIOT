/*=======================================================================================================================================
 *  PROJECT	    : Xoit
 *  Created on: 24 Jun 2018
 *  Author		: Ali hamdy
 *  Description :
 *	--> i applied the assignment on atemga16 Micro-controller
 *	--> instead of the serial monitor i used an lcd
 *	--> the switch is connected to interrupt zero
 *	--> the used lcd is 2x16
 *=======================================================================================================================================
*/
#define F_CPU 1000000UL /*1MHz Clock frequency*/
#include"macros.h"
#include"avr/io.h"
#include"avr/delay.h"
#include"std_types.h"
#include"lcd.h"
#include"external_interrupts.h"
#include"adc.h"
#include"timers.h"
uint8 LED_STATE= 0;
/* 1=> the led is on ,0=>the led is off*/
uint32 g_temp=0;
/*g_temp is the variable that contain the TEMP*/
g_tempCounter=0;
/*g_tempCounter is the counter for counting the 3 second*/
uint8 int_fix=0;
/*interrupt 0 is executed at the int the interrupt INI0_init function (i don't know why)
 * to fix this make the ISR do nothing at the first interrupt */
void mainScreen (void);
/*====================================================================================================================================
 *Function Name : mainScreen
 *Description   : this function is responsible for displaying the main screen,showing led state and temperature
 *Arguments     : none
 *Returns       : none
 *====================================================================================================================================*/
void pressedScreen (void);
/*====================================================================================================================================
 *Function Name : pressedScreen
 *Description   : this function is responsible for displaying the "Pressed" when the switch is pressed
 *Arguments     : none
 *Returns       : none
 *====================================================================================================================================*/
void switchAction (void);
/*====================================================================================================================================
 *Function Name : switchAction
 *Description   : this is function that is called whenever there's an external interrupt, the one that should turn the led on or off
 *Arguments     : none
 *Returns       : none
 *====================================================================================================================================*/
void tempUpdate (void);
/*====================================================================================================================================
 *Function Name : tempUpdate
 *Description   : this is function that is called whenever the timer finishes counting
 *Arguments     : none
 *Returns       : none
 *====================================================================================================================================*/
int main()
{
	SET_BIT(DDRB,0);
	PRESCALER_CS00=1;
	PRESCALER_CS01=0;
	PRESCALER_CS02=1;
	LCD_init();
	ADC_init();
	SET_BIT(SREG,7);
	INT0_init(switchAction);
	timer0_init_CTC_mode(tempUpdate,250);
	g_temp=ADC_readChannel(1);
	g_temp=(g_temp*150*5)/(1023*1.5);
	mainScreen();
	while(1)
	{
		int_fix=1;
	}
return 0;
}
void mainScreen()
{
	LCD_clearScreen();
	LCD_displayString("LED_STATE:");
	if(BIT_IS_SET(LED_STATE,0))
		{
			LCD_displayString("ON");
		}
	else
		{
			LCD_displayString("OFF");
		}
	LCD_displayStringRowColumn(1,0,"Temperature:");
	LCD_intgerToString(g_temp);
}
void pressedScreen ()
{
	LCD_clearScreen();
	LCD_displayString("     PRESSED");
	_delay_ms(500);
	LCD_clearScreen();
	mainScreen();
}
void switchAction ()
{
	if(int_fix==1)
	{
		TOGGLE_BIT(LED_STATE,0);
		TOGGLE_BIT(PORTB,0);
		pressedScreen();
	}
}
void tempUpdate ()
{
	g_tempCounter++;
	if(g_tempCounter==12)
	{
		g_tempCounter=0;
		/*here the function that read temp sensor current reading  save the reading  at g_temp */
		g_temp=ADC_readChannel(1);
		/* calculate the temp from the ADC value*/
		g_temp=(g_temp*150*5)/(1023*1.5);
		LCD_displayStringRowColumn(1,0,"Temperature:    ");
		LCD_goToRowColumn(1,12);
		LCD_intgerToString(g_temp);
	}
}
