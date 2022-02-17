/*
 * HMI-ECV.c
 *
 *  Created on: Nov 5, 2021
 *      Author: as
 */


#include "uart.h"
#include "Timer0.h"
#include "keypad.h"
#include "lcd.h"
#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h> /* For the delay functions */


#define sec15 458
#define minute 1832
uint8 g_counter=0;
uint8 key_num[10];
uint8 key_num2[10];
uint8 key_num3[10];
uint8 pass1=0;
uint8 pass2=0;
uint8 i=0,j=0,k=0,flag=0,created=0,entered=0,show=0,change=1,unlock=2,confirmed=0,wrong=0;
void Timer0_callBack(void){
	g_counter++;
}
void create_password(void){
	if(key_num[pass1]!=13&&flag==0){
			/* Get the pressed button from keypad */
			key_num[pass1] = KEYPAD_getPressedKey();
			_delay_ms(500);
			if(key_num[pass1]!=13){
				 LCD_displayCharacter('*');
				 pass1++;
			}
		 //   _delay_ms(500);
			}
	else if(key_num2[pass2]!=13)
	{
			flag=1;
			LCD_displayStringRowColumn(0,0,"Reenter Password");
			LCD_moveCursor(1,pass2);
			/* Get the pressed button from keypad */
			key_num2[pass2] = KEYPAD_getPressedKey();
			_delay_ms(500);
			if(key_num[pass2]!=13){
		    LCD_displayCharacter('*');
			pass2++;
			}
			//_delay_ms(500);
	}
	else{
		for(i=0, j=0;i<pass1;i++){
			if(key_num[i]==key_num2[j]){
					j++;
		}
		}
		if(i==j){/*if true send it by UART to save in EEPROM*/
			for(i=0;i<pass1;i++){
					UART_sendByte(key_num[i]);
					_delay_ms(30);
			}
			created=1;
	   }
		else{/*if not repeat the first step*/
						LCD_clearScreen();
						LCD_displayString("Enter Password: ");
						LCD_moveCursor(1,0);
						key_num[10]=0;
						key_num2[10]=0;
						pass1=0,pass2=0,flag=0;
						//create_password();
	}

}
}
void enter_password(void){
		/* Get the pressed button from keypad */
	if(key_num3[k]!=13){
		key_num3[k] = KEYPAD_getPressedKey();
		_delay_ms(500);
		if(key_num3[k]!=13){
			LCD_displayCharacter('*');
			UART_sendByte(key_num3[k]);
			_delay_ms(30);
			k++;
				}
}
}
void main_menu(void){
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"+: Open door");
	LCD_displayStringRowColumn(1,0,"-:changepassword");
	show=1;
}
int main(){
	/* Enable Global Interrupt I-Bit */
	SREG |= (1<<7);
	/* Create configuration structure for Timer0 driver */
	Timer0_ConfigType Timer0_Config = {F_CPU_1024,Normal};
	/* Set the Call back function pointer in the Timer driver */
	Timer0_setCallBack(Timer0_callBack);
	/* Initialize both the LCD and UART driver */
	LCD_init();
	Uart_ConfigType Uart_Config = {Disabled,One,Eight,9600};
	UART_init(&Uart_Config);
	LCD_displayString("Enter Password: ");
	LCD_moveCursor(1,0);
	while(1){
        if(created==0)
        	create_password();
        else if(show==0)
            main_menu();
        else if(KEYPAD_getPressedKey()=='+'){
        	UART_sendByte(unlock);
            _delay_ms(500);
            LCD_clearScreen();
            LCD_displayString("Enter Password: ");
            LCD_moveCursor(1,0);
            for(i=0;i<pass1;i++){
                enter_password();
            }
            while(confirmed==0){
                confirmed=UART_recieveByte();
            }
            if(confirmed==1){}
            else if(confirmed==2){
                LCD_clearScreen();
              	LCD_displayString("wrong ");
                _delay_ms(15000);
                show=0;
                k=0;
                key_num3[10]=0;
                confirmed=0;
                /*confirmed=0;
                key_num3[10]=0;
                LCD_clearScreen();
                LCD_displayString("Enter Password: ");
                LCD_moveCursor(1,0);
                for(i=0;i<pass1;i++){
                     enter_password();
                }*/
               // wrong=1;
            }

         }
      	 else if(KEYPAD_getPressedKey()=='-'){
      		UART_sendByte(change);
      		_delay_ms(500);
            LCD_clearScreen();
            LCD_displayString("Enter Password: ");
            LCD_moveCursor(1,0);
            for(i=0;i<pass1;i++){
            	enter_password();
            }
            while(confirmed==0){
            	confirmed=UART_recieveByte();
            }
            if(confirmed==1){
               LCD_clearScreen();
               LCD_displayString("Enter Password: ");
               LCD_moveCursor(1,0);
               key_num[10]=0;
               key_num2[10]=0;
               pass1=0,pass2=0,flag=0;
               created=0;
               show=0;
               confirmed=0;
               key_num3[10]=0;
               k=0;
          }
            else if(confirmed==2){
            	LCD_clearScreen();
            	LCD_displayString("wrong ");
            	_delay_ms(15000);
    		    //Timer0_Init(&Timer0_Config,0);
    		   /* while(g_counter!=sec15){};
    		    g_counter=0;
    		    Timer0_DeInit();
    		    LCD_clearScreen();*/
    		    show=0;
    		    k=0;
    		    key_num3[10]=0;
    		    confirmed=0;
            	/*confirmed=0;
            	k=0;
                key_num3[10]=0;
                LCD_clearScreen();
                LCD_displayString("Enter Password: ");
                LCD_moveCursor(1,0);
                for(i=0;i<pass1;i++){
                     enter_password();
                 }*/
            }
      	 }
}
}

