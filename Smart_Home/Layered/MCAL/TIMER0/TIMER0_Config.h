/*
 * TIMER0_Config.h
 *
 *  Created on: Mar 17, 2023
 *      Author: dell
 */

#ifndef MCAL_TIMER0_TIMER0_CONFIG_H_
#define MCAL_TIMER0_TIMER0_CONFIG_H_


#define TIMER0_MODE         CTC_MODE
//Choose PRESCALER Options (1,8,64,256,1024) and use #if not switch case
#define TIMER0_PRESCALER               8
#define TIMER0_CLK                     8 //result will be in micro sec
//#define TIMER0_CLK                     800000UL
#define TIMER0_RESOLUTION              256

//#define TIMER0_CTC_VALUE               200

#define  NORMAL_MODE                   0
#define  CTC_MODE                      1
#define  PHASE_CORRECT_PWM_MODE        2
#define  FAST_PWM_MODE                 3

#endif /* MCAL_TIMER0_TIMER0_CONFIG_H_ */
