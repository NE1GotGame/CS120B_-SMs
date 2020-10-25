/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum button{ LED, LED_PB0, LED_PB1} state;

void onLED(char button) {
	
	switch(state) {
		case LED:
			state = LED_PB0;
			break;
		case LED_PB0:
			if(button) {
				state = LED_PB1;
			}
			else if (!button) {
				state = LED_PB0;
			}
			break;
		case LED_PB1:
			if (button) {
				state = LED_PB0;
			}
			else if (!button) {
				state = LED_PB1;
			}
			break;
		default:
			state = LED;
			break;
	}
	switch(state){
		case LED_PB0:
			PORTB = 0x01;
			break;
		case LED_PB1:
			PORTB = 0x02;
			break;
		default:
			PORTB = 0X01;
			break;
	}
}


int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
	unsigned char button;
	state = LED;
    while (1) {
	button = PINA & 0x01;
	onLED(button);
    }
    return 1;
}
