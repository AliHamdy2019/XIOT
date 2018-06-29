/*
 * 	PROJECT	    : timers.h
 *  Created on	: 23 Sep 2017
 *  Author		: Ali hamdy
 */

#include "std_types.h"
#include "macros.h"
#include "avr/io.h"
#include "avr/interrupt.h"
#ifndef TIMERS_H_
#define TIMERS_H_
/* choose which timer and which mode u want */
#define TIMER0
/*#define TIMER1*/
#define TIMER2
/*===================================================================================================================================*/
/* prescaler values
0 0 0 No clock source (Timer/Counter stopped).
0 0 1 clkI/O/(No prescaling)
0 1 0 clkI/O/8 (From prescaler)
0 1 1 clkI/O/64 (From prescaler)
1 0 0 clkI/O/256 (From prescaler)
1 0 1 clkI/O/1024 (From prescaler)
1 1 0 External clock source on T0 pin. Clock on falling edge.
1 1 1 External clock source on T0 pin. Clock on rising edge  */
/*=====================================================================================================================================*/
#ifdef TIMER0
/*************************/
extern unsigned char PRESCALER_CS00;
extern unsigned char PRESCALER_CS01;
extern unsigned char PRESCALER_CS02;
void Timer0_stop(void);
/*TIMER0_Modes*/
/*#define TIMER0_NORMAL*/
#ifdef TIMER0_NORMAL
void timer0_init_normal_mode(void (*ptr)(void));
#endif
/*************************/
#define TIMER0_CTC
#ifdef TIMER0_CTC
void timer0_init_CTC_mode(void (*ptr)(void),unsigned char tick);
#endif
/*************************/
/*#define TIMER0_CTC_USING_OC0*/
#ifdef TIMER0_CTC_USING_OC0
void Timer0_CTC_USING_OC0_Init(unsigned char tick);
/*choose what do u want with with OC0 */
#define TOGGLE_OC0
#define CLEAR_OC0
#define SET_OC0
#endif
/*************************/
/*#define TIMER0_PMW*/
#ifdef TIMER0_PMW
void Timer0_PWM_Init(unsigned char set_duty_cycle);
/*choose what do u want with with OCR */
#define NON_INVERTING_Mode_OC0
/*#define INVERTING_Mode_OC0*/
#endif
/*************************/
#endif
/*=====================================================================================================================================*/
#ifdef TIMER1
/*************************/
extern unsigned char PRESCALER_CS10;
extern unsigned char PRESCALER_CS11;
extern unsigned char PRESCALER_CS12;
void Timer1_stop(void);
/*TIMER1_Modes*/
/*#define TIMER1_NORMAL*/
#ifdef TIMER1_NORMAL
void timer1_init_normal_mode(void (*ptr)(void));
#endif
/*************************/
/*#define TIMER1_CTC*/
#ifdef TIMER1_CTC
void timer1_init_CTC_mode(void (*ptr)(void),unsigned char tick);
#endif
/*************************/
/*#define TIMER1_CTC_USING_OC1*/
#ifdef TIMER1_CTC_USING_OC1
void Timer1_CTC_USING_OC1_Init(unsigned char tick);
/*choose what do u want with with OC1 */
#define TOGGLE_OC1
#define CLEAR_OC1
#define SET_OC1
#endif
/*************************/
/*#define TIMER1_PMW*/
#ifdef TIMER1_PMW
void Timer1_PWM_Init(unsigned char set_duty_cycle);
/*choose what do u want with with OCR */
#define NON_INVERTING_Mode_OC1
#define INVERTING_Mode_OC1
#endif
/*************************/
#endif
/*=====================================================================================================================================*/
#ifdef TIMER2
/*************************/
extern unsigned char PRESCALER_CS20;
extern unsigned char PRESCALER_CS21;
extern unsigned char PRESCALER_CS22;
void Timer2_stop(void);
/*TIMER2_Modes*/
/*#define TIMER2_NORMAL*/
#ifdef TIMER2_NORMAL
void timer2_init_normal_mode(void (*ptr)(void));
#endif
/*************************/
#define TIMER2_CTC
#ifdef TIMER2_CTC
void timer2_init_CTC_mode(void (*ptr)(void),unsigned char tick);
#endif
/*************************/
/*#define TIMER2_CTC_USING_OC2*/
#ifdef TIMER2_CTC_USING_OC2
void Timer2_CTC_USING_OC2_Init(unsigned char tick);
/*choose what do u want with with OC2 */
#define TOGGLE_OC2
#define CLEAR_OC2
#define SET_OC2
#endif
/*************************/
/*#define TIMER2_PMW*/
#ifdef TIMER2_PMW
void Timer2_PWM_Init(unsigned char set_duty_cycle);
/*choose what do u want with with OCR */
#define NON_INVERTING_Mode_OC2
/*#define INVERTING_Mode_OC2*/
#endif
/*************************/
#endif
/*=====================================================================================================================================*/
#endif /* TIMERS_H_ */

