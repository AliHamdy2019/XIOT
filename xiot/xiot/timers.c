/*
 * PROJECT     : timers.c
 * Created on  : 23 Sep 2017
 * Author      : Ali hamdy
 * Description :
 * ------------------------------
 *  [1]-calculate the prescaler:| and use the variable names PRESCALER_CS(KN) k is the thimer number and n is the variable number
 * ------------------------------
 *  example: for timer2 the 3 variables are 1-PRESCALER_CS20
 *                                          2-PRESCALER_CS21
 *  ---------------------                   3-PRESCALER_CS22
 *  [2]choose the timer:| buy removing the comment
 *  ---------------------
 *  example:all the timers
 *            /*#define TIMER0*/
            /*#define TIMER1*/
             /*#define TIMER2*/
  /* to use timer1 make them
              #define TIMER0 (without the comment)
             /*#define TIMER1*/
             /*#define TIMER2*/
 /*----------------------
 /*  [3]choose the mode:| but removing the comment like above
  *  --------------------
  *  [4]the functions:|
  *  ------------------------------
  *  [A]timer(n)_init_normal_mode:|
  *  ------------------------------
  *  >takes 1 arguments - the name of application function that should run when an interrupt happens (what we want to right at the ISR)
  *  					  and this function should return void and take void
  *  >the function will initiate the timer and run the normal mode
  *  -----------------------------
  *  [B]timer(n)_CTC_normal_mode:|
  *  -----------------------------
  *  >takes 2 arguments 1-the name of application function that should run when an interrupt happens (what we want to right at the ISR)
  *  					  and this function should return void and take void
  *  					2-the compare value in range (0-255)
  *  >the function will initiate the timer and run he ctc mode
  *  -----------------------------------------
  *  [C]timer(n)_CTC_normal_USING_OC(n)_mode:|
  *  -----------------------------------------
  *  >takes 1 arguments - the compare value in range (0-255)
  *  >the function will initiate the timer,OC(n) and  run he ctc mode
  *  >we should choose what we want with OC(n)
  *  		1-toggle
  *  		2-clear
  *  		3-set
  *  similar to choosing the mode and the timer
  *  ----------------------
  *  [D]timer(n)_PMW_mode:|
  *  ----------------------
  *  >takes 1 arguments - the duty cycle of the wave it takes the percentage (numbers from 1 to 100)
  *  >the function will initiate the timer,OC(n) and  run he FAST PMW mode
  *  >we should choose what we want with OC(n)
  *  		1-NON_INVERTING
  *  		2-INVERTING
  *  similar to choosing the mode and the timer
  *  -------------------
  *  [E]timer(n)_stop: |
  *  -------------------
  *  >stop the timer by stoping the prescaler
  *  >takes void and return void
 */
#include"timers.h"


/*TIMER0*/
#ifdef TIMER0
unsigned char PRESCALER_CS00=1;
unsigned char PRESCALER_CS01=0;
unsigned char PRESCALER_CS02=1;
/*====================================================================================================================================*/
/*TIMER0 Normal mode*/
/* TIMER0 normal mode: to use it call the function timer0_init_normal_mode and give it the name of the function u want to executed
 * when an interrupt occurs
 * this function should return void and take void */
#ifdef TIMER0_NORMAL
static void (* FunctionName__NormalMode_TIMER0)(void);
void timer0_init_normal_mode(void(*ptr)(void))
{
	/* CALL BACk concept : FunctionNmae_NormalMode will hold the name of the app function we want to executed when an interrupt
	 * occurs  (ISR CODE)*/
	FunctionName__NormalMode_TIMER0=ptr;

	TCNT0 = 0; //timer initial value
	TIMSK |= (1<<TOIE0); //enable overflow interrupt
	/* Configure the timer control register
	 * 1. Non PWM mode FOC0=1
	 * 2. Normal Mode WGM01=0 & WGM00=0
	 * 3. Normal Mode COM00=0 & COM01=0
	 * 4. clock = F_CPU/N  the default is 1024 (CS00=1 CS01=0 CS02=1) */
	TCCR0 = (1<<FOC0);
	TCCR0|= (PRESCALER_CS00<<CS00)|(PRESCALER_CS01<<CS01)|(PRESCALER_CS02<<CS02);

}
ISR(TIMER0_OVF_vect)
{
	FunctionName__NormalMode_TIMER0();
}
#endif
/*===================================================================================================================================*/
/* TIMER0 compare match mode: to use it call the function timer0_init_CTC_mode and give it the name of the function u want to executed
 * when an interrupt occurs
 * this function should return void and take void  */
#ifdef TIMER0_CTC
static void (* FunctionName__CTCMode_TIMER0)(void);
void timer0_init_CTC_mode(void (* ptr)(void),unsigned char tick)
{
	/* CALL BACk concept : FunctionNmae_NormalMode will hold the name of the app function we want to executed when an interrupt
	 * occurs  (ISR CODE)*/
	FunctionName__CTCMode_TIMER0=ptr;
	TCNT0 = 0; //timer initial value
	OCR0  = tick; //compare value
	TIMSK |= (1<<OCIE0); //enable compare interrupt
	/* Configure timer0 control register
	 * 1. Non PWM mode FOC0=1
	 * 2. CTC Mode WGM01=1 & WGM00=0
	 * 3. No need for OC0 in this example so COM00=0 & COM01=0
	 * 4. clock = F_CPU/N  the default is 1024 (CS00=1 CS01=0 CS02=1)
	 */

	TCCR0 = (1<<FOC0) | (1<<WGM01) ;
	TCCR0 |= (PRESCALER_CS00 <<CS00)|(PRESCALER_CS01<<CS01)|(PRESCALER_CS02<<CS02);
}
ISR(TIMER0_COMP_vect)
{
	FunctionName__CTCMode_TIMER0();
}
#endif
/*====================================================================================================================================*/
/* TIMER0 compare match mode using OC0 : call this function and OC0 will work  */
#ifdef TIMER0_CTC_USING_OC0
void Timer0_CTC_USING_OC0_Init(unsigned char tick)
{
	TCNT0 = 0; // initial value 0
	OCR0 = tick; //compare value
	DDRB  = DDRB | (1<<PB3); //set OC0 as output pin --> pin where the PWM signal is generated from MC
	/* Configure timer control register
	 * 1. Non PWM mode FOC0=1 */
	  TCCR0 = (1<<FOC20);
    /* 2. CTC Mode WGM01=1 & WGM00=0*/
	  TCCR0|= (1<<WGM01);
	/* 3. what happens to OC0*/
	#ifdef TOGGLE_OC0
	  TCCR0|=(1<<COM00);
	#endif
	#ifdef CLEAR_OC0
	  TCCR0|=(1<<COM01);
	#endif
	#ifdef SET_OC0
	  TCCR0|=(1<<COM01)|(1<<COM00);
	#endif
    /* 4. clock = F_CPU/N  the default is 1024 (CS00=1 CS01=0 CS02=1) */
	TCCR0 |= (PRESCALER_CS00 <<CS00)|(PRESCALER_CS01<<CS01)|(PRESCALER_CS02<<CS02);
}
#endif
/*====================================================================================================================================*/
#ifdef TIMER0_PMW
void Timer0_PWM_Init(unsigned char set_duty_cycle)
{
	TCNT0 = 0; // Timer initial value
	OCR0  = set_duty_cycle*(256/100); //compare value
	DDRB  = DDRB | (1<<PB3); //set OC0 as output pin --> pin where the PWM signal is generated from MC
	/* Configure timer control register
	 * 1. Fast PWM mode FOC0=0 */
    /* 2. Fast PWM Mode WGM01=1 & WGM00=1*/
	TCCR0 = (1<<WGM00) | (1<<WGM01);
	 /*the mode inverting or non inverting*/
	#ifdef NON_INVERTING_Mode_OC0
	TCCR0 |= (1<<COM01);
	#endif
	#ifdef INVERTING_Mode_OC0
	TCCR0 |= (1<<COM01)|(1<<COM00);
	#endif
	 /* 4. clock = F_CPU/N  the default is 1024 (CS20=1 CS21=0 CS22=1) */
	TCCR0 |= (PRESCALER_CS00 <<CS00)|(PRESCALER_CS01<<CS01)|(PRESCALER_CS02<<CS02);
}
#endif
/*====================================================================================================================================*/
void Timer0_stop(void)
{
	//to stop the timer we stop the clock
	TCCR0 &=~(0x07);
}
/*====================================================================================================================================*/
#endif
/*====================================================================================================================================*/
/*====================================================================================================================================*/
#ifdef TIMER1
unsigned char PRESCALER_CS10=1
unsigned char PRESCALER_CS11=0
unsigned char PRESCALER_CS12=1
/*====================================================================================================================================*/

#endif
/*====================================================================================================================================*/
/*====================================================================================================================================*/
#ifdef TIMER2
unsigned char PRESCALER_CS20=1;
unsigned char PRESCALER_CS21=1;
unsigned char PRESCALER_CS22=1;
/*====================================================================================================================================*/
/* TIMER2 normal mode: to use it call the function timer2_init_normal_mode and give it the name of the function u want to executed
 * when an interrupt occurs
 * this function should return void and take void */
#ifdef TIMER2_NORMAL
static void (* FunctionName__NormalMode_TIMER2)(void);
void timer2_init_normal_mode(void (*ptr)(void))
{
	/* CALL BACk concept : FunctionNmae_NormalMode will hold the name of the app function we want to executed when an interrupt
	 * occurs  (ISR CODE)*/
	FunctionName__NormalMode_TIMER2=ptr;

	TCNT2 = 0; //timer initial value
	TIMSK |= (1<<TOIE2); //enable overflow interrupt
	/* Configure the timer control register
	 * 1. Non PWM mode FOC2=1
	 * 2. Normal Mode WGM21=0 & WGM20=0
	 * 3. Normal Mode COM20=0 & COM21=0
	 * 4. clock = F_CPU/N  the default is 1024 (CS20=1 CS21=1 CS22=1)*/
	TCCR2 = (1<<FOC2);
	TCCR2|= (PRESCALER_CS20 <<CS20)|(PRESCALER_CS21<<21)|(PRESCALER_CS22<<CS22);
}
ISR(TIMER2_OVF_vect)
{
	FunctionName__NormalMode_TIMER2();
}
#endif
/*====================================================================================================================================*/
/* TIMER2 compare match mode: to use it call the function timer2_init_CTC_mode and give it the name of the function u want to executed
 * when an interrupt occurs
 * this function should return void and take void  */
#ifdef TIMER2_CTC
static void (* FunctionName__CTCMode_TIMER2)(void);
void timer2_init_CTC_mode(void (*ptr)(void),unsigned char tick)
{
	/* CALL BACk concept : FunctionNmae_NormalMode will hold the name of the app function we want to executed when an interrupt
	 * occurs  (ISR CODE)*/
	FunctionName__CTCMode_TIMER2=ptr;
	TCNT2 = 0; //timer initial value
	OCR2  = tick; //compare value
	TIMSK |= (1<<OCIE2); //enable compare interrupt
	/* Configure timer control register
	 * 1. Non PWM mode FOC2=1
	 * 2. CTC Mode WGM21=1 & WGM20=0
	 * 3. No need for OC2 in this example so COM20=0 & COM21=0
	 * 4. clock = F_CPU/N  the default is 1024 (CS20=1 CS21=1 CS22=1)
	 */
	TCCR2 = (1<<FOC2) | (1<<WGM21) ;
	TCCR2|= (PRESCALER_CS20 <<CS20)|(PRESCALER_CS21<<CS21)|(PRESCALER_CS22<<CS22);
}
ISR(TIMER2_COMP_vect)
{
	FunctionName__CTCMode_TIMER2();
}
#endif
/*====================================================================================================================================*/
/* TIMER2 compare match mode using OC2 : call this function and OC2 will work  */
#ifdef TIMER2_CTC_USING_OC2
void Timer2_CTC_USING_OC2_Init(unsigned char tick)
{
	TCNT2 = 0; // initial value 0
	OCR2 = tick; //compare value
	DDRD = DDRD | (1<<PD7); // OC2 Pin as output pin
	/* Configure timer control register
	 * 1. Non PWM mode FOC2=1 */
	  TCCR2 = (1<<FOC2);
    /* 2. CTC Mode WGM21=1 & WGM20=0*/
	  TCCR2|= (1<<WGM21);
	/* 3. what happens to OC2*/
	#ifdef TOGGLE_OC2
	  TCCR2|=(1<<COM20);
	#endif
	#ifdef CLEAR_OC2
	  TCCR2|=(1<<COM21);
	#endif
	#ifdef SET_OC2
	  TCCR2|=(1<<COM21)|(1<<COM20);
	#endif
    /* 4. clock = F_CPU/N  the default is 1024 (CS20=1 CS21=1 CS22=1) */
	  TCCR2|= (PRESCALER_CS20 <<CS20)|(PRESCALER_CS21<<21)|(PRESCALER_CS22<<CS22);
}
#endif
/*====================================================================================================================================*/
#ifdef TIMER2_PMW
void Timer2_PWM_Init(unsigned char set_duty_cycle)
{
	TCNT2 = 0; // Timer initial value
	OCR2  = set_duty_cycle*(256/100); //compare value
	DDRD = DDRD | (1<<PD7); // OC2 Pin as output pin
	/* Configure timer control register
	 * 1. Fast PWM mode FOC2=0 */
    /* 2. Fast PWM Mode WGM21=1 & WGM20=1*/
	TCCR2 = (1<<WGM00) | (1<<WGM01);
	 /*the mode inverting or non inverting*/
	#ifdef NON_INVERTING_Mode_OC2
	TCCR2 |= (1<<COM21);
	#endif
	#ifdef INVERTING_Mode_OC2
	TCCR2 |= (1<<COM21)|(1<<COM20);
	#endif
	 /* 4. clock = F_CPU/N  the default is 1024 (CS20=1 CS21=1 CS22=1) */
	TCCR2|= (PRESCALER_CS20 <<CS20)|(PRESCALER_CS21<<21)|(PRESCALER_CS22<<CS22);
}
#endif
/*====================================================================================================================================*/
void Timer2_stop(void)
{
	//to stop the timer we stop the clock
	TCCR2 &=~(0x07);
}
/*====================================================================================================================================*/
#endif
