/*
 * buzzer.h
 *
 *  Created on: Nov 7, 2021
 *      Author: as
 */

#ifndef BUZZER_H_
#define BUZZER_H_
#include "std_types.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
/* The Ports and Pins IDs for the buzzer pin */
#define Buzzer_PORT_ID   PORTD_ID

#define Buzzer_PIN_ID    PIN2_ID
/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum
{
	OFF,ON
}Buzzer_State;
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description :
 * Initialize the buzzer by:
 * 1. Setup the direction of the buzzer pin as output by send the request to GPIO driver.
 * 2. Turn off the buzzer at the beginning
 */
void Buzzer_Init(void);

/*
 * Description :
 * 1. Turn on the buzzer.
 */
void Buzzer_on(void);
/*
 * Description :
 * 1. Turn off the buzzer.
 */
void Buzzer_off(void);


#endif /* BUZZER_H_ */
