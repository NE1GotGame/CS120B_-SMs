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

enum locking_state {start, pound, Y, locked, unlocked} state;

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;

	state = start;
	unsigned char  enterLock= 0;
    /* Insert your solution below */
    while (1){
	switch (state) {
		case start:
				state = pound;
				break;
		case pound:	
				if (PINA == PINA){
					state = locked;
				}
				if(PINA == 0x04){
					state = Y;
				}
				else {
					state = pound;
				}
				break;
		case Y:	
				if (PINA == 0x00){
					state = locked;
				}
				else if(PINA == 0x04){
					state = Y;
				}
				else {
					state = pound;
				}
				break;
		case locked:	
				if (PINA == PINA) {
					state == locked;
				}
				if (PINA == 0x02) {
					enterLock = 1;
					state = unlocked;
				}
				else if(PINA == 0x00){
					state = locked;
				}
				else {
					state = pound;
				}
				break;
		case unlocked:	
				if(PINA == 0x80){
					state = pound;
				}
				else {
					state = unlocked;
				}
				break;
		default:	
				break;
	}

	switch(state){
		case pound:
		case Y:
		case locked:	
				PORTB = 0x00;
				break;
		case unlocked:	
				if (enterLock == 1) {
					if (PORTB == 0x00) {		
						PORTB = 0x01;
					}
					else {
						PORTB = 0x00;
					}
					enterLock = 0;
				}
				break;
		default:	
				break;
	}
    }
    return 1;
}

