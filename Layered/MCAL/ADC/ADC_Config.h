/*
 * ADC_Config.h
 *
 *  Created on: Mar 16, 2023
 *      Author: dell
 */

#ifndef MCAL_ADC_ADC_CONFIG_H_
#define MCAL_ADC_ADC_CONFIG_H_

/*You Can choose between : { ADC_INTERNAL_2_56v/ ADC_INTERNAL_AVCC /ADC_EXTERNAL}  */
#define ADC_VREF   			 ADC_EXTERNAL
#define ADC_AJUST  			 ADC_RIGHT
#define ADC_PRESCALAR   	 ADC_PRESCALAR_128

#define ADC_PRESCALAR_2          0
#define ADC_PRESCALAR_4          1
#define ADC_PRESCALAR_8          2
#define ADC_PRESCALAR_16         3
#define ADC_PRESCALAR_32         4
#define ADC_PRESCALAR_64         5
#define ADC_PRESCALAR_128        6

#define ADC_RIGHT   0
#define ADC_LEFT    1


//#define does not consume memory
#define ADC_INTERNAL_2_56v  0
#define ADC_INTERNAL_AVCC   1
#define ADC_EXTERNAL        2

//enum always takes 4 bytes from memory
/*
enum ADC_VREF_Options
{
	ADC_INTERNAL_2_56v,
	ADC_INTERNAL_AVCC,
	ADC_EXTERNAL
};
*/
#endif /* MCAL_ADC_ADC_CONFIG_H_ */
