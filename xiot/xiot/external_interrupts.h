/*
 * 	PROJECT	    : external_interrupts
 *  Created on	: 23 Sep 2017
 *  Author		: Ali hamdy
 *  Description : external interrupt library
 */

#ifndef EXTERNAL_INTERRPUTS_H_
#define EXTERNAL_INTERRPUTS_H_

#include "std_types.h"
#include "macros.h"
#include "avr/io.h"
#include<avr/interrupt.h>


#define INT0_enable
/*====================================================TNTERRUPT0============================================================*/
#ifdef INT0_enable
#define INT0_RISING_EDGE
/*#define INT0_FAILLING_EDGE*/
void INT0_init(void(*ptr)(void));
#endif
/*==========================================================================================================================*/
/*#define INT1_enable*/
/*====================================================TNTERRUPT1============================================================*/
#ifdef INT1_enable
#define INT1_RISING_EDGE
/*#define INT1_FAILLING_EDGE*/
void INT1_init(void (*ptr)(void));
#endif
/*==========================================================================================================================*/
/*#define INT2_enable*/
/*====================================================TNTERRUPT2============================================================*/
#ifdef INT2_enable
#define INT2_RISING_EDGE
/*#define INT2-FAILLING_EDGE*/
void INT2_init(void(*ptr)(void));
#endif
/*==========================================================================================================================*/

#endif /* EXTERNAL_INTERRPUTS_H_ */
