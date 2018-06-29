/*
 * 	PROJECT	    : ADC
 *  Created on	: 23 Sep 2017
 *  Author		: Ali hamdy
 *  Description : ATMEGA16 ADC library
 */

#ifndef TEMP_SENSOR_EXAMPLE_ADC_H_
#define TEMP_SENSOR_EXAMPLE_ADC_H_

#include "std_types.h"
#include "avr/io.h"
#include "macros.h"

/*
 * Description :
 * Function responsible for initialize the ADC driver.
 */
void ADC_init(void);

/*
 * Description :
 * Function responsible for read analog data from a certain ADC channel
 * and convert it to digital using the ADC driver.
 */
uint32 ADC_readChannel(uint8 channel_num);

#endif /* TEMP_SENSOR_EXAMPLE_ADC_H_ */
