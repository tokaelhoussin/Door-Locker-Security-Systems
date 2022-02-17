/*
 * Timer0.c
 *
 *  Created on: Nov 4, 2021
 *      Author: as
 */


#include "Timer0.h"
#include "common_macros.h"
#include <avr/io.h> /* To use Timer0 Registers */
#include <avr/interrupt.h> /* For Timer ISR */
/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/
ISR(TIMER0_OVF_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}
ISR(TIMER0_COMP_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

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
void Timer0_Init(const Timer0_ConfigType * Config_Ptr,unsigned char tick){
	if(Config_Ptr->type==Normal){
		TCNT0 = 0; //Set Timer initial value to 0
		TIMSK |= (1<<TOIE0); // Enable Timer0 Overflow Interrupt
		/*
			 * insert the required clock value in the first three bits (CS00, CS01 and CS02)
			 * of TCCR0 Register
	    */
		TCCR0 = (TCCR0 & 0xF8) | (Config_Ptr->clock);
		/* Configure the timer control register
			* 1. Non PWM mode FOC0=1
			* 2. Normal Mode WGM01=0 & WGM00=0
			* 3. Normal Mode COM00=0 & COM01=0
			* 4. Configure clock
	    */
		TCCR0 = (TCCR0 & 0xBF) | (1<<FOC0);
	}
	else if(Config_Ptr->type==CTC){
		TCNT0 = 0; //Set Timer initial value to 0
		OCR0  = tick; // Set Compare Value
		TIMSK |= (1<<OCIE0); // Enable Timer0 Compare Interrupt
		/*
			* insert the required clock value in the first three bits (CS00, CS01 and CS02)
			* of TCCR0 Register
	    */
		TCCR0 = (TCCR0 & 0xF8) | (Config_Ptr->clock);
		/* Configure timer0 control register
			* 1. Non PWM mode FOC0=1
			* 2. CTC Mode WGM01=1 & WGM00=0
			* 3. COM00=0 & COM01=0
			* 4. Configure clock
	    */
		TCCR0 = (TCCR0 & 0xBF) | (1<<FOC0) | (1<<WGM01);
	}
}
/*
 * Description:
 * stop the timer
 */
void Timer0_DeInit(void)
{
	/*clear all the timer registers*/
	TCCR0=0;
	TCNT0=0;
	OCR0=0;
    /*Disable the interrupts*/
	CLEAR_BIT(TIMSK,OCIE0);
	CLEAR_BIT(TIMSK,TOIE0);
}
/*
 * Description: Function to set the Call Back function address.
 */
void Timer0_setCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr = a_ptr;
}
