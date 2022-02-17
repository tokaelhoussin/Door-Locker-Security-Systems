/*
 * Control-ECV.c
 *
 *  Created on: Nov 5, 2021
 *      Author: as
 */

#include "uart.h"
#include "twi.h"
#include "Timer0.h"
#include "external_eeprom.h"
#include "dc_motor.h"
#include "buzzer.h"
#include "avr/io.h" /* To use the SREG Register */
#define F_CPU 8000000
#include "util/delay.h"

#define sec15 458
#define minute 1832
uint8 g_counter=0;
uint8 key_num,i=0,j=0,key_num2,saved=0,similar=0,check=0,flag=1,choose=0,choice=0,wrong=0,flag2=2,k=0,flag3=3;
void Timer0_callBack(void){
	g_counter++;
}
void save_password(void){
if(i<5){
	/*Receive LED number from the other device through the UART */
	key_num=UART_recieveByte();
	_delay_ms(30);
	EEPROM_writeByte(0x0311+i, key_num); /* Write keynum in the external EEPROM */
	_delay_ms(10);
	i++;
}
else{
	saved=1;
	i=0;
}
}
void choose_option(void){
	while(choice==0){
	    choice=UART_recieveByte();
	}
	choose=1;
}
void check_similarity(void){
	if(j<5){
		key_num=UART_recieveByte();
		_delay_ms(30);
		EEPROM_readByte(0x0311+j, &key_num2);  /* Read keynum from the external EEPROM */
		_delay_ms(10);
		j++;
		if(key_num==key_num2){
			similar++;
		}
	}
	else{
		if(similar!=5)
			wrong=1;
		j=0;
		check=1;
	}
}
int main(){
	/* Enable Global Interrupt I-Bit */
	SREG |= (1<<7);
	/* Create configuration structure for Timer0 driver */
	Timer0_ConfigType Timer0_Config = {F_CPU_1024,Normal};
	/* Set the Call back function pointer in the Timer driver */
	Timer0_setCallBack(Timer0_callBack);
	/* Initialize the TWI/I2C and UART and DcMotor Drivers  */
	TWI_ConfigType TWI_Config = {9600,1};//9600*10
	TWI_init(&TWI_Config);
	Uart_ConfigType Uart_Config = {Disabled,One,Eight,9600};
	UART_init(&Uart_Config);
	/* Enable interrupts by setting I-bit */
	SREG  |= (1<<7);
	DcMotor_Init();
    Buzzer_Init();
	while(1){
		if(saved==0){
			save_password();
		}
		else if(choose==0){
			choose_option();
		}
		else if(check==0){
			check_similarity();
		}
		else if(similar==5){
			if(choice==1){
				UART_sendByte(flag);
	      		_delay_ms(30);
	      		saved=0;
			    similar=0;
				choice=0;
				choose=0;
				check=0;
			}
			else if(choice==2){
			   UART_sendByte(flag);
	           _delay_ms(30);
			   DcMotor_Rotate(DC_MOTOR_CW);
			   _delay_ms(15000);
			   DcMotor_Rotate(DC_MOTOR_STOP);
			   _delay_ms(3000);
			   DcMotor_Rotate(DC_MOTOR_ACW);
			   _delay_ms(15000);
			   DcMotor_Rotate(DC_MOTOR_STOP);
			   choice=0;
			}
		}
		else if(wrong==1){
			Buzzer_on();
		    _delay_ms(15000);
		    Buzzer_off();
		    UART_sendByte(flag2);
		    _delay_ms(30);
		    wrong=0;
		    choose=0;
		    check=0;
		    similar=0;
		}
	}
}


