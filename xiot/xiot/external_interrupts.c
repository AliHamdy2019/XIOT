/*
 * 	PROJECT	    : external_interrupts
 *  Created on	: 23 Sep 2017
 *  Author		: Ali hamdy
 *  Description : external interrupt library
 */

#include "external_interrupts.h"
/*====================================================TNTERRUPT0============================================================*/
#ifdef INT0_enable
static void (*functionName_INT0)(void);
static uint8 SREG_STATE=0;//0 I bit=0 ,1 I bit 1
void INT0_init(void(*ptr)(void))
{
	functionName_INT0=ptr;
	DDRD  &= (~(1<<PD2));               // Configure INT0/PD2 as input pin
	GICR  |= (1<<INT0);                 // Enable external interrupt pin INT0
	#ifdef INT0_RISING_EDGE
	MCUCR |= (1<<ISC00) | (1<<ISC01);   // Trigger INT0 with the raising edge
	#endif
	#ifdef INT0_FAILLING_EDGE          // Trigger INT0 with the falling edge
	MCUCR |= (1<<ISC01);
	MCUCR &= ~(1<<ISC00);
	#endif
}
ISR(INT0_vect)
{
	functionName_INT0();
}
#endif
/*==========================================================================================================================*/
/*====================================================TNTERRUPT1============================================================*/
#ifdef INT1_enable
static void (*functionName_INT1)(void)	;
void INT1_init(void(*ptr)(void))
{
	functionName_INT1=ptr;
	DDRD  &= (~(1<<PD3));  // Configure INT1/PD3 as input pin
	PORTD |= (1<<PD3);     // Enable the internal pull up resistor at PD3 pin
	GICR  |= (1<<INT1);    // Enable external interrupt pin INT1
	#ifdef INT1_RISING_EDGE
	MCUCR |= (1<<ISC10) | (1<<ISC11);   // Trigger INT1 with the raising edge
	#endif
	#ifdef INT1_FAILLING_EDGE          // Trigger INT1 with the falling edge
	MCUCR |= (1<<ISC11);
	MCUCR &= ~(1<<ISC10);
	#endif
}
ISR(INT1_vect)
{
	functionName_INT1();
}
#endif
/*==========================================================================================================================*/
/*====================================================TNTERRUPT2============================================================*/
#ifdef INT2_enable
static void (*functionName_INT2)(void)	;
void INT2_init(void(*ptr)(void))
{
	functionName_INT2=ptr;
	#ifdef INT2_RISING_EDGE
	MCUCSR|=(1<<INT2);
	#endif
	#ifdef INT2_FAILING_EDGE
	MCUCSR&=~(1<<ISC2);//-ve edge
	#endif
	GICR|=(1<<INT2);//module interrupt enable
	DDRB&=~(1<<PB2);
}
ISR(INT2_vect)
{
	functionName_INT2();
}
#endif
/*==========================================================================================================================*/
