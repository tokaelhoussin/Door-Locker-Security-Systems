/*
 * Timer0.h
 *
 *  Created on: Nov 4, 2021
 *      Author: as
 */

#ifndef TIMER0_H_
#define TIMER0_H_

#include "std_types.h"
/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum
{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024
}Timer0_Clock;
typedef enum
{
	Normal,CTC
}Timer0_Type;
typedef struct
{
	Timer0_Clock clock;
	Timer0_Type type;
}Timer0_ConfigType;
/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
/*
 * Description :
 * 1. Set the required clock.
 * 2. put initial timer counter=0.
 * 3. Set the required type.
 * 4. configure rest of the registers depends on the type.
 */
void Timer0_Init(const Timer0_ConfigType * Config_Ptr,unsigned char tick);
/*
 * Description:
 * stop the timer
 */
void Timer0_DeInit(void);
/*
 * Description: Function to set the Call Back function address.
 */
void Timer0_setCallBack(void(*a_ptr)(void));
#endif /* TIMER0_H_ */
