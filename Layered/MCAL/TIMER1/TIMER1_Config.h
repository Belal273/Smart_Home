/*
 * TIMER1_Config.h
 *
 *  Created on: Mar 29, 2023
 *      Author: dell
 */

#ifndef TIMER1_CONFIG_H_
#define TIMER1_CONFIG_H_


#define TIMER1_MODE         CTC_MODE
//Choose PRESCALER Options (1,8,64,256,1024) and use #if not switch case
#define TIMER1_PRESCALER               8
#define TIMER1_CLK                     8 //result will be in micro sec
//#define TIMER1_CLK                     800000UL
#define TIMER1_RESOLUTION              256

#define PWM1_MODE 					 FAST_PWM_MODE
#define COMPARE_OUTPUT_MATCH         NON_INVERTING


#define NON_INVERTING       			 0
#define INVERTING       				 1

//#define TIMER1_CTC_VALUE               200

#define  NORMAL_MODE                   0
#define  CTC_MODE                      1
#define  PHASE_CORRECT_PWM_MODE        2
#define  FAST_PWM_MODE                 3

#endif /* MCAL_TIMER1_TIMER1_CONFIG_H_ */
