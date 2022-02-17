/*
 * buzzer.c
 *
 *  Created on: Nov 7, 2021
 *      Author: as
 */

#include "buzzer.h"
#include "gpio.h"

/*
 * Description :
 * Initialize the buzzer by:
 * 1. Setup the direction of the buzzer pin as output by send the request to GPIO driver.
 * 2. Turn off the buzzer at the beginning
 */
void Buzzer_Init(void)
{
	/* Setup the buzzer pin as output pins */
	GPIO_setupPinDirection(Buzzer_PORT_ID,Buzzer_PIN_ID,PIN_OUTPUT);

	/* buzzer is stopped at the beginning */
	GPIO_writePin(Buzzer_PORT_ID,Buzzer_PIN_ID,LOGIC_LOW);
}
/*
 * Description :
 * 1. Turn on the buzzer.
 */
void Buzzer_on(void){


		GPIO_writePin(Buzzer_PORT_ID,Buzzer_PIN_ID,LOGIC_HIGH);




}
/*
 * Description :
 * 1. Turn off the buzzer.
 */
void Buzzer_off(void){

	GPIO_writePin(Buzzer_PORT_ID,Buzzer_PIN_ID,LOGIC_LOW);
}
